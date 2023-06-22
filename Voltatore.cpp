#include "Voltatore.h"
#include "Controllo.h"
#include "Periodo.h"

void VoltatoreClass::init()
{
  Serial.println("Voltatore...");
	flagVolt_1 = 0;
	direzione = 0;
	#ifdef _FINE_CORSA_VOLTATORE
	pinMode(PIN_FINE_CORSA_VOLTATORE, INPUT);
  Serial.println("Riposizionamento...");
  delay(100);
	while (digitalRead(PIN_FINE_CORSA_VOLTATORE))
	{
		//Serial.println("attendere riposizionamento");
		Controllo.stepToDoV += 100;
		delay(20);
	}
	
	#else
	
	while (!(Comandi.checkA(true)))
	{
/*
		SchermoC.setCursor(0, 1);
		SchermoC.print("sx? b inverte");
*/
		Serial.println("� tutto a sx? premere b per invertire");
		Controllo.stepToDoV += 100;
		delay(200);
		if (Comandi.checkB(true))
		{
			if (direzione == 0)
			{
				direzione = 1;
			}
			else direzione = 0;
		}
	}
	
#endif // _FINE_CORSA_VOLTATORE

	actualPos = 0;
	stepToDo = 0;
	Controllo.stepToDoV = 0;
	Controllo.stepDoneV = 0;
}

void VoltatoreClass::aggiorna()
{
	if (Periodo.getSeconds() % PERIOD_VOLTATA == 0 && flagVolt_1 == 1)
	{
		if (direzione == 0)
		{
			direzione =	1;
			actualPos = 0;
		}
		else
		{
			direzione = 0;
			actualPos = 1;
		}
		stepToDo = STEP_VOLTATA;											//carica max 64000 step
		flagVolt_1 = 0;
	}
	if (Periodo.getSeconds() % PERIOD_VOLTATA != 0)
	{
		flagVolt_1 = 1;
	}
}

void VoltatoreClass::ciclo_voltatore()
{
	aggiorna();
	Controllo.stepToDoV = stepToDo;
	if (Controllo.stepToDoV - Controllo.stepDoneV == 0)//
	{	
// 		unsigned char oldSreg;
// 		oldSreg = SREG;
// 		cli();						//necessario bloccare le ISR per permettere di azzerare con sicurezza le comande
		Controllo.stepDoneV = 0;
		Controllo.stepToDoV = 0;
// 		sei();
// 		SREG = oldSreg;
		stepToDo = 0;
	}
}

VoltatoreClass Voltatore;
