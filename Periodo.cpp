
#include "Periodo.h"
#include "Utili.h"

void PeriodoClass::init()
{
  Serial.println("Periodo...");
	days = 0;
	initHours = 0;
	hours = 0;
	minuts = 0;
}

void PeriodoClass::setTime(const _uint_16_time_ _initHours)
{
	initHours = _initHours;
}

_uint_16_time_ PeriodoClass::getTimeInitHours()
{
	return initHours;
}

void PeriodoClass::aggiorna()
{
	seconds = millis() / 1000;
	minuts = seconds / SECONDI_MINUTO;
	hours = initHours + minuts / MINUTI_ORE;
	days = hours / ORE_GIORNO;
}


_uint_32_time_ PeriodoClass::getTimeMills()
{
	return (_uint_32_time_)(millis());
}


_uint_16_time_ PeriodoClass::getMins()
{
	return minuts;
}

_uint_32_time_ PeriodoClass::getSeconds()
{
	return seconds;
}


_uint_16_time_ PeriodoClass::getHour()
{
	return hours;
}


_uint_16_time_ PeriodoClass::getDay()
{
	return days;
}

PeriodoClass Periodo;
