#ifndef ULTRA_LCD_IMPLEMENTATION_HITACHI_HD44780_H
#define ULTRA_LCD_IMPLEMENTATION_HITACHI_HD44780_H

/**
* Implementation of the LCD display routines for a hitachi HD44780 display. These are common LCD character displays.
* When selecting the rusian language, a slightly different LCD implementation is used to handle UTF8 characters.
**/

#if LANGUAGE_CHOICE == 6
#include "LiquidCrystalRus.h"
#define LCD_CLASS LiquidCrystalRus
#else
#include <LiquidCrystal.h>
#define LCD_CLASS LiquidCrystal
#endif

/* Custom characters defined in the first 8 characters of the LCD */
#define LCD_STR_BEDTEMP     "\x00"
#define LCD_STR_DEGREE      "\x01"
#define LCD_STR_THERMOMETER "\x02"
#define LCD_STR_UPLEVEL     "\x03"
#define LCD_STR_REFRESH     "\x04"
#define LCD_STR_FOLDER      "\x05"
#define LCD_STR_FEEDRATE    "\x06"
#define LCD_STR_CLOCK       "\x07"
#define LCD_STR_ARROW_RIGHT "\x7E"  /* from the default character set */
LCD_CLASS lcd(LCD_PINS_RS, LCD_PINS_ENABLE, LCD_PINS_D4, LCD_PINS_D5,LCD_PINS_D6,LCD_PINS_D7);  //RS,Enable,D4,D5,D6,D7

static void lcd_implementation_init()
{
    byte bedTemp[8] =
    {
        B00000,
        B11111,
        B10101,
        B10001,
        B10101,
        B11111,
        B00000,
        B00000
    }; //thanks Sonny Mounicou
    byte degree[8] =
    {
        B01100,
        B10010,
        B10010,
        B01100,
        B00000,
        B00000,
        B00000,
        B00000
    };
    byte thermometer[8] =
    {
        B00100,
        B01010,
        B01010,
        B01010,
        B01010,
        B10001,
        B10001,
        B01110
    };
    byte uplevel[8]={
        B00100,
        B01110,
        B11111,
        B00100,
        B11100,
        B00000,
        B00000,
        B00000
    }; //thanks joris
    byte refresh[8]={
        B00000,
        B00110,
        B11001,
        B11000,
        B00011,
        B10011,
        B01100,
        B00000,
    }; //thanks joris
    byte folder [8]={
        B00000,
        B11100,
        B11111,
        B10001,
        B10001,
        B11111,
        B00000,
        B00000
    }; //thanks joris
    byte feedrate [8]={
        B11100,
        B10000,
        B11000,
        B10111,
        B00101,
        B00110,
        B00101,
        B00000
    }; //thanks Sonny Mounicou
    byte clock [8]={
        B00000,
        B01110,
        B10011,
        B10101,
        B10001,
        B01110,
        B00000,
        B00000
    }; //thanks Sonny Mounicou
    lcd.begin(LCD_WIDTH, LCD_HEIGHT);
    lcd.createChar(LCD_STR_BEDTEMP[0], bedTemp);
    lcd.createChar(LCD_STR_DEGREE[0], degree);
    lcd.createChar(LCD_STR_THERMOMETER[0], thermometer);
    lcd.createChar(LCD_STR_UPLEVEL[0], uplevel);
    lcd.createChar(LCD_STR_REFRESH[0], refresh);
    lcd.createChar(LCD_STR_FOLDER[0], folder);
    lcd.createChar(LCD_STR_FEEDRATE[0], feedrate);
    lcd.createChar(LCD_STR_CLOCK[0], clock);
    lcd.clear();
    //lcd_error_implementation();
}
static void lcd_implementation_clear()
{
    lcd.clear();
}
/* Arduino < 1.0.0 is missing a function to print PROGMEM strings, so we need to implement our own */
static void lcd_printPGM(const char* str)
{
    char c;
    while((c = pgm_read_byte(str++)) != '\0')
    {
        lcd.write(c);
    }
}

