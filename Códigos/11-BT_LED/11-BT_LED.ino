#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

char dato;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_hersa"); //Bluetooth device name
  pinMode(2,OUTPUT);
}

void loop() {
  if (SerialBT.available()) {
    dato = SerialBT.read();
  
    if (dato == '1'){
      digitalWrite(2,HIGH);
      Serial.println("Encendido");
      SerialBT.println("On");
    }
  
    if (dato == '0'){
      digitalWrite(2,LOW);
      Serial.println("Apagado");
      SerialBT.println("Off");
    }
  }
  delay(100);
}
