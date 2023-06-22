// Periodo.h

#ifndef _PERIODO_h
#define _PERIODO_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "Utili.h"

typedef unsigned long _uint_32_time_;
typedef unsigned int _uint_16_time_;

class PeriodoClass
{
	protected:
	_uint_32_time_ oldMills;
	_uint_32_time_ seconds;
	_uint_16_time_ initHours;
	_uint_16_time_ hours;
	_uint_16_time_ days;
	_uint_16_time_ minuts;

	public:
	void init();
	void aggiorna();
	void setTime(const _uint_16_time_ _initHours);
	
	_uint_16_time_ getTimeInitHours();
	
	_uint_16_time_ getMins();
	_uint_16_time_ getHour();
	_uint_16_time_ getDay();
	
	_uint_32_time_ getSeconds();
	_uint_32_time_ getTimeMills();
	
};

extern PeriodoClass Periodo;

#endif