static void lcd_implementation_temperaturelo_screen()//function added by sagard for temperature screen
{
    lcd.clear();
    //delay(1000);  
    int tHotend=int(degHotend(0) + 0.5);
    int tTarget=int(degTargetHotend(0) + 0.5);
    lcd.setCursor(0,0);
    lcd_printPGM(PSTR("Heating Extruder"));
    lcd.setCursor(0,1);
	//lcd.print(LCD_STR_THERMOMETER[0]);
    lcd_printPGM(PSTR("E1"));
    lcd.print(itostr3(tHotend));
    lcd.print('/');
    lcd.print(itostr3left(tTarget));
    lcd_printPGM(PSTR(LCD_STR_DEGREE " "));
    if (tTarget < 10)
        lcd.print(' ');
/*# if EXTRUDERS > 1 || TEMP_SENSOR_BED != 0
    //If we have an 2nd extruder or heated bed, show that in the top right corner
    lcd.setCursor(8, 1);
#  if EXTRUDERS > 1
    tHotend = int(degHotend(1) + 0.5);
    tTarget = int(degTargetHotend(1) + 0.5);
    lcd.print(LCD_STR_THERMOMETER[0]);
#  else//Heated bed
    lcd.setCursor(0,2)
    tHotend=int(degBed() + 0.5);
    tTarget=int(degTargetBed() + 0.5);
    lcd.print(LCD_STR_BEDTEMP[0]);
#  endif
    lcd.print(itostr3(tHotend));
    lcd.print('/');
    lcd.print(itostr3left(tTarget));
# endif//EXTRUDERS > 1 || TEMP_SENSOR_BED != 0*/
    if(tHotend>=tTarget)
    {
      //lcd.clear();
      //if(a=0)
      //{
      lcd.setCursor(0,3);
      lcd_printPGM(PSTR("Heating Done"));
      lcd.setCursor(0,4);
      lcd_printPGM(PSTR("Push Filament Now"));
      //}
      //else
      //{
      //lcd.setCursor(0,3);
      //lcd_printPGM(PSTR("Heating Done"));
      //lcd.setCursor(0,4);
      //lcd_printPGM(PSTR("Pull Filament Now"));
            
    //}
}
}

static void lcd_implementation_temperatureun_screen()//function added by sagard for temperature screen
{
    lcd.clear();
    //delay(1000);  
    int tHotend=int(degHotend(0) + 0.5);
    int tTarget=int(degTargetHotend(0) + 0.5);
    lcd.setCursor(0,0);
    lcd_printPGM(PSTR("Heating Extruder"));
    lcd.setCursor(0,1);
	//lcd.print(LCD_STR_THERMOMETER[0]);
    lcd_printPGM(PSTR("E1"));
    lcd.print(itostr3(tHotend));
    lcd.print('/');
    lcd.print(itostr3left(tTarget));
    lcd_printPGM(PSTR(LCD_STR_DEGREE " "));
    if (tTarget < 10)
        lcd.print(' ');
/*# if EXTRUDERS > 1 || TEMP_SENSOR_BED != 0
    //If we have an 2nd extruder or heated bed, show that in the top right corner
    lcd.setCursor(8, 1);
#  if EXTRUDERS > 1
    tHotend = int(degHotend(1) + 0.5);
    tTarget = int(degTargetHotend(1) + 0.5);
    lcd.print(LCD_STR_THERMOMETER[0]);
#  else//Heated bed
    lcd.setCursor(0,2)
    tHotend=int(degBed() + 0.5);
    tTarget=int(degTargetBed() + 0.5);
    lcd.print(LCD_STR_BEDTEMP[0]);
#  endif
    lcd.print(itostr3(tHotend));
    lcd.print('/');
    lcd.print(itostr3left(tTarget));
# endif//EXTRUDERS > 1 || TEMP_SENSOR_BED != 0*/
    if(tHotend>=tTarget)
    {
      //lcd.clear();
      //if(a=0)
      //{
      lcd.setCursor(0,3);
      lcd_printPGM(PSTR("Heating Done"));
      //lcd.setCursor(0,4);
      //lcd_printPGM(PSTR("Push Filament Now"));
      //}
      //else
      //{
      //lcd.setCursor(0,3);
      //lcd_printPGM(PSTR("Heating Done"));
      lcd.setCursor(0,4);
      lcd_printPGM(PSTR("Pull Filament Now"));
            
    //}
}
}

//static void lcd_implementation_filename(char* name);

