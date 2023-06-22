#include "Utili.h"	
#include "HD44780_LCD_PCF8574.h"


class SchermoClass
{
	protected:
	
	public:
  void init();
  void refresh();
  void ciclo_schermo();
  void alarm();
};

extern SchermoClass Schermo;