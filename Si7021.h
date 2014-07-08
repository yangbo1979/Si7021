/*
 Added by Liuji Shang
 */
 
#ifndef SI7021_H
#define SI7021_H

#include "Arduino.h"

/* Si7021 CMD Code */
#define Measure_RH_M      0xE5
#define Measure_RH_NM     0xF5
#define Measure_T_M       0xE3
#define Measure_T_M       0xF3
#define Read_Temp_RH      0xE0
#define RESET             0xFE
#define Write_RH_T_REG    0xE6
#define Read_RH_T_REG     0xE7
#define Read_ID_1_1       0xFA
#define Read_ID_1_2       0x0F
#define Read_ID_2_1       0xFC
#define Read_ID_2_2       0xC9
#define Read_Rev_1        0x84
#define Read_Rev_2        0xB8

/* ID Register */
#define ID_SI7021         0x15

#define WAKE_UP_TIME      15
#define SI7021_ADR        0x40

/* Coefficients */
#define TEMPERATURE_OFFSET   46.85
#define TEMPERATURE_MULTIPLE 175.72
#define TEMPERATURE_SLOPE    65536
#define HUMIDITY_OFFSET      6
#define HUMIDITY_MULTIPLE    125
#define HUMIDITY_SLOPE       65536



class Si7021
{
 public:
  Si7021();
  bool  detectSensor( );
  float getTemperature( );
  float getHumidity( );
  
 private:
  float _last_temperature;
  unsigned int _tempMeasurement();
  unsigned int _RHMeasurement();

};
#endif  // SI7021_H