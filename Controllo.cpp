//
//
//
#include <Arduino.h>
#include "Controllo.h"
#include "Voltatore.h"

#include "Resistenza.h"
#include "Utili.h"


void ControlloClass::init()
{
  /*
  	TCCR0A &= 0x00;
  	TCCR0B &= 0x00;
  	OCR0A &= 0x00;
  	TIMSK0 &= 0x00;
   	TIFR0 &= 0x00;
  */
  Serial.println("Controllo...");

  unsigned char oldSreg;
  oldSreg = SREG;
  cli();
  TCCR0A |= 1 << WGM01;
  TCCR0B |= 1 << CS00;
  TCCR0B |= 1 << CS01;
  //TCCR0B |= 1<<CS02;
  OCR0A |= 0xFF;			//0xca 5kHz ma ogni ciclo dura circa 9 ms da cui minimo 0x20
  TCNT0 |= 0x00;
  TIMSK0 |= 1 << OCIE0A;	//per attivare l'IRS del comparatore 0A
  sei();
  SREG = oldSreg;

  contatoreOVF = 0;
  val_step = 1.5;
  pwm_t = 0.5;
  pwm_u = 0.5;
  stepDoneU = 0;
  stepDoneV = 0;
  stepToDoU = 0;
  stepToDoV = 0;
  flagStepDone = 1;
  flagStepDone2 = 1;
}


int ControlloClass::ctrl_T()
{
  if (contatoreOVF % PERIOD_PWM_RES < PERIOD_PWM_RES * pwm_t)
  {
    return 0;
  }
  else return 1;
}

int ControlloClass::ctrl_U()
{
  if (contatoreOVF % PERIOD_PWM_FAN < PERIOD_PWM_FAN * pwm_u)
  {
    return 0;
  }
  else return 1;
}

int ControlloClass::ctrl_Volt()
{
  if (contatoreOVF % PERIOD_STEP_VOLTATA < PERIOD_STEP_VOLTATA / 2 && stepDoneV < stepToDoV)
  {
    if (flagStepDone2)
    {
      stepDoneV++;
      flagStepDone2 = 0;
    }
    return 1;
  }
  else if (contatoreOVF % PERIOD_STEP_VOLTATA < PERIOD_STEP_VOLTATA / 2 && flagStepDone2 == 0)
  {
    flagStepDone2 = 0;
    return 1;
  }
  else
  {
    flagStepDone2 = 1;
    return 0;
  }
}


ControlloClass Controllo;
