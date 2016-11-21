#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>

#include "iohelp.h"
#include "smallfont.h"
#include "title.h"
#include "anim.h"

// https://gist.github.com/thegaragelab/0a0dc5f5745a308312cf
// https://github.com/thegaragelab/tinytemplate
// https://github.com/JChristensen/tinySPI/blob/master/tinySPI.cpp


#define LCD_MOSI  PINB2
#define LCD_SCK   PINB4
#define LCD_CD    PINB1
#define LCD_RESET PINB0
#define LCD_COL 84
#define LCD_ROW 6

#define WAIT_INNER (F_CPU / 6000)



/** Wait for a time
*
* @param millis number of miliseconds
*/

void wait(uint16_t millis) {
  for(uint16_t outer=0; outer<millis; outer++) {
    for(uint16_t inner=0; inner<WAIT_INNER; inner++) {
      asm volatile(
        "  nop    \n\t"
      );
  	}
 	}
}



/** Send a command byte to the LCD
*
* @param cmd the command byte to send.
*/
void lcdCommand(uint8_t cmd) {
  // Bring CD low
  PORTB &= ~(1 << LCD_CD);
  // Send the data
  sspiOutMSB(LCD_SCK, LCD_MOSI, cmd, 8);
}


void lcdInit() {
	// Set up the output pins, ensuring they are all 'low' to start
	uint8_t val = (1 << LCD_SCK) | (1 << LCD_MOSI) | (1 << LCD_RESET) | (1 << LCD_CD);
	PORTB &= ~val;
 	DDRB |= val;
	// Do a hard reset on the LCD
  wait(10);
	PORTB |= (1 << LCD_RESET);
 
	// Initialise the LCD
 	lcdCommand(0x21);  // LCD Extended Commands.
  lcdCommand(0xBF);  // Set LCD Vop (Contrast).
  lcdCommand(0x04);  // Set Temp coefficent.
 	lcdCommand(0x14);  // LCD bias mode 1:48.
 	lcdCommand(0x20);  // LCD Normal commands
 	lcdCommand(0x0C);  // Normal display, horizontal addressing
}

/** Send a data byte to the LCD
*
* @param data the data byte to send.
*/

static void lcdData(uint8_t data) {
	// Bring CD high
	PORTB |= (1 << LCD_CD);
 	// Send the data
  sspiOutMSB(LCD_SCK, LCD_MOSI, data, 8);
}

/** Clear the screen
*
* Clear the entire display.
*
* @param invert if true the colors are inverted and the screen will be filled
*               with black.
*/

void lcdClear(bool invert) {
	uint8_t fill = invert?0xFF:0x00;       // Set the position
 	lcdCommand(0x80);
  lcdCommand(0x40);
  // Fill in the whole display
 	for(uint16_t index = 0; index < (LCD_COL * LCD_ROW); index++) {
  	lcdData(fill);
	}
}

void lcdPrintChar(uint8_t row, uint8_t col, char ch, bool invert) {
	// Make sure it is on the screen
  if((row>=LCD_ROW)||(col>=LCD_COL)) {
    return;
	}
  // If the character is invalid replace it with the '?'
  if((ch<0x20)||(ch>0x7f)){
    ch = '?';
	}
  
	// Set the starting address
  lcdCommand(0x80 | col);
  lcdCommand(0x40 | (row % LCD_ROW));
  // And send the column data
  const uint8_t *chdata = SMALL_FONT + ((ch - 0x20) * 5);
  
	for(uint8_t pixels = 0; (pixels < DATA_WIDTH) && (col < LCD_COL); pixels++, col++, chdata++) {
    uint8_t data = pgm_read_byte_near(chdata);
    lcdData(invert?~data:data);
	}
  // Add the padding byte
  if(col < LCD_COL) {
    lcdData(invert?0xFF:0x00);
	} 
}

void lcdPrint(uint8_t row, uint8_t col, const char *str, bool invert){
  for(;(*str!='\0')&&(col<LCD_COL);col+=CHAR_WIDTH,str++){
    lcdPrintChar(row, col, *str, invert);
  }
}


/** Display an arbitrary graphic on the display
 *
 * This function is used to display user defined graphics held in PROGMEM to
 * the display. The first byte of the graphic indicates the height (in 8 pixel
 * rows) and the width (in pixel columns) packed as HHWWWWWW giving a maximum
 * size of 4 rows (32 pixels) by 64 pixels for a single image. Images that
 * will display off the edge of the screen are clipped. The packed version of
 * the width and height are 1 less than the actual width and height.
 *
 * The image is packed as a sequence of 8 pixel vertical strips.
 *
 * @param row the row number (0 to 5) to start the top left of the image.
 * @param col the column number (0 to 83) to start the top left of the image.
 * @param img pointer to the image in PROGMEM.
 * @param invert if true the pixel colors will be inverted.
 */

void lcdImageP(uint8_t row, uint8_t col, const uint8_t *img, bool invert) {
  // Break out the width and height
  uint8_t data = pgm_read_byte_near(img++);
  uint8_t height = 6; //(data >> 6) + 1;
  uint8_t width = 84; //(data & 0x03F) + 1;
  while((height>0)&&(row<LCD_ROW)) {
    // Set the starting address
    lcdCommand(0x80 | col);
    lcdCommand(0x40 | (row % LCD_ROW));
    // Send the data (up to the end of the screen)
    for(uint8_t offset=0; offset<width; offset++, img++) {
      if((col+offset)<LCD_COL) {
        if(invert){
          lcdData(~pgm_read_byte_near(img));
        } else {
          lcdData(pgm_read_byte_near(img));
        }
      }
    	height--;
    	row++;
    }
	}
}

void lcdImageB(const uint8_t * img, bool invert) {
 	lcdCommand(0x80);
  lcdCommand(0x40);
  // Fill in the whole display
 	for(uint16_t index = 0; index < (LCD_COL * LCD_ROW); index++) {
  	lcdData(invert?~pgm_read_byte_near(img):pgm_read_byte_near(img));
		img++;
	}
}

int main(void) {
   
  lcdInit();
  lcdClear(true);
  wait(100);
	lcdClear(false);
  wait(100);


  lcdImageB(IMAGE_TITLE,true);
  wait(1000);
 
  while(1) {  

    // Intro graphics
    for (int i =0; i < 5; i++) {
      lcdImageB(IMAGE_B0,true);
      wait(100);
      lcdImageB(IMAGE_B1,true);
      wait(100);
    }

    lcdImageB(IMAGE_B1,true);
    wait(250);

    // Page 1 - Opening page with names
    lcdClear(false);
    lcdPrint(0,0,"test0",false); 
    lcdPrint(1,0,"test1",false);
    lcdPrint(2,0,"test2",false);
    lcdPrint(3,0,"test3",false);
    lcdPrint(4,0,"test4",false);
    wait(500); 
    
  }
}
