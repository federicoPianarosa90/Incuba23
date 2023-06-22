// Memoria.h

#ifndef _MEMORIA_h
#define _MEMORIA_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "Utili.h"
#include "Periodo.h"
#include <EEPROM.h>


class MemoriaClass
{
	protected:
	
	_uint_16_time_ data[LUNGH_VECT_MEM];
	_uint_16_time_ newData[LUNGH_VECT_MEM];

	public:
		
	_uint_16_time_ posMem;
	int flagAgg_2;
	void init();
	void scrivi(_uint_16_time_ _data[], int _indirizzo);
	void leggi(int _indirizzo);
  void resetMem();
	
	_uint_16_time_ getMins();
	_uint_16_time_ getHour();
	_uint_16_time_ getDay();
	_uint_16_time_ getMP();
	
	int cicloEeprom(const int _indirizzo);

};

extern MemoriaClass Memoria;

#endif
