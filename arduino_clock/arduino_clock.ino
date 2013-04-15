/*
*********************************************************
* LCD Clock with adjustment buttons
* 
* Simple clock based on the Arduino UNO board 
* and the 2x16 LCD display
*
* You need to download the Time library
* @see http://www.pjrc.com/teensy/td_libs_Time.html
* and add it to your library
* @see http://arduino.cc/en/Guide/Libraries
*
* @date 2013-04-14
*********************************************************
*/


// Required Libraries
#include <Time.h>
#include <LiquidCrystal.h>


// Define button pins
#define BTN_MODE     9
#define BTN_SET_PLUS 8
#define BTN_SET_MIN  7

// Define display modes
#define MODE_DEFAULT      0
#define MODE_SET_HOUR     1
#define MODE_SET_MINUTE   2
#define MODE_SET_DAY      3
#define MODE_SET_MONTH    4
#define MODE_SET_YEAR     5



// Setup the LCD display
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


// The current display mode
int currentMode = 0;


/**
 * Setup the board
 */
void setup() {
  // init putton pins
  pinMode(BTN_MODE, INPUT);
  pinMode(BTN_SET_PLUS, INPUT);
  pinMode(BTN_SET_MIN, INPUT);
  
  // init LCD
  lcd.begin(16, 2);
  
  // set the initial time (2013-01-01 12:00:00)
  setTime(12, 0, 0, 1, 1, 2013);
  
  // Debugging! 
  Serial.begin(9600);
}


/**
 * Controller
 */
void loop() {
  btnModeDetection();
  
  switch(currentMode) {
    case MODE_DEFAULT:
      timePrint();
      break;
      
    default:
      lcdClearLine(0);
      lcdPrintText(0, "Mode : " + String(currentMode));
      break;
  }
  
  delay(100);
}




/******************************************************************
* BUTTON CONTROLS                                                 *
******************************************************************/

/**
 * Detect mode button pressed so we can change the display mode
 *
 * @TODO: build in check to avoid multiple key press detection!
 */
void btnModeDetection() {
  int pressed = digitalRead(BTN_MODE);
  if (pressed != HIGH) {
    return;
  }
  
  currentMode++;
  if (currentMode > 5) {
    currentMode = 0;
  }
}



/******************************************************************
* DATE-TIME HELPERS                                               *
******************************************************************/

/**
 * Print out time & date on the display
 */
void timePrint() {
  String timeDisplay = digitString(hour()) + ':' + digitString(minute()) + ':' + digitString(second());
  String dateDisplay = digitString(day()) + '-' + digitString(month()) + '-' + digitString(year());
  
  //Serial.print(timeDisplay);
  //Serial.println(); 
  
  lcdPrintText(0, timeDisplay);
  lcdPrintText(1, dateDisplay);
}

/**
 * Helper to convert a time/date value to String object
 * It will prepend values lower then ten with a leading 0
 */
String digitString(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  String digitsString = String(digits);
  if(digits < 10) {
    digitsString = "0" + digitsString;
  }
      
  return digitsString;
}




/******************************************************************
* LCD HELPERS                                                     *
******************************************************************/

/**
 * Print the given text to the LCD display
 *
 * @param int lineNum
 *    The line number to write the text to
 * @param String lineText
 *    The text to write to the line
 */
void lcdPrintText(int lineNum, String lineText) {
  lcd.setCursor(0, lineNum);
  lcd.print(lineText);
}

/**
 * Clear the given line number
 *
 * @param int lineNum
 */
void lcdClearLine(int lineNum) {
  lcd.setCursor(0, lineNum);
  lcd.print("                ");
}

