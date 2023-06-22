/*
classe:		MemoriaClass
visibile:	Memoria
autore:		Federico Pianarosa
data:		02/10/2019
consente l'accesso alla memoria EEPROM integrata per il ciclo di scrittura e lettura di 4 byte raffiguranti i dati di incubazione;

0)	minuti trascorsi allo scoccare dell'ora
1)	giorni trascorsi dall'inizio del periodo di incubazione;
2)	ore trascorse dall'inizio del giorno di incubazione;
3)	prossima posizione nella memoria
*/

#include "Utili.h"
#include "Periodo.h"
#include "Memoria.h"

#include <EEPROM.h>

//metodo di inizializzazione del processo e ripristino dati temporali
/*lettura eeprom indirizzo 0, se indirizzo 0 gi� compilato continua la lettura fino a che indicizzazione == 0,
leggi ultimo indirizzo (indirizzo - 4) */

void MemoriaClass::init()
{
  Serial.println("Memoria...");
	newData[0] = {0};
	data[0] = {0};
	flagAgg_2 = 1;

  if(!digitalRead(PULSANTE_RESET)) resetMem();

	leggi(0);
	
	while (posMem != 0)
	{
		leggi(posMem);
	}
}

void MemoriaClass::scrivi(_uint_16_time_ _data[], int _indirizzo)
{
// 	unsigned int oldSreg = SREG;
// 	cli();
	for(int i = 0; i < 4; ++i){
// 		Serial.println("scrittura eeprom");
		EEPROM.write(_indirizzo + i, _data[i]);
		data[i] = _data[i];
	}
// 	sei();
// 	SREG = oldSreg;
}

void MemoriaClass::leggi(int _indirizzo)
{
	unsigned int oldSreg = SREG;
	cli();
	for(int i = 0; i < 4; ++i){
		data[i] = EEPROM.read(_indirizzo + i);
	}
	SREG = oldSreg;
	sei();
	
}

void MemoriaClass::resetMem()
{
  _uint_16_time_ dati_nuovi[4] = {0};

  dati_nuovi[1] = _ORE_INIZIALI / 24;
  dati_nuovi[2] = _ORE_INIZIALI % 24;

  Memoria.scrivi(dati_nuovi, 0);
}

_uint_16_time_ MemoriaClass::getMins()
{
	return data[3];
}

_uint_16_time_ MemoriaClass::getHour()
{
	return data[2];
}

_uint_16_time_ MemoriaClass::getDay()
{
	return data[1];
}

_uint_16_time_ MemoriaClass::getMP()
{
	return data[0];
}

int MemoriaClass::cicloEeprom(const int _indirizzo)
{
	//lettura e scrittura della memoria eeprom per continuit�
	if (Periodo.getSeconds() % PERIODO_MEM_REFRESH == 0 && flagAgg_2 == 0)
	{

		posMem = _indirizzo;	//indicizzazione prossimo indirizzo da compilare nella memoria eeprom
		
		newData[0] = posMem;
		newData[1] = Periodo.getDay();
		newData[2] = Periodo.getHour() % 24;
		newData[3] = Periodo.getMins() % 60;
						// prossima posizione memoria
		Memoria.scrivi(newData, _indirizzo);
		flagAgg_2 = 1;
		return posMem;
	}
	if (Periodo.getSeconds() % PERIODO_MEM_REFRESH != 0)
	{
		flagAgg_2 = 0;
		return posMem;
	}
}

MemoriaClass Memoria;
