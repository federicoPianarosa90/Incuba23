// Utili.h

#ifndef _UTILI_h
#define _UTILI_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif


// per immettere in memoria una data prestabilita scommentare sotto, la definizione
// avvia una chiamata al metodo di scrittura memoria eeprom nella fase di inizializzazione
// altrimenti la normale lettura della memoria eeprom avvia la lettura di continuit�.
// la memoria � azzerabile dal menu comandi una volta avviata la macchina, non conviene
// pertanto azzerare la memoria da  qui

/************************************************************************/
//#define _NUOVI_DATI_MEMORIA
/************************************************************************/

// il fine corsa 2 pu� essere utilizzato per la gestione del voltatore,
// scommentare sotto se si vuole utilizzarlo in questo modo.
// l'altro metodo prevede l'utilizzo del secondo finecorsa per la gestione
// della vasca di umidificazione interna.

/************************************************************************/
#define _FINE_CORSA_VOLTATORE
/************************************************************************/

/************************************************************************/
#define _FINE_CORSA_UMIDIFICATORE
/************************************************************************/

// se il selettore � un variatore, allora scommentare sotto e commentare  la
// definizione _SWITCH_MODE

/************************************************************************/
//#define _VARIATORE_MODE
/************************************************************************/

// la definizione sotto va commentata se si utilizza il variatore
//

/************************************************************************/
#define _SWITCH_MODE
/************************************************************************/


//
//	costanti

#define _OCI0A_VAL_				0x60

#define _ORE_INIZIALI			  0
#define _CORR_POS_SENSORE		0.6

#define MILLIS_AGG				200
#define MICRO_DELAY				500
#define RESOLUTION_SW			60

#define PERIOD_STEP_VOLTATA		30
#define PERIOD_STEP_UMID		8//4
#define PERIOD_PWM_RES			20
#define PERIOD_PWM_FAN			20

#define PERIODO_MEM_REFRESH		2000
#define LUNGH_VECT_MEM			4

#define SECONDI_ORA				3600
#define ORE_GIORNO				24
#define SECONDI_MINUTO			60
#define MINUTI_ORE				60

#define SCHERMO_ADDRESS			0x27
#define MAX_COLONNE				16
#define MAX_RIGHE				2

#define SENSORE_ADDRESS			112
#define SENS_FIRST_CONN			0x5C
#define SENS_SECOND_CONN		0x24
#define LUNGHEZZA_VETTORE		6
#define DIVISORE_DATA			65536
#define PERIODO_SENSORE			3
#define PERIODO_U           60

#define REGOLATION_STEP_NUM		30
#define POS_MAX_STEP_NUM		9000
#define POS_MIN_STEP_NUM		0
#define RESOLUTION_CTRL_VAL		10

#define PERIOD_VOLTATA			3600
#define STEP_VOLTATA			1600//portare uova a sx

#define PERIOD_SCHERMO      5
#define ALARM_LEVEL         100

//
//	pinout

#define PULSANTE_A						  12
#define PULSANTE_B						  A7
#define VARIATORE						    A6
#define SWITCH_A_PIN					  11
#define SWITCH_B_PIN					  5
#define LUX_PIN							    6
#define PIN_STEP_UMIDIFICATORE			  7
#define PIN_DIREZIONE_UMIDIFICATORE		8
#define PIN_STEP_VOLTATORE				    9
#define PIN_DIREZIONE_VOLTATORE	10
#define	RESISTENZA_PIN					2
#define	FAN_PIN							    3
#define	FINECORSA1_PIN					A2
#define	FINECORSA2_PIN					A3
#define PIN_ALLERT						  A2
#define PIN_MAX_UMIDIFICATOR		A3
#define PIN_WATERCHECK			    A7
#define PIN_GALLEGGIANTE        4
#define PIN_RX                  4
#define PIN_TX                  13
#define PULSANTE_RESET					A3

#ifdef _FINE_CORSA_VOLTATORE

#define PIN_FINE_CORSA_VOLTATORE		A2

#endif // _FINE_CORSA_VOLTATORE

//
//metodi utili


#endif
