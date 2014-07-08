/*
 Added by Liuji Shang
 */

#include "Arduino.h"

#include "Si7021.h"
#include <Wire.h>

Si7021::Si7021()
{
  _last_temperature = 0.0;
}

bool Si7021::detectSensor( )
{
  byte temp;
  int i;
  byte deviceID;

  delay( 10);									

  Wire.beginTransmission( SI7021_ADR );
  Wire.write(0xFA);
  Wire.write(0x0F);
  Wire.endTransmission( false );	

  Wire.requestFrom(SI7021_ADR, 8);
  while(Wire.available()<8)
  {;;}
  
  i = 0;
  while(i<8)
  {
     temp = Wire.read();
     i++;
  }
  Wire.endTransmission( );
  
  Wire.beginTransmission( SI7021_ADR );
  Wire.write(0xFC);
  Wire.write(0xC9);
  Wire.endTransmission( false );	

  Wire.requestFrom(SI7021_ADR, 6);
  while(Wire.available()<6)
  {;;}

  i = 0;
  deviceID = Wire.read();
  while(i < 5)
  {
    temp = Wire.read();
    i++;
  }
  Wire.endTransmission( );

  
  if ( deviceID == ID_SI7021)
  {
	return true ;
  }
  else
  {
    return false ;
  }
}

unsigned int Si7021::_tempMeasurement()
{
  unsigned int rawData;
  delay(10);
  Wire.beginTransmission( SI7021_ADR );
  Wire.write(0xE3);
  Wire.endTransmission( false );							
  Wire.requestFrom( SI7021_ADR, 2);
  while ( Wire.available( ) < 2 )					
  {;;}
  
  rawData = ( Wire.read() << 8 );					
  rawData |= Wire.read( );						
  Wire.endTransmission( );	
  return rawData;
}

unsigned int Si7021::_RHMeasurement()
{
  unsigned int rawData;
  delay(10);
  Wire.beginTransmission( SI7021_ADR );
  Wire.write(0xE5);
  Wire.endTransmission( false );							
  Wire.requestFrom( SI7021_ADR, 2);
  while ( Wire.available( ) < 2 )					
  {;;}
  
  rawData = ( Wire.read() << 8 );					
  rawData |= Wire.read( );							
  Wire.endTransmission( );	
  return rawData;
}

float Si7021::getTemperature( )
{
  float rawTemperature;

  rawTemperature = _tempMeasurement();
  _last_temperature = ( rawTemperature * TEMPERATURE_MULTIPLE) / TEMPERATURE_SLOPE- TEMPERATURE_OFFSET;

  return _last_temperature;
}

float Si7021::getHumidity( )
{
  float rawHumidity, curve, linearHumidity;

  rawHumidity = _RHMeasurement( );
  linearHumidity = (rawHumidity * HUMIDITY_MULTIPLE) / HUMIDITY_SLOPE - HUMIDITY_OFFSET;

  return linearHumidity;
}