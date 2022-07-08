#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#define LED_BLUE 2
#define LED_GREEN 33
#define LED_RED 32
#define LED_YELLOW 18

BluetoothSerial SerialBT;

char dato;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ColmiBoT"); //Bluetooth device name
  pinMode(LED_BLUE,OUTPUT);
  pinMode(LED_GREEN,OUTPUT);
  pinMode(LED_RED,OUTPUT);
  pinMode(LED_YELLOW,OUTPUT);
}

void loop() {
  if (SerialBT.available()) {
    dato = SerialBT.read();
  
    if (dato == '0'){
      digitalWrite(LED_BLUE,HIGH);
      digitalWrite(LED_GREEN,LOW);
      digitalWrite(LED_RED,LOW);
      digitalWrite(LED_YELLOW,LOW);
      Serial.println("AZUL");
      SerialBT.println("AZUL");
    }
  
    if (dato == '1'){
      digitalWrite(LED_BLUE,LOW);
      digitalWrite(LED_GREEN,HIGH);
      digitalWrite(LED_RED,LOW);
      digitalWrite(LED_YELLOW,LOW);
      Serial.println("VERDE");
      SerialBT.println("VERDE");
    }

    if (dato == '2'){
      digitalWrite(LED_BLUE,LOW);
      digitalWrite(LED_GREEN,LOW);
      digitalWrite(LED_RED,HIGH);
      digitalWrite(LED_YELLOW,LOW);
      Serial.println("ROJO");
      SerialBT.println("ROJO");
    }

    if (dato == '3'){
      digitalWrite(LED_BLUE,LOW);
      digitalWrite(LED_GREEN,LOW);
      digitalWrite(LED_RED,LOW);
      digitalWrite(LED_YELLOW,HIGH);
      Serial.println("AMARILLO");
      SerialBT.println("AMARILLO");
    }

    if (dato == '4'){
      digitalWrite(LED_BLUE,LOW);
      digitalWrite(LED_GREEN,LOW);
      digitalWrite(LED_RED,LOW);
      digitalWrite(LED_YELLOW,LOW);
      Serial.println("APAGADOS");
      SerialBT.println("APAGADOS");
    }
  }
  delay(100);
}
