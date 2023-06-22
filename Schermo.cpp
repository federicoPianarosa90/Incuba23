#include "Schermo.h"	
#include "Utili.h"	
#include "HD44780_LCD_PCF8574.h"
#include "Periodo.h"
#include "Sensore.h"
#include "Resistenza.h"
#include "Memoria.h"

HD44780LCD lcd(2, 16, 0x27);  // Set the LCD I2C address
char buf[16];
char dataT[16];
char dataU[10];
char dataW[6];
char tempo[8];
int flagSchermo;

void SchermoClass::init()
{
  Serial.println("Schermo...");
  lcd.PCF8574_LCDInit(LCDCursorTypeOff);
  lcd.PCF8574_LCDClearScreen();
  lcd.PCF8574_LCDBackLightSet(true);
  lcd.PCF8574_LCDGOTO(1, 0);
  strncpy(buf, "Incuba 23 ", 16);
  lcd.PCF8574_LCDSendString(buf);
  //Serial.print(Memoria.getDay());
  //Serial.print(" H ");
  //Serial.print(Memoria.getHour());
  //Serial.print(" M ");
  //Serial.println(Memoria.getMins());
  sprintf (tempo, "G%d-O%d-M%d", Memoria.getDay(), Memoria.getHour(), Memoria.getMins());
  lcd.PCF8574_LCDGOTO(2, 0);
  lcd.PCF8574_LCDSendString(tempo);
}

void SchermoClass::alarm()
{
  int val = Resistenza.checkWater();
  sprintf(dataW, "W%d", val);
  sprintf (tempo, "%d:%d:%d", Memoria.getDay(), Memoria.getHour(), Memoria.getMins());
}

void SchermoClass::refresh()
{
  alarm();
  flagSchermo = 0;
  float Temp = Sensore.getTMedia()[0];
  Temp = Temp - _CORR_POS_SENSORE;  //correzione data da posizione sensore
  float Umid = Sensore.getUMedia()[0];
  if (Temp <= 0) Temp = 0;
  if (Umid <= 0) Umid = 0;
  int intT = int(Temp);
  int decT = (int(Temp * 100) % 100);
  int intU = int(Umid);
  int decU = (int(Umid * 100) % 100);
  if (decT < 10 ) sprintf (dataT, "T %d.0%d", intT, decT);
  else sprintf (dataT, "T %d.%d", intT, decT);
  if (decU < 10 ) sprintf (dataU, "U %d.0%d", intU, decU);
  else sprintf (dataU, "U %d.%d", intU, decU);
  //Serial.println(dataT);
  //Serial.println(dataU);
  lcd.PCF8574_LCDClearScreen();
  lcd.PCF8574_LCDGOTO(1, 0);
  strncpy(buf, dataT, 16);
  lcd.PCF8574_LCDSendString(buf);
  lcd.PCF8574_LCDGOTO(1, 8);
  strncpy(buf, tempo, 8);
  lcd.PCF8574_LCDSendString(buf);
  lcd.PCF8574_LCDGOTO(2, 0);
  strncpy(buf, dataU, 10);
  lcd.PCF8574_LCDSendString(buf);
  
  lcd.PCF8574_LCDGOTO(2, 12);
  lcd.PCF8574_LCDSendString(dataW);

}

void SchermoClass::ciclo_schermo()
{
  if (Periodo.getSeconds() % PERIOD_SCHERMO == 0 && flagSchermo == 1)
	{
		refresh();
		flagSchermo = 0;
	}
	if (Periodo.getSeconds() % PERIOD_SCHERMO != 0)
	{
		flagSchermo = 1;
	}

}
