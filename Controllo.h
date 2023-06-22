// Controllo.h

#ifndef _CONTROLLO_h
#define _CONTROLLO_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Utili.h"

class ControlloClass
{
	protected:
	

	public:
	void init();
	int ctrl_Volt();
	int ctrl_T();
	int ctrl_U();
	
	unsigned int contatoreOVF;
	float pwm_t;
	float pwm_u;
	float val_step;
	int stepDoneU;
	int stepDoneV;
	int stepToDoU;
	unsigned int stepToDoV;
	unsigned int flagStepDone;
	int flagStepDone2;
};

extern ControlloClass Controllo;

#endif
