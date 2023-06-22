#include "Utili.h"

class VoltatoreClass
{
	protected:


	public:
	void init();
	void aggiorna();
	void ciclo_voltatore();
	
	int direzione;
	unsigned int stepToDo;
	int flagVolt_1;
	int actualPos;
};

extern VoltatoreClass Voltatore;
