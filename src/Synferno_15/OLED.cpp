#include "OLED.h"

// A4 == SDA
// A5 == SCL
U8X8_SSD1306_128X64_NONAME_SW_I2C SSD1306(/* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE); 

void OLED::begin() {
  SSD1306.begin();
  SSD1306.setPowerSave(0);

  // provides 8 rows and 16 characters at these settings
  SSD1306.setFont(u8x8_font_chroma48medium8_r);

  this->buffer.reserve(16);
  this->buffer = "*              *";
  
  this->write(0);
  this->write(7);
}

void OLED::write(byte row, byte col, boolean pad) {
  // right pad
  if( pad ) {
    while( this->buffer.length() < (16-col) ) this->buffer += " ";
  }
  
  static char s[16];
  this->buffer.toCharArray(s, 16);  
  SSD1306.drawString(col, row, s);
}

