// 
// 
// 
#include <Arduino.h>
#include "Utili.h"
#include "Controllo.h"

#include "Voltatore.h"


ISR(TIMER0_COMPA_vect)
{
	unsigned int oldSreg = SREG;
	cli();
	OCR0A |= _OCI0A_VAL_;
	Controllo.contatoreOVF++;
	digitalWrite(RESISTENZA_PIN, Controllo.ctrl_T());
	digitalWrite(FAN_PIN, Controllo.ctrl_U());
	digitalWrite(PIN_STEP_VOLTATORE, Controllo.ctrl_Volt());
	digitalWrite(PIN_DIREZIONE_VOLTATORE, Voltatore.direzione);
	sei();
	SREG = oldSreg;
}
