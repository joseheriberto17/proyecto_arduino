/*
  Nombre del Archivo: proyecto_arduino.ino
  Descripción: programa que manda una solicitud al esclavo para recibir algunos datos.
   

  Autor: jose heriberto marquez diaz
  Fecha: 30 de diciembre de 2023

  Notas:
  - Ninguna
*/

// ------------------------------------
// Inclusión de Librerías
// ------------------------------------
#include <stdio.h>
#include <Wire.h>
// ------------------------------------
// Definición de Constantes
// ------------------------------------
#define VELOCIDAD_SERIAL 115200

// ------------------------------------
// Variables Globales
// ------------------------------------


// ------------------------------------
// Configuración Inicial
// ------------------------------------
void setup()
{
  Serial.begin(VELOCIDAD_SERIAL);
  Wire.begin();

  pinMode(LED_BUILTIN,OUTPUT);
  
  digitalWrite(LED_BUILTIN,LOW);
}

// ------------------------------------
// Función Principal
// ------------------------------------
void loop()
{
   Wire.requestFrom(8,4);

   while(Wire.available())
   {
      char c = Wire.read();

      Serial.print(c);
   }
   Serial.println();

   delay(1000);
   
}

// ------------------------------------
// Funciónes secundarias
// ------------------------------------
void toogle_pin(uint8_t pin)
{
   if (digitalRead(pin) == LOW)
   {
      digitalWrite(LED_BUILTIN,HIGH);
   }

   if (digitalRead(pin) == HIGH)
   {
      digitalWrite(LED_BUILTIN,LOW);
   }
}