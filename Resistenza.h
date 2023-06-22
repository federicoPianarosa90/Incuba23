// Resistenza.h

#ifndef _RESISTENZA_h
#define _RESISTENZA_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "Utili.h"

class ResistenzaClass
{
	protected:
	float Kpt;
	float Kdt;
	float Kit;
	float errKpt;
	float errKdt;
	float errKit;
  float Kpu;
	float Kdu;
	float Kiu;
	float errKpu;
	float errKdu;
	float errKiu;


	public:
	void init();
	void ciclo_rest(float _t_ref);
	float regolazionet(float *_temp, float _tRef, float _timeLoop, int _lunghezza_t);
  void ciclo_resu(float _u_ref);
	float regolazioneu(float *_umid, float _uRef, float _timeLoop, int _lunghezza_t);
	float calcolaMedia(float *_dataPtr, int _lunghezza);
  int checkWater();
	
	float pwm_rest;
  float pwm_resu;
	int flagAgg_3t;
  int flagAgg_3u;
};

extern ResistenzaClass Resistenza;

#endif
