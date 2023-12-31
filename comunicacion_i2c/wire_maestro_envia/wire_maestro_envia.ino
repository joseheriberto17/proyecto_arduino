/*
  Nombre del Archivo: wire_maestro_write.ino
  Descripción: programa que realiza una comunicacion i2c entre 2 arduinos 

  Autor: jose heriberto marquez diaz
  Fecha: 5 de diciembre de 2024

  Notas:
  - Arduino CLI, librerias por definir
*/

#include <Wire.h>

const int16_t I2C_SLAVE = 0x08;
uint8_t num = 0; 

void setup()
{
    Serial.begin(115200);

    // definicion como maestro
    Wire.begin();
    pinMode(13,OUTPUT);
    digitalWrite(13,LOW);
}

void loop()
{
    
    Wire.beginTransmission(I2C_SLAVE);
    Wire.write("12a");    
    num = Wire.endTransmission();
    delay(1000);
    toogle(13);
}

void toogle(uint8_t pin){
    if (digitalRead(pin)==0)
    {
        digitalWrite(pin,HIGH);
    }
    else
    {
        digitalWrite(pin,LOW);
    }
}