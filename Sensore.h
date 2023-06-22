// Sensore.h


#include "Utili.h"	

float calcolaMedia(float *_dataPtr, int _lunghezza);

class SensoreClass
{
	protected:
	float T_vettore[LUNGHEZZA_VETTORE];
	float U_vettore[LUNGHEZZA_VETTORE];
	float T_media[LUNGHEZZA_VETTORE];
	float U_media[LUNGHEZZA_VETTORE];

	public:
	void init();
	void lettura();
	void leggiSensore();
	float* getTemp();
	float* getUmid();
	float* getTMedia();
	float* getUMedia();
	
	int flagAgg_2;
};

extern SensoreClass Sensore;