/*
Possible status screens:
16x2   |0123456789012345|
       |000/000 B000/000|
       |Status line.....|

16x4   |0123456789012345|
       |000/000 B000/000|
       |SD100%    Z000.0|
       |F100%     T--:--|
       |Status line.....|

20x2   |01234567890123456789|
       |T000/000D B000/000D |
       |Status line.........|

20x4   |01234567890123456789|
       |T000/000D B000/000D |
       |X+000.0 Y+000.0 Z+000.0|
       |F100%  SD100% T--:--|
       |Status line.........|

20x4   |01234567890123456789|
       |T000/000D B000/000D |
       |T000/000D     Z000.0|
       |F100%  SD100% T--:--|
       |Status line.........|

//20x4 display what we want this is implemented and tested successfully
       |01234567890123456789|
       |E1:000/000DC   --:--|
       |BT:000/000DC  SD---%|
       |Filename.gc         |
       |Status line.........|
*/
static void lcd_implementation_status_screen()//function changed by sagard according to version1 requirement
{
    int tHotend=int(degHotend(0) + 0.5);
    int tTarget=int(degTargetHotend(0) + 0.5);

#if LCD_WIDTH < 20//no changes here
    lcd.setCursor(0, 0);
    lcd.print(itostr3(tHotend));
    lcd.print('/');
    lcd.print(itostr3left(tTarget));

# if EXTRUDERS > 1 || TEMP_SENSOR_BED != 0
    //If we have an 2nd extruder or heated bed, show that in the top right corner
    lcd.setCursor(8, 0);
#  if EXTRUDERS > 1
    tHotend = int(degHotend(1) + 0.5);
    tTarget = int(degTargetHotend(1) + 0.5);
    lcd.print(LCD_STR_THERMOMETER[0]);
#  else//Heated bed
    tHotend=int(degBed() + 0.5);
    tTarget=int(degTargetBed() + 0.5);
    lcd.print(LCD_STR_BEDTEMP[0]);
#  endif
    lcd.print(itostr3(tHotend));
    lcd.print('/');
    lcd.print(itostr3left(tTarget));
# endif//EXTRUDERS > 1 || TEMP_SENSOR_BED != 0

#else//LCD_WIDTH > 19//here use directly the SD function that they have
    lcd.setCursor(0, 0);
    /*#  ifdef SDSUPPORT
    lcd_printPGM(PSTR("SD"));
    if (IS_SD_PRINTING)
        lcd.print(itostr3(card.percentDone()));
    else
        lcd_printPGM(PSTR("---"));
    lcd.print('%');
#  endif */
    //lcd.print(LCD_STR_THERMOMETER[0]);
    lcd_printPGM(PSTR("ET:"));
    lcd.print(itostr3(tHotend));
    lcd.print('/');
    lcd.print(itostr3left(tTarget));
    lcd_printPGM(PSTR(LCD_STR_DEGREE "C "));
    if (tTarget < 10)
        lcd.print(' ');
	///this is to be used in second line
	/*lcd_printPGM("PRINT STATUS ");
	#  ifdef SDSUPPORT
    if (IS_SD_PRINTING)
        lcd.print(itostr3(card.percentDone()));
    else
        lcd_printPGM(PSTR("---"));
    lcd.print('%');
    #  endif//SDSUPPORT*/
	#endif//LCD_WIDTH > 19
	lcd.setCursor(LCD_WIDTH - 6, 0);
    //lcd.print(LCD_STR_CLOCK[0]);
    if(starttime != 0)
    {
        uint16_t time = millis()/60000 - starttime/60000;
        lcd.print(itostr2(time/60));
        lcd.print(':');
        lcd.print(itostr2(time%60));
    }else{
        lcd_printPGM(PSTR("--:--"));
    }

/*# if EXTRUDERS > 1 || TEMP_SENSOR_BED != 0
    //If we have an 2nd extruder or heated bed, show that in the top right corner
    lcd.setCursor(10, 0);
#  if EXTRUDERS > 1
    tHotend = int(degHotend(1) + 0.5);
    tTarget = int(degTargetHotend(1) + 0.5);
    lcd.print(LCD_STR_THERMOMETER[0]);
#  else//Heated bed
    tHotend=int(degBed() + 0.5);
    tTarget=int(degTargetBed() + 0.5);
    lcd.print(LCD_STR_BEDTEMP[0]);
#  endif
    lcd.print(itostr3(tHotend));
    lcd.print('/');
    lcd.print(itostr3left(tTarget));
    lcd_printPGM(PSTR(LCD_STR_DEGREE " "));
    if (tTarget < 10)
        lcd.print(' ');
# endif//EXTRUDERS > 1 || TEMP_SENSOR_BED != 0
*/
//#endif//LCD_WIDTH > 19

#if LCD_HEIGHT > 2//2nd line coding
//Lines 2 for 4 line LCD
# if LCD_WIDTH < 20
#  ifdef SDSUPPORT
    lcd.setCursor(0, 2);
    lcd_printPGM(PSTR("SD"));
    if (IS_SD_PRINTING)
        lcd.print(itostr3(card.percentDone()));
    else
        lcd_printPGM(PSTR("---"));
    lcd.print('%');
#  endif//SDSUPPORT
# else//LCD_WIDTH > 19
    lcd.setCursor(0,1);
    #  if TEMP_SENSOR_BED != 0
    //If we both have a 2nd extruder and a heated bed, show the heated bed temp on the 3rd line on the left, as the first line is filled with extruder temps
    //lcd.setCursor(0,2);
    tHotend=int(degBed() + 0.5);
    tTarget=int(degTargetBed() + 0.5);
    lcd_printPGM(PSTR("BT:"));
    //lcd.print(LCD_STR_BEDTEMP[0]);
    lcd.print(itostr3(tHotend));
    lcd.print('/');
    lcd.print(itostr3left(tTarget));
    lcd_printPGM(PSTR(LCD_STR_DEGREE "C "));
    if (tTarget < 10)
        lcd.print(' ');
#  else
    lcd.setCursor(0,1);
    lcd_printPGM(PSTR("  "));
#  endif
   lcd.setCursor(LCD_WIDTH-7, 1);
#  ifdef SDSUPPORT
    lcd_printPGM(PSTR("SD"));
    if (IS_SD_PRINTING)
        lcd.print(itostr3(card.percentDone()));
    else
        lcd_printPGM(PSTR("---"));
    lcd.print('%');
#  endif 
        /*lcd_printPGM(PSTR("E1"));
	//lcd.print(LCD_STR_THERMOMETER[0]);
    lcd.print(itostr3(tHotend));
    lcd.print('/');
    lcd.print(itostr3left(tTarget));
    lcd_printPGM(PSTR(LCD_STR_DEGREE " "));
    if (tTarget < 10)
        lcd.print(' ');
	# if EXTRUDERS > 1 || TEMP_SENSOR_BED != 0
    //If we have an 2nd extruder or heated bed, show that in the top right corner
    lcd.setCursor(10, 1);
#  if EXTRUDERS > 1
    tHotend = int(degHotend(1) + 0.5);
    tTarget = int(degTargetHotend(1) + 0.5);
    lcd.print(LCD_STR_THERMOMETER[0]);
#  else//Heated bed
    tHotend=int(degBed() + 0.5);
    tTarget=int(degTargetBed() + 0.5);
    lcd.print(LCD_STR_BEDTEMP[0]);
#  endif
    lcd.print(itostr3(tHotend));
    lcd.print('/');
    lcd.print(itostr3left(tTarget));
    lcd_printPGM(PSTR(LCD_STR_DEGREE " "));
    if (tTarget < 10)
        lcd.print(' ');
# endif//EXTRUDERS > 1 || TEMP_SENSOR_BED != 0*/
	/*lcd.setCursor(0, 1);
    lcd_printPGM("EXT1:");
    lcd.print(itostr3(tHotend));
    lcd.print('/');
    lcd.print(itostr3left(tTarget));
    lcd_printPGM(PSTR(LCD_STR_DEGREE " "));
    if (tTarget < 10)
    lcd.print(' ');
	*/
	/*#  if EXTRUDERS > 1 && TEMP_SENSOR_BED != 0
    //If we both have a 2nd extruder and a heated bed, show the heated bed temp on the 2nd line on the left, as the first line is filled with extruder temps
    tHotend=int(degBed() + 0.5);
    tTarget=int(degTargetBed() + 0.5);

    lcd.setCursor(0, 1);
    lcd.print(LCD_STR_BEDTEMP[0]);
    lcd.print(itostr3(tHotend));
    lcd.print('/');
    lcd.print(itostr3left(tTarget));
    lcd_printPGM(PSTR(LCD_STR_DEGREE " "));
    if (tTarget < 10)
        lcd.print(' ');
#  else
    lcd.setCursor(0,1);
    lcd.print('X');
    lcd.print(ftostr3(current_position[X_AXIS]));
    lcd_printPGM(PSTR(" Y"));
    lcd.print(ftostr3(current_position[Y_AXIS]));
#  endif//EXTRUDERS > 1 || TEMP_SENSOR_BED != 0
*/
#endif//LCD_WIDTH > 19
/*    lcd.setCursor(LCD_WIDTH - 8, 1);
    lcd.print('Z');
    lcd.print(ftostr32(current_position[Z_AXIS]));*/
#endif//LCD_HEIGHT > 2

#if LCD_HEIGHT > 3
    //lcd.setCursor(0, 2);
    //lcd.print(LCD_STR_FEEDRATE[0]);
    //lcd.print(itostr3(feedmultiply));
    //lcd.print('%');
# if LCD_WIDTH > 19
lcd.setCursor(0, 2);
lcd.print(lcd_filename_message);
    /*#  if EXTRUDERS > 1 && TEMP_SENSOR_BED != 0
    //If we both have a 2nd extruder and a heated bed, show the heated bed temp on the 3rd line on the left, as the first line is filled with extruder temps
    lcd.setCursor(0,2);
    tHotend=int(degBed() + 0.5);
    tTarget=int(degTargetBed() + 0.5);
    lcd_printPGM(PSTR("BT"));
    //lcd.print(LCD_STR_BEDTEMP[0]);
    lcd.print(itostr3(tHotend));
    lcd.print('/');
    lcd.print(itostr3left(tTarget));
    lcd_printPGM(PSTR(LCD_STR_DEGREE " "));
    if (tTarget < 10)
        lcd.print(' ');
#  else
    lcd.setCursor(0,2);
    lcd_printPGM(PSTR("  "));
#  endif//EXTRUDERS > 1 || TEMP_SENSOR_BED != 0*/

    /*lcd.setCursor(0,2);
# if EXTRUDERS > 1 || TEMP_SENSOR_BED != 0
    //If we have an 2nd extruder or heated bed, show that in the top right corner
    //lcd.setCursor(10, 0);
#  if EXTRUDERS > 1
    tHotend = int(degHotend(1) + 0.5);
    tTarget = int(degTargetHotend(1) + 0.5);
    lcd.print(LCD_STR_THERMOMETER[0]);
#  else//Heated bed
    tHotend=int(degBed() + 0.5);
    tTarget=int(degTargetBed() + 0.5);
    lcd.print(LCD_STR_BEDTEMP[0]);
#  endif
    lcd.print(itostr3(tHotend));
    lcd.print('/');
    lcd.print(itostr3left(tTarget));
    lcd_printPGM(PSTR(LCD_STR_DEGREE " "));
    if (tTarget < 10)
        lcd.print(' ');
#else
    lcd_printPGM("PLA Printing");*/
//# endif//EXTRUDERS > 1 || TEMP_SENSOR_BED != 0

/*#  ifdef SDSUPPORT
    lcd.setCursor(7, 2);
    lcd_printPGM(PSTR("SD"));
    if (IS_SD_PRINTING)
        lcd.print(itostr3(card.percentDone()));
    else
        lcd_printPGM(PSTR("---"));
    lcd.print('%');
#  endif//SDSUPPORT*/

# endif//LCD_WIDTH > 19
    /*lcd.setCursor(LCD_WIDTH - 6, 2);
    lcd.print(LCD_STR_CLOCK[0]);
    if(starttime != 0)
    {
        uint16_t time = millis()/60000 - starttime/60000;
        lcd.print(itostr2(time/60));
        lcd.print(':');
        lcd.print(itostr2(time%60));
    }else{
        lcd_printPGM(PSTR("--:--"));
    }*/
#endif//LCD_HEIGHT>3

    //Status message line on the last line
    lcd.setCursor(0, LCD_HEIGHT - 1);
    lcd.print(lcd_status_message);
}

