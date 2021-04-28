//https://www.mikrocontroller.net/topic/180921 Thomas F.(adriano6)
#include "LCD_101x64.h"
#include "Font7x6.h"
#include <Arduino.h>

LCD::LCD(uint8_t _data, uint8_t _clock, uint8_t _control, uint8_t _reset, uint8_t _chipSelect) {
  data = _data;
  clock = _clock;
  control = _control;
  reset_ = _reset;
  chipSelect = _chipSelect;
  pinMode(data, OUTPUT);
  pinMode(clock, OUTPUT);
  pinMode(control, OUTPUT);
  pinMode(reset_, OUTPUT);
  pinMode(chipSelect, OUTPUT);
}


// ------------------------------------------------------------------
// char
// ------------------------------------------------------------------
size_t LCD::write(uint8_t ch) {
  drawChar(ch);
  return 1;
}

// ------------------------------------------------------------------
// 
// ------------------------------------------------------------------
void LCD::reset() {
  _delay_us(10);
  digitalWrite(data, LOW);//Data_LO
  digitalWrite(clock, LOW);//Clock_LO
  digitalWrite(control, LOW);//Control_LO
  _delay_us(10);
  digitalWrite(reset_, HIGH);//Reset_HI
  _delay_us(10);
  digitalWrite(chipSelect, LOW);//ChipSelect_LO
  _delay_us(10);
  digitalWrite(reset_, LOW);//Reset_LO
  _delay_us(10);  
  digitalWrite(reset_, HIGH);//Reset_HI
  digitalWrite(chipSelect, HIGH);//ChipSelect_HI
}


// ------------------------------------------------------------------
// command to display
// ------------------------------------------------------------------
void LCD::sendCommand(uint8_t command) {
  uint8_t i,s;
  s=0x80;

  digitalWrite(data, LOW);//Data_LO
  digitalWrite(clock, LOW);//Clock_LO
  digitalWrite(control, LOW);//Control_LO
  digitalWrite(chipSelect, LOW);//ChipSelect_LO
  _delay_us(10);
  for (i=0; i<8; i++) {
    if (command & s)  digitalWrite(data, HIGH);//Data_HI;
    else digitalWrite(data, LOW);//Data_LO
    s = s>>1;
    _delay_us(10);
    digitalWrite(clock, HIGH);//Clock_HI
    _delay_us(10);
    digitalWrite(clock, LOW);//Clock_LO
    _delay_us(10);
  }
  digitalWrite(chipSelect, HIGH);//ChipSelect_HI
}


// ------------------------------------------------------------------
// 
// ------------------------------------------------------------------
void LCD::init() {

  reset();

  sendCommand(0b00100001);    // Function set: chip is active, horizontal addressing, use extended instruction set
  //SendCommand(0b11011010);    // 
  sendCommand(0b00010100);    // Bias System 
  //SendCommand(0b00001011);    // Set voltage multiplier factor -> ok
  //SendCommand(0b00000101);    // Temperature controlVLCD temperature coefficient 1
  sendCommand((128+80));      // contrast
  sendCommand(0b00100000);    // Function set
  sendCommand(0b00010001);    // VLCD programming range: high
  sendCommand(0b00001100);    // Display control: normal 
  //  SendCommand(0b00001101);    // Display control: inverse -> ok
}   


// ------------------------------------------------------------------
// Line: 0..7, Row 0..100;
// ------------------------------------------------------------------
void LCD::setCursor(uint8_t line, uint8_t row) {
  _setCursor(7-line, row);
}


// ------------------------------------------------------------------
// Line: 0..7, Row 0..100;
// ------------------------------------------------------------------
void LCD::_setCursor(uint8_t line, uint8_t row) {
  sendCommand( 0b00101000);
  sendCommand((0b01000000 + line));
  sendCommand((0b10000000 + row));
}

// ------------------------------------------------------------------
// data to display
// ------------------------------------------------------------------
void LCD::sendData(uint8_t value) {
  uint8_t i,s;
  s = 0x80;
  
  digitalWrite(data, LOW);//Data_LO
  digitalWrite(clock, LOW);//Clock_LO
  digitalWrite(control, HIGH);//Control_HI
  digitalWrite(chipSelect, LOW);//ChipSelect_LO

  _delay_us(10);
  for (i = 0; i < 8; i++) {
    if (value & s)  digitalWrite(data, HIGH);//Data_HI
    else digitalWrite(data, LOW);//Data_LO
    s = s>>1;
    _delay_us(10);
    digitalWrite(clock, HIGH);//Clock_HI
    _delay_us(10);
    digitalWrite(clock, LOW);//Clock_LO
    _delay_us(10);
  }
  digitalWrite(chipSelect, HIGH);//ChipSelect_HI
}

// ------------------------------------------------------------------
// char 0-9 A-Z : space
// ------------------------------------------------------------------
void LCD::drawChar(char ch) {
  for (int i = 0; i < 6; i++) {
    sendData(pgm_read_byte(&all_lat[convert(ch)][i]));
  }
}


void LCD::drawRaw(uint8_t raw[6]) {
	for (int i = 0; i < 6; i++) {
		sendData(raw[i]);
	}
}

// -------------------------------------------------------------------
// line
// -------------------------------------------------------------------
void LCD::clearLine(uint8_t line) {
	setCursor(line, 0);
	for (uint8_t i = 0; i < 101; i++) {
		sendData(0x0);
	}
}

// ------------------------------------------------------------------
// 
// ------------------------------------------------------------------
void LCD::clear() {
  _setCursor(0, 0);
  for (long i = 0; i < ((101*64) / 8+8); i++) {
    sendData(0x0);
  }
}
