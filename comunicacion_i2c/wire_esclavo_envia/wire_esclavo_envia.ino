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
  Wire.begin(8);
  Wire.onRequest(Respuesta);

  pinMode(LED_BUILTIN,OUTPUT);
  
  digitalWrite(LED_BUILTIN,LOW);
}

// ------------------------------------
// Función Principal
// ------------------------------------
void loop()
{
  

   while(Wire.available())
   {
      char c = Wire.read();

      Serial.print(c);
   }
   
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

void Respuesta()
{
   String dataToSend = "Hola_desde_el_dispositivo_esclav";
  
   // Enviar los datos al Maestro
   Wire.write(dataToSend.c_str());
   Serial.println("datos enviado");
}