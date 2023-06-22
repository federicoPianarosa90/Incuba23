//
//

#include "Sensore.h"
#include "Controllo.h"
#include "Resistenza.h"

#include "Voltatore.h"
#include "Periodo.h"

#include "Memoria.h"
#include "Utili.h"


void ResistenzaClass::init()
{
  Serial.println("Resistenze...");
  Kpt = 150.0;
  Kdt = 8000.0;
  Kit = 0.015;
  errKpt = 1.0;
  errKdt = 1.0;
  errKit = 1.0;
  Kpu = 150.0;
  Kdu = 8000.0;
  Kiu = 0.015;
  errKpu = 1.0;
  errKdu = 1.0;
  errKiu = 1.0;
  flagAgg_3t = 1;
  flagAgg_3u = 1;
  for (int a = 0; a < LUNGHEZZA_VETTORE * 2; a++)
  {
    //Serial.println("lettura");
    Sensore.lettura();
    pwm_rest = regolazionet(Sensore.getTMedia(), 37.7, PERIODO_SENSORE, LUNGHEZZA_VETTORE);
    pwm_resu = regolazioneu(Sensore.getUMedia(), 50.0, PERIODO_SENSORE, LUNGHEZZA_VETTORE);
  }
}


void ResistenzaClass::ciclo_rest(float _t_ref)
{
  if (Periodo.getSeconds() % PERIODO_SENSORE == 0 && flagAgg_3t)
  {
    //Serial.println(Periodo.getSeconds());
    pwm_rest = regolazionet(Sensore.getTMedia(), _t_ref, PERIODO_SENSORE, LUNGHEZZA_VETTORE);

    flagAgg_3t = 0;
  }
  if (Periodo.getSeconds() % PERIODO_SENSORE == 1)
  {
    flagAgg_3t = 1;
  }
  Controllo.pwm_t = pwm_rest;
}

void ResistenzaClass::ciclo_resu(float _u_ref)
{
  if (Periodo.getSeconds() % PERIODO_SENSORE == 0 && flagAgg_3u)
  {
    //Serial.println(Periodo.getSeconds());
    pwm_resu = regolazioneu(Sensore.getUMedia(), _u_ref, PERIODO_SENSORE, LUNGHEZZA_VETTORE);

    flagAgg_3u = 0;
  }
  if (Periodo.getSeconds() % PERIODO_SENSORE == 1)
  {
    flagAgg_3u = 1;
  }
  Controllo.pwm_u = pwm_resu;
}


float ResistenzaClass::regolazionet(float *_temp, float _tRef, float _timeLoop, int _lunghezza_t) {

  float err[_lunghezza_t];
  float err_der[_lunghezza_t - 1];
  float err_int[_lunghezza_t - 1];


  for (int a = 0; a < _lunghezza_t; ++a)
  {
    err[a] = _tRef - _temp[a];
  }

  errKpt = calcolaMedia(err, _lunghezza_t);

  for (int a = 0; a < _lunghezza_t - 1; ++a)
  {
    err_der[a] = (err[a] - err[a + 1]) / _timeLoop;
    err_int[a] = (err[a] + err[a + 1]) / 2.0 * _timeLoop;
  }

  errKdt = calcolaMedia(err_der, 3);
  errKit += calcolaMedia(err_int, _lunghezza_t - 1);

  float valueReturned = Kpt * errKpt + Kdt * errKdt + Kit * errKit;

  if (valueReturned > 50.0) valueReturned = 50.0;
  if (valueReturned < -50.0) valueReturned = - 50.0;

  float valueMapped = ((float) map(valueReturned, -50.0, 50.0, 0.0, 1000.0)) / 1000.0;

  //Serial.print("E prop * kpt ");
  //Serial.println(errKpu * Kpt);
  //Serial.print("E der * kdt ");
  //Serial.println(errKdu * Kdt);
  //Serial.print("E int * kit ");
  //Serial.println(errKiu * Kit);
  //Serial.print("datiMem: D ");
  //Serial.print(Memoria.getDay());
  //Serial.print(" H ");
  //Serial.print(Memoria.getHour());
  //Serial.print(" M ");
  //Serial.println(Memoria.getMins());

  //Serial.print("datiPer: D ");
  //Serial.print(Periodo.getDay());
  //Serial.print(" H ");
  //Serial.print(Periodo.getHour());
  //Serial.print(" M ");
  //Serial.println(Periodo.getMins());

  //Serial.print("T ref ");
  //Serial.println(_tRef);
  //Serial.print("T media ");
  //Serial.println(_tRef - errKpu);
  //Serial.print("value for the resistor T");
  //Serial.println(valueMapped);

  return valueMapped;
}

float ResistenzaClass::regolazioneu(float *_umid, float _uRef, float _timeLoop, int _lunghezza_t) {

  float err[_lunghezza_t];
  float err_der[_lunghezza_t - 1];
  float err_int[_lunghezza_t - 1];
  

  for (int a = 0; a < _lunghezza_t; ++a)
  {
    err[a] = _uRef - _umid[a];
  }

  errKpu = calcolaMedia(err, _lunghezza_t);

  for (int a = 0; a < _lunghezza_t - 1; ++a)
  {
    err_der[a] = (err[a] - err[a + 1]) / _timeLoop;
    err_int[a] = (err[a] + err[a + 1]) / 2.0 * _timeLoop;
  }

  errKdu = calcolaMedia(err_der, 3);
  errKiu += calcolaMedia(err_int, _lunghezza_t - 1);

  float valueReturned = Kpu * errKpu + Kdu * errKdu + Kiu * errKiu;

  if (valueReturned > 50.0) valueReturned = 50.0;
  if (valueReturned < -50.0) valueReturned = - 50.0;

  float valueMapped = ((float) map(valueReturned, -50.0, 50.0, 0.0, 1000.0)) / 1000.0;
  if (checkWater() <= ALARM_LEVEL) 
  {
    valueMapped = 0;
  }

  //Serial.print("E prop * kpu ");
  //Serial.println(errKpu * Kpu);
  //Serial.print("E der * kdu ");
  //Serial.println(errKdu * Kdu);
  //Serial.print("E int * kiu ");
  //Serial.println(errKiu * Kiu);
  //Serial.print("datiMem: D ");

  //Serial.print("u ref ");
  //Serial.println(_uRef);
  //Serial.print("u media ");
  //Serial.println(_uRef - errKpu);
  //Serial.print("value for the resistor U");
  //Serial.println(valueMapped);

  return valueMapped;
}

float ResistenzaClass::calcolaMedia(float *_dataPtr, int _lunghezza) {
  float somma = 0;
  for (int i = 0; i < _lunghezza; ++i) {
    somma += _dataPtr[i];
  }
  return somma / _lunghezza;
}

int ResistenzaClass::checkWater() {
  int cwval = analogRead(PIN_WATERCHECK);
  char buf[8];
  sprintf(buf, "W %d", cwval);
  //Serial.println(buf);
  return cwval;
}


ResistenzaClass Resistenza;
