#include "Wire.h"

int num=0;

void setup() {
  
  Wire.begin(8); // Inicia la comunicación I2C y asigna la dirección 10 al Arduino esclavo

  // Establece la función de devolución de llamada para manejar eventos de recepción
  Wire.onReceive(receiveEvent);
  Serial.begin(115200);
}

void loop() {
  delay(500);
}

// callback del i2c cuando recibe datos disponibles por interrucion
void receiveEvent(int datos) {

  while (Wire.available()) {
    char c = Wire.read();
    Serial.print(c);
  }
  Serial.println(); // Salto de línea después de imprimir los datos recibidos
}
