//
//
//
#include <Arduino.h>
#include "Periodo.h"
#include "Sensore.h"

#include <Wire.h>
#include "Utili.h"


int U_msb, U_lsb, U_checksum;
int T_msb, T_lsb, T_checksum;
unsigned int U_data, T_data;
float U_rel, T_in;


void SensoreClass::init()
{
  Serial.println("Sensore...");
  T_vettore[0] = {0.0};
  U_vettore[0] = {0.0};
  T_media[0] = {0.0};
  U_media[0] = {0.0};
  flagAgg_2 = 1;
  U_msb = 0;
  U_lsb = 0;
  U_checksum = 0;
  T_msb = 0;
  T_lsb = 0;
  T_checksum = 0;
  U_data = 0;
  T_data = 0;
  U_rel = 0.0;
  T_in = 0.0;
  Wire.begin();
}


float* SensoreClass::getTemp() {
  return T_vettore;
}

float* SensoreClass::getUmid() {
  return U_vettore;
}

float* SensoreClass::getTMedia() {
  return T_media;
}

float* SensoreClass::getUMedia() {
  return U_media;
}



void SensoreClass::leggiSensore() {
  if (Periodo.getSeconds() % PERIODO_SENSORE == 0 && flagAgg_2)
  {
    //Serial.println("inizio lettura");
    if (1)
    {
      //Wire.begin();
      Wire.beginTransmission(SENSORE_ADDRESS);
      Wire.write(SENS_FIRST_CONN);
      Wire.write(SENS_SECOND_CONN);
      Wire.endTransmission();

      Wire.requestFrom(SENSORE_ADDRESS, 6);
      if (Wire.available() > 0)
      {
        U_msb = Wire.read();
        U_lsb = Wire.read();
        U_checksum = Wire.read();
        T_msb = Wire.read();
        T_lsb = Wire.read();
        T_checksum = Wire.read();
      }
      //      U_msb = Wire.read();
      //      U_lsb = Wire.read();
      //      U_checksum = Wire.read();
      //      T_msb = Wire.read();
      //      T_lsb = Wire.read();
      //      T_checksum = Wire.read();

      U_data = U_msb << 8;
      U_data |= U_lsb;

      T_data = T_msb << 8;
      T_data |= T_lsb;

      U_rel = (float) 100.0 * U_data / DIVISORE_DATA;
      T_in = (float) - 45.0 + 175.0 * T_data / DIVISORE_DATA;

      /*
        Serial.print("temperatura ");
        Serial.print(T_in);
        Serial.print("	umidity ");
        Serial.println(U_rel);
      */

      for (int i = LUNGHEZZA_VETTORE - 1; i >= 1; --i) {
        T_vettore[i] = T_vettore[i - 1];
        T_media[i] = T_media[i - 1];
        U_vettore[i] = U_vettore[i - 1];
        U_media[i] = U_media[i - 1];
      }

      T_vettore[0] = T_in;
      U_vettore[0] = U_rel;

      T_media[0] = calcolaMedia(T_vettore, LUNGHEZZA_VETTORE);
      U_media[0] = calcolaMedia(U_vettore, LUNGHEZZA_VETTORE);
      //aggiornamento();
      flagAgg_2 = 0;
    }
    else
    {
      //			Serial.println("---------------");
      //			Serial.println("lettura fallita");
      //			Serial.println("---------------");
    }
  }
  if (Periodo.getSeconds() % PERIODO_SENSORE != 0)
  {
    flagAgg_2 = 1;
  }
}


float calcolaMedia(float *_dataPtr, int _lunghezza) {
  float somma = 0;
  for (int i = 0; i < _lunghezza; ++i) {
    somma += _dataPtr[i];
  }
  return somma / _lunghezza;
}

void SensoreClass::lettura()
{
  if (1)
  {
    //Wire.begin();
    Wire.beginTransmission(SENSORE_ADDRESS);
    Wire.write(SENS_FIRST_CONN);
    Wire.write(SENS_SECOND_CONN);
    Wire.endTransmission();

    Wire.requestFrom(SENSORE_ADDRESS, 6);
    if (Wire.available() > 0)
    {
      U_msb = Wire.read();
      U_lsb = Wire.read();
      U_checksum = Wire.read();
      T_msb = Wire.read();
      T_lsb = Wire.read();
      T_checksum = Wire.read();
    }

    U_data = U_msb << 8;
    U_data |= U_lsb;

    T_data = T_msb << 8;
    T_data |= T_lsb;

    U_rel = (float) 100.0 * U_data / DIVISORE_DATA;
    T_in = (float) - 45.0 + 175.0 * T_data / DIVISORE_DATA;

    
      Serial.print("temperatura ");
      Serial.print(T_in);
      Serial.print("	umidity ");
      Serial.println(U_rel);
    

    for (int i = LUNGHEZZA_VETTORE - 1; i >= 1; --i) {
      T_vettore[i] = T_vettore[i - 1];
      T_media[i] = T_media[i - 1];
      U_vettore[i] = U_vettore[i - 1];
      U_media[i] = U_media[i - 1];
    }

    T_vettore[0] = T_in;
    U_vettore[0] = U_rel;

    T_media[0] = calcolaMedia(T_vettore, LUNGHEZZA_VETTORE);
    U_media[0] = calcolaMedia(U_vettore, LUNGHEZZA_VETTORE);
    flagAgg_2 = 0;
  }
  else
  {
    //		Serial.println("---------------");
    //		Serial.println("lettura fallita");
    //		Serial.println("---------------");
  }

}

SensoreClass Sensore;
