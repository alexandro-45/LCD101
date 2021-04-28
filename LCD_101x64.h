#ifndef LCD_101x64_H
#define LCD_101x64_H
//----------------------------------------------------------------------------------------
// LCD Siemens A60 Handy 101x64
//--------------------------------------------------------------------------------------

#include <avr/io.h>
#include <compat/deprecated.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "Print.h"

//-------------------------------------------------------------------------------------------------
class LCD: public Print {
  private:
    uint8_t data;
    uint8_t clock;
    uint8_t control;
    uint8_t reset_;
    uint8_t chipSelect;
    void _setCursor(uint8_t line, uint8_t row);
  public:
    LCD(uint8_t _data, uint8_t _clock, uint8_t _control, uint8_t _reset, uint8_t _chipSelect);
    virtual size_t write(uint8_t);
    void reset(void);
    void init(void);
    void sendCommand(uint8_t command);
    void sendData(uint8_t value);
    void setCursor(uint8_t line, uint8_t row);
    void drawChar(char ch);
	void drawRaw(uint8_t raw[6]);
	void clearLine(uint8_t line);
    void clear();
};
//--------------------------------------------------------------------------------------
#endif
