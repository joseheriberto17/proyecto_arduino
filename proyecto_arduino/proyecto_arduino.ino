/*
  Nombre del Archivo: proyecto_arduino.ino
  Descripción: programa que recopila las capacidades mas intersante del arduino uno.
    secuencia de led de tre colores

  Autor: jose heriberto marquez diaz
  Fecha: 5 de diciembre de 2024

  Notas:
  - Arduino CLI, librerias por definir
*/

// ------------------------------------
// Inclusión de Librerías
// ------------------------------------
#include <stdio.h>
// ------------------------------------
// Definición de Constantes
// ------------------------------------
#define PIN_LED 13
#define PIN_LED_1 5
#define PIN_LED_2 6
#define PIN_LED_3 9
#define PIN_LED_4 10
#define PIN_LED_5 11
#define PIN_BUTTON_1 2
#define PIN_BUTTON_2 3


#define VELOCIDAD_SERIAL 9600

// ------------------------------------
// Variables Globales
// ------------------------------------

// secuencia led
uint8_t counter_led = 0;
uint8_t dir_led = 0; 
uint8_t size_led = 4;
uint8_t stop = 0;

//intesidad del led
uint8_t power_led = 255;

unsigned long sample_time = 500;

// configuracion de la secuencia led
uint16_t gpio_pins[4] = {PIN_LED_1, PIN_LED_2, PIN_LED_3,PIN_LED_4};
const uint8_t M_LED[4][4] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};

//interrupcciones
// pin 3
void toogle_dir(){
  toogle_data(dir_led);
  delay(100);
}

void toogle_stop(){
  toogle_data(stop);
  delay(100);
}
// ------------------------------------
// Configuración Inicial
// ------------------------------------
void setup()
{
  Serial.begin(VELOCIDAD_SERIAL);

  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_LED_1, OUTPUT);
  pinMode(PIN_LED_2, OUTPUT);
  pinMode(PIN_LED_3, OUTPUT);
  pinMode(PIN_LED_4, OUTPUT);
  pinMode(PIN_LED_5, OUTPUT);
  
  pinMode(PIN_BUTTON_1,INPUT_PULLUP);
  pinMode(PIN_BUTTON_2,INPUT_PULLUP);

  digitalWrite(PIN_LED_1, LOW); // Enciende el LED
  digitalWrite(PIN_LED_2, LOW); // Enciende el LED
  digitalWrite(PIN_LED_3, LOW); // Enciende el LED
  digitalWrite(PIN_LED_4, LOW); // Enciende el LED

  attachInterrupt(digitalPinToInterrupt(2),toogle_dir,RISING);
  attachInterrupt(digitalPinToInterrupt(3),toogle_stop,RISING);

  // tiempo para que no se dispare la interrupcciones
  delay(1000);
  stop = 0;
  dir_led = 0;
}

// ------------------------------------
// Función Principal
// ------------------------------------
void loop()
{
  // Código principal del programa
  
  if (stop == 0)
  {
    counter_led++;   
  } 
    if (counter_led == 4)
    {
      counter_led = 0;
    }
    for (int i = 0; i < 4; ++i)
    {
      //control de la secuencia de leds
      analogWrite(gpio_pins[i], power_led*(M_LED[counter_led][(dir_led==0)? (i):(-i + size_led-1)]));
    }
    analogWrite(PIN_LED_5,power_led);
    delay(sample_time);
  
}

// ------------------------------------
// Funciónes secundarias
// ------------------------------------
void Toogle_led(uint8_t pin)
{
  if (digitalRead(pin) == 0)
  {
    digitalWrite(pin, 1);
  }
  else
  {
    digitalWrite(pin, 0);
  }
}

void toogle_data(uint8_t &variable){
	if (variable == 1) {
		variable = 0;
	} else {
		variable = 1;
	}
}

void serialEvent() {
  if (Serial.available() > 0)
  {
    // recoge los datos del serial
    String dataString = Serial.readStringUntil('\n');
    Serial.println("comando  recibido: " + dataString);
    
    // extraccion de letra y numero
    char letra;
    int numero;
    char data[10];
    dataString.toCharArray(data,dataString.length()+1);
    sscanf(data,"%c%d",&letra,&numero);

    Serial.print("letra: ");
    Serial.println(letra);
    Serial.print("numero: ");
    Serial.println(numero);

    //interpretacion los datos

    switch (letra)
    {
    case 'w':
      dir_led = 0;
      Serial.println("direccion: adelante");
      break;
    case 's':
      dir_led = 1;
      Serial.println("direccion: atras");
      break;
    case 't':
      sample_time = numero;
      Serial.print("muestreo: ");
      Serial.println(sample_time);
      break;
    case 'p':
      power_led = numero;
      Serial.print("potencia: ");
      Serial.println(power_led);
      break;
    case 'x':
      if (stop == 1) 
      {
        stop = 0;
      } 
      else 
      {
        stop = 1;
      }
      Serial.print("stop: ");
      Serial.println(stop);      
      break;

    default:
      break;
    }
  }
}