static void lcd_implementation_error_screen()//function implemented by sagard for error screen
{
  lcd.clear();
  lcd.setCursor(7,1);
  lcd_printPGM(PSTR("ERROR"));
  lcd.setCursor(2,2);
  lcd.print(lcd_status_message);
  delay(1000);
  lcd.noDisplay();
  delay(1000);
  lcd.display();
  delay(1000);
}

  

static void lcd_implementation_drawmenu_generic(uint8_t row, const char* pstr, char pre_char, char post_char)
{
    char c;
    //Use all characters in narrow LCDs
  #if LCD_WIDTH < 20
    	uint8_t n = LCD_WIDTH - 1 - 1;
    #else
    	uint8_t n = LCD_WIDTH - 1 - 2;
  #endif
    lcd.setCursor(0, row);
    lcd.print(pre_char);
    while((c = pgm_read_byte(pstr)) != '\0')
    {
        lcd.print(c);
        pstr++;
        n--;
    }
    while(n--)
        lcd.print(' ');
    lcd.print(post_char);
    lcd.print(' ');
}
static void lcd_implementation_drawmenu_setting_edit_generic(uint8_t row, const char* pstr, char pre_char, char* data)
{
    char c;
    //Use all characters in narrow LCDs
  #if LCD_WIDTH < 20
    	uint8_t n = LCD_WIDTH - 1 - 1 - strlen(data);
    #else
    	uint8_t n = LCD_WIDTH - 1 - 2 - strlen(data);
  #endif
    lcd.setCursor(0, row);
    lcd.print(pre_char);
    while((c = pgm_read_byte(pstr)) != '\0')
    {
        lcd.print(c);
        pstr++;
        n--;
    }
    lcd.print(':');
    while(n--)
        lcd.print(' ');
    lcd.print(data);
}
static void lcd_implementation_drawmenu_setting_edit_generic_P(uint8_t row, const char* pstr, char pre_char, const char* data)
{
    char c;
    //Use all characters in narrow LCDs
  #if LCD_WIDTH < 20
    	uint8_t n = LCD_WIDTH - 1 - 1 - strlen_P(data);
    #else
    	uint8_t n = LCD_WIDTH - 1 - 2 - strlen_P(data);
  #endif
    lcd.setCursor(0, row);
    lcd.print(pre_char);
    while((c = pgm_read_byte(pstr)) != '\0')
    {
        lcd.print(c);
        pstr++;
        n--;
    }
    lcd.print(':');
    while(n--)
        lcd.print(' ');
    lcd_printPGM(data);
}
#define lcd_implementation_drawmenu_setting_edit_int3_selected(row, pstr, pstr2, data, minValue, maxValue) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, '>', itostr3(*(data)))
#define lcd_implementation_drawmenu_setting_edit_int3(row, pstr, pstr2, data, minValue, maxValue) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, ' ', itostr3(*(data)))
#define lcd_implementation_drawmenu_setting_edit_float3_selected(row, pstr, pstr2, data, minValue, maxValue) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, '>', ftostr3(*(data)))
#define lcd_implementation_drawmenu_setting_edit_float3(row, pstr, pstr2, data, minValue, maxValue) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, ' ', ftostr3(*(data)))
#define lcd_implementation_drawmenu_setting_edit_float32_selected(row, pstr, pstr2, data, minValue, maxValue) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, '>', ftostr32(*(data)))
#define lcd_implementation_drawmenu_setting_edit_float32(row, pstr, pstr2, data, minValue, maxValue) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, ' ', ftostr32(*(data)))
#define lcd_implementation_drawmenu_setting_edit_float5_selected(row, pstr, pstr2, data, minValue, maxValue) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, '>', ftostr5(*(data)))
#define lcd_implementation_drawmenu_setting_edit_float5(row, pstr, pstr2, data, minValue, maxValue) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, ' ', ftostr5(*(data)))
#define lcd_implementation_drawmenu_setting_edit_float52_selected(row, pstr, pstr2, data, minValue, maxValue) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, '>', ftostr52(*(data)))
#define lcd_implementation_drawmenu_setting_edit_float52(row, pstr, pstr2, data, minValue, maxValue) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, ' ', ftostr52(*(data)))
#define lcd_implementation_drawmenu_setting_edit_float51_selected(row, pstr, pstr2, data, minValue, maxValue) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, '>', ftostr51(*(data)))
#define lcd_implementation_drawmenu_setting_edit_float51(row, pstr, pstr2, data, minValue, maxValue) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, ' ', ftostr51(*(data)))
#define lcd_implementation_drawmenu_setting_edit_long5_selected(row, pstr, pstr2, data, minValue, maxValue) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, '>', ftostr5(*(data)))
#define lcd_implementation_drawmenu_setting_edit_long5(row, pstr, pstr2, data, minValue, maxValue) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, ' ', ftostr5(*(data)))
#define lcd_implementation_drawmenu_setting_edit_bool_selected(row, pstr, pstr2, data) lcd_implementation_drawmenu_setting_edit_generic_P(row, pstr, '>', (*(data))?PSTR(MSG_ON):PSTR(MSG_OFF))
#define lcd_implementation_drawmenu_setting_edit_bool(row, pstr, pstr2, data) lcd_implementation_drawmenu_setting_edit_generic_P(row, pstr, ' ', (*(data))?PSTR(MSG_ON):PSTR(MSG_OFF))

//Add version for callback functions
#define lcd_implementation_drawmenu_setting_edit_callback_int3_selected(row, pstr, pstr2, data, minValue, maxValue, callback) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, '>', itostr3(*(data)))
#define lcd_implementation_drawmenu_setting_edit_callback_int3(row, pstr, pstr2, data, minValue, maxValue, callback) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, ' ', itostr3(*(data)))
#define lcd_implementation_drawmenu_setting_edit_callback_float3_selected(row, pstr, pstr2, data, minValue, maxValue, callback) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, '>', ftostr3(*(data)))
#define lcd_implementation_drawmenu_setting_edit_callback_float3(row, pstr, pstr2, data, minValue, maxValue, callback) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, ' ', ftostr3(*(data)))
#define lcd_implementation_drawmenu_setting_edit_callback_float32_selected(row, pstr, pstr2, data, minValue, maxValue, callback) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, '>', ftostr32(*(data)))
#define lcd_implementation_drawmenu_setting_edit_callback_float32(row, pstr, pstr2, data, minValue, maxValue, callback) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, ' ', ftostr32(*(data)))
#define lcd_implementation_drawmenu_setting_edit_callback_float5_selected(row, pstr, pstr2, data, minValue, maxValue, callback) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, '>', ftostr5(*(data)))
#define lcd_implementation_drawmenu_setting_edit_callback_float5(row, pstr, pstr2, data, minValue, maxValue, callback) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, ' ', ftostr5(*(data)))
#define lcd_implementation_drawmenu_setting_edit_callback_float52_selected(row, pstr, pstr2, data, minValue, maxValue, callback) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, '>', ftostr52(*(data)))
#define lcd_implementation_drawmenu_setting_edit_callback_float52(row, pstr, pstr2, data, minValue, maxValue, callback) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, ' ', ftostr52(*(data)))
#define lcd_implementation_drawmenu_setting_edit_callback_float51_selected(row, pstr, pstr2, data, minValue, maxValue, callback) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, '>', ftostr51(*(data)))
#define lcd_implementation_drawmenu_setting_edit_callback_float51(row, pstr, pstr2, data, minValue, maxValue, callback) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, ' ', ftostr51(*(data)))
#define lcd_implementation_drawmenu_setting_edit_callback_long5_selected(row, pstr, pstr2, data, minValue, maxValue, callback) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, '>', ftostr5(*(data)))
#define lcd_implementation_drawmenu_setting_edit_callback_long5(row, pstr, pstr2, data, minValue, maxValue, callback) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, ' ', ftostr5(*(data)))
#define lcd_implementation_drawmenu_setting_edit_callback_bool_selected(row, pstr, pstr2, data, callback) lcd_implementation_drawmenu_setting_edit_generic_P(row, pstr, '>', (*(data))?PSTR(MSG_ON):PSTR(MSG_OFF))
#define lcd_implementation_drawmenu_setting_edit_callback_bool(row, pstr, pstr2, data, callback) lcd_implementation_drawmenu_setting_edit_generic_P(row, pstr, ' ', (*(data))?PSTR(MSG_ON):PSTR(MSG_OFF))


void lcd_implementation_drawedit(const char* pstr, char* value)
{
    lcd.setCursor(1, 1);
    lcd_printPGM(pstr);
    lcd.print(':');
   #if LCD_WIDTH < 20
    	lcd.setCursor(LCD_WIDTH - strlen(value), 1);
    #else
    	lcd.setCursor(LCD_WIDTH -1 - strlen(value), 1);
   #endif
    lcd.print(value);
}
static void lcd_implementation_drawmenu_sdfile_selected(uint8_t row, const char* pstr, const char* filename, char* longFilename)
{
    char c;
    uint8_t n = LCD_WIDTH - 1;
    lcd.setCursor(0, row);
    lcd.print('>');
    if (longFilename[0] != '\0')
    {
        filename = longFilename;
        longFilename[LCD_WIDTH-1] = '\0';
    }
    while((c = *filename) != '\0')
    {
        lcd.print(c);
        filename++;
        n--;
    }
    while(n--)
        lcd.print(' ');
}
static void lcd_implementation_drawmenu_sdfile(uint8_t row, const char* pstr, const char* filename, char* longFilename)
{
    char c;
    uint8_t n = LCD_WIDTH - 1;
    lcd.setCursor(0, row);
    lcd.print(' ');
    if (longFilename[0] != '\0')
    {
        filename = longFilename;
        longFilename[LCD_WIDTH-1] = '\0';
    }
    while((c = *filename) != '\0')
    {
        lcd.print(c);
        filename++;
        n--;
    }
    while(n--)
        lcd.print(' ');
}
static void lcd_implementation_drawmenu_sddirectory_selected(uint8_t row, const char* pstr, const char* filename, char* longFilename)
{
    char c;
    uint8_t n = LCD_WIDTH - 2;
    lcd.setCursor(0, row);
    lcd.print('>');
    lcd.print(LCD_STR_FOLDER[0]);
    if (longFilename[0] != '\0')
    {
        filename = longFilename;
        longFilename[LCD_WIDTH-2] = '\0';
    }
    while((c = *filename) != '\0')
    {
        lcd.print(c);
        filename++;
        n--;
    }
    while(n--)
        lcd.print(' ');
}
static void lcd_implementation_drawmenu_sddirectory(uint8_t row, const char* pstr, const char* filename, char* longFilename)
{
    char c;
    uint8_t n = LCD_WIDTH - 2;
    lcd.setCursor(0, row);
    lcd.print(' ');
    lcd.print(LCD_STR_FOLDER[0]);
    if (longFilename[0] != '\0')
    {
        filename = longFilename;
        longFilename[LCD_WIDTH-2] = '\0';
    }
    while((c = *filename) != '\0')
    {
        lcd.print(c);
        filename++;
        n--;
    }
    while(n--)
        lcd.print(' ');
}
#define lcd_implementation_drawmenu_back_selected(row, pstr, data) lcd_implementation_drawmenu_generic(row, pstr, LCD_STR_UPLEVEL[0], LCD_STR_UPLEVEL[0])
#define lcd_implementation_drawmenu_back(row, pstr, data) lcd_implementation_drawmenu_generic(row, pstr, ' ', LCD_STR_UPLEVEL[0])
#define lcd_implementation_drawmenu_submenu_selected(row, pstr, data) lcd_implementation_drawmenu_generic(row, pstr, '>', LCD_STR_ARROW_RIGHT[0])
#define lcd_implementation_drawmenu_submenu(row, pstr, data) lcd_implementation_drawmenu_generic(row, pstr, ' ', LCD_STR_ARROW_RIGHT[0])
#define lcd_implementation_drawmenu_gcode_selected(row, pstr, gcode) lcd_implementation_drawmenu_generic(row, pstr, '>', ' ')
#define lcd_implementation_drawmenu_gcode(row, pstr, gcode) lcd_implementation_drawmenu_generic(row, pstr, ' ', ' ')
#define lcd_implementation_drawmenu_function_selected(row, pstr, data) lcd_implementation_drawmenu_generic(row, pstr, '>', ' ')
#define lcd_implementation_drawmenu_function(row, pstr, data) lcd_implementation_drawmenu_generic(row, pstr, ' ', ' ')

static void lcd_implementation_quick_feedback()
{
#if BEEPER > -1
    SET_OUTPUT(BEEPER);
    for(int8_t i=0;i<10;i++)
    {
		WRITE(BEEPER,HIGH);
		delay(3);
		WRITE(BEEPER,LOW);
		delay(3);
    }
#endif
}
#endif//ULTRA_LCD_IMPLEMENTATION_HITACHI_HD44780_H
