

/*
	nome:		 incubatrice 2023
	descrizione: Programma per la gestione e il controllo della nuova incubatrice INCUBA23
				 implementa la gestione del tempo di incubatura e garantisce la continuity
				 nel caso vi sia una interruzione dell'alimentazione dela scheda.
				 non utilizzare su schede diverse da quelle specificate:
				 incuba20_pm versione 1.0.
	marchio:	 __________________
	autore:		 Federico Pianarosa
	data:		 2020/05
	contatto:	 federico.pianarosa90@gmail.com
*/


/*
		per decidere in che modo programmare la scheda di controllo o per inserire una nuova data
		entrare in Utili.h, libreria adibita alle costanti, alle definizioni al settaggio.
*/
//
//pin information here below

/*
  pin 0, 1 reserved Tx Rx
  pin 2	power res Mosfet
  pin 3	power fan Mosfet
  pin 4	<unused
  pin 5	selector b
  pin 6	lux
  pin 7	step umid
  pin 8	dir  umid
  pin 9	step volt
  pin 10 dir volt
  pin 11 selector a
  pin 12	btn a
  pin 13	<unused
  pin A0	<unused
  pin A1 <unused
  pin A2 <finecorsa1
  pin A3 <finecorsa2
  pin A4	sda
  pin A5 sck
  pin A6 variator(if used)
  pin A7 selector b
*/


#include "Utili.h"

// #include "Comandi.h"
#include "Controllo.h"
#include "Memoria.h"
#include "Periodo.h"
#include "Resistenza.h"
#include "Sensore.h"
#include "Schermo.h"
#include "Voltatore.h"

#include <SoftwareSerial.h>
SoftwareSerial NanoToEsp8266Serial(PIN_RX, PIN_TX); //RX4 TX13

#define MSG_BUFFER_SIZE     (29)
#define REF_MSG_BUFFER_SIZE (5)
char refArray[REF_MSG_BUFFER_SIZE] = {'0', '0', 'U', 'T'};
char msgArray[MSG_BUFFER_SIZE] = {0};

int valT = 0;
int valU = 0;
int valTR = 0;
int valUR = 0;
int valP = 0;

float refT, refU;

unsigned long now, old;

char readedByte;

int printedBytes;
int incomingBytes;

/*EX COMANDI CLASS*/
float tempRef1;
float umidRef1;
float tempRef2;
float umidRef2;
int posVasca;
int	basculationDay;
int finishDay;


void setup()
{
	tempRef1  = 37.7 + _CORR_POS_SENSORE;
	umidRef1 = 45.0;
  tempRef2  = 37.5 + _CORR_POS_SENSORE;
	umidRef2 = 55.0;
	posVasca = 0;
	basculationDay = 14;
	finishDay = 22;

  Serial.begin(115200);
  while (!Serial)
  {
    ;
  }
	
  pinMode(RESISTENZA_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);
  //pinMode(VARIATORE, INPUT);
  pinMode(PULSANTE_RESET, INPUT);
  //pinMode(PULSANTE_B, INPUT);
  pinMode(PIN_STEP_UMIDIFICATORE, OUTPUT);
  pinMode(PIN_STEP_VOLTATORE, OUTPUT);
  pinMode(PIN_DIREZIONE_UMIDIFICATORE, OUTPUT);
  pinMode(PIN_DIREZIONE_VOLTATORE, OUTPUT);
  pinMode(PIN_WATERCHECK, INPUT);

  

  Serial.println("starting incuba23...");

  Periodo.init();
  
  //delay(1000);

  Memoria.init();

  Memoria.leggi(0);

 // Comandi.init();

  Controllo.init();

  _uint_16_time_ dati_nuovi[4] = {0};

#ifdef _NUOVI_DATI_MEMORIA
  Serial.println("Reset EEPROM...");
  dati_nuovi[1] = _ORE_INIZIALI / 24;
  dati_nuovi[2] = _ORE_INIZIALI % 24;
  Memoria.scrivi(dati_nuovi, 0);

#endif // _NUOVI_DATI_MEMORIA

  _uint_16_time_ init_Hour_set_time = Memoria.getDay() * 24 + Memoria.getHour();

  Periodo.setTime(init_Hour_set_time);

  Sensore.init();
  
  Resistenza.init();

  Schermo.init();

  Voltatore.init();

}

void loop()
{

  Periodo.aggiorna();

  Memoria.cicloEeprom(0);

  Sensore.leggiSensore();

  if (Periodo.getDay() < basculationDay)
  {
    Resistenza.ciclo_rest(tempRef1);
    Resistenza.ciclo_resu(umidRef1);
    Schermo.ciclo_schermo();
    Voltatore.ciclo_voltatore();
  }
  else if (Periodo.getDay() >= basculationDay && Periodo.getDay() < finishDay)
  {
    Resistenza.ciclo_rest(tempRef2);
    Resistenza.ciclo_resu(umidRef2);
    Schermo.ciclo_schermo();
  }
  else
  {
    Resistenza.ciclo_rest(20.0);
    Resistenza.ciclo_resu(35.0);
  }

  //Comandi.cicloComandi();
}
