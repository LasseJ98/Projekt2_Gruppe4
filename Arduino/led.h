/******************************************
* "LED.H"                                 *
* Header file for "Mega2560 LED driver"   *
* Henning Hargaard, 25/10 2016            *
*******************************************/ 
void initLEDport();
void writeAllLEDs(unsigned char pattern);
void turnOnLED(unsigned char led_nr);
void turnOffLED(unsigned char led_nr);
void toggleLED(unsigned char led_nr);
/******************************************/
