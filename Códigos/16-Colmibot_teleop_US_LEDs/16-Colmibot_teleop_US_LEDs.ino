#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#define EnML 15
#define ML_A 2
#define ML_B 4

#define EnMR 5
#define MR_A 16
#define MR_B 17

#define pot 39

#define LED_L 33
#define LED_F 32
#define LED_R 18

#define echoPin_L 12 
#define trigPin_L 13 

#define echoPin_F 27 
#define trigPin_F 14 

#define echoPin_R 25 
#define trigPin_R 26 

// Variables
long duration_L;
long duration_F;
long duration_R;

int dist_L;
int dist_F;
int dist_R;

BluetoothSerial SerialBT;

char dato;
bool activacion = false;

// Configurando los parámetros de PWM
const int frecuencia = 500;
const int canal_L = 0;
const int canal_R = 1;
const int resolucion = 12;

int vel = 0;

void setup() {
  pinMode(EnML, OUTPUT);
  pinMode(ML_A, OUTPUT);
  pinMode(ML_B, OUTPUT);

  pinMode(EnMR, OUTPUT);
  pinMode(MR_A, OUTPUT);
  pinMode(MR_B, OUTPUT);
  
  ledcSetup(canal_L, frecuencia, resolucion);
  ledcSetup(canal_R, frecuencia, resolucion);
  
  ledcAttachPin(EnML, canal_L);
  ledcAttachPin(EnMR, canal_R);

  Serial.begin(115200);
  SerialBT.begin("ColmiBoT"); //Bluetooth device name
  
  pinMode(LED_L, OUTPUT);
  pinMode(LED_F, OUTPUT);
  pinMode(LED_R, OUTPUT);
  
  pinMode(trigPin_L, OUTPUT);   // Se define el pin trigger como SALIDA
  pinMode(echoPin_L, INPUT);    // Se define el pin echo como entrada
  pinMode(trigPin_F, OUTPUT);   // Se define el pin trigger como SALIDA
  pinMode(echoPin_F, INPUT);    // Se define el pin echo como entrada
  pinMode(trigPin_R, OUTPUT);   // Se define el pin trigger como SALIDA
  pinMode(echoPin_R, INPUT);    // Se define el pin echo como entrada
}

//-----------------loop----------------
void loop() {
  if (SerialBT.available()) {
    dato = SerialBT.read();
  
    if (dato == '0'){
      Stop();
    }
  
    if (dato == '1'){
      Forward();
    }

    if (dato == '2'){
      Right();
    }

    if (dato == '3'){
      Back();
    }

    if (dato == '4'){
      Left();
    }

    if (dato == '5'){
      Automatico();
    }
  }
  US_left();
  US_front();
  US_right();
}

//------------------Funciones----------------

void Forward(){
  vel = analogRead(pot);
  ledcWrite(canal_L, vel);
  ledcWrite(canal_R, vel);
  
  digitalWrite(ML_A, LOW);
  digitalWrite(ML_B, HIGH);
  digitalWrite(MR_A, LOW);
  digitalWrite(MR_B, HIGH);  
  Serial.println("Forward");
}

void Back(){
  vel = analogRead(pot);
  ledcWrite(canal_L, vel);
  ledcWrite(canal_R, vel);
  
  digitalWrite(ML_A, HIGH);
  digitalWrite(ML_B, LOW); 
  digitalWrite(MR_A, HIGH);
  digitalWrite(MR_B, LOW); 
  Serial.println("Back");
}

void Stop(){
  digitalWrite(ML_A, LOW);
  digitalWrite(ML_B, LOW);
  digitalWrite(MR_A, LOW);
  digitalWrite(MR_B, LOW);
  Serial.println("Stopped");  
}

void Right(){
  vel = analogRead(pot);
  ledcWrite(canal_L, 0.75*vel);
  ledcWrite(canal_R, 0.75*vel);
  
  digitalWrite(ML_A, LOW);
  digitalWrite(ML_B, HIGH);
  digitalWrite(MR_A, HIGH);
  digitalWrite(MR_B, LOW);  
  Serial.println("Right");
}

void Left(){
  vel = analogRead(pot);
  ledcWrite(canal_L, 0.75*vel);
  ledcWrite(canal_R, 0.75*vel);
  
  digitalWrite(ML_A, HIGH);
  digitalWrite(ML_B, LOW);
  digitalWrite(MR_A, LOW);
  digitalWrite(MR_B, HIGH);  
  Serial.println("Left");
}

int US_left(){
  digitalWrite(trigPin_L, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin_L, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_L, LOW);
  
  duration_L = pulseIn(echoPin_L, HIGH);
  dist_L = duration_L * 0.0343 / 2;

  if(dist_L < 7){
    digitalWrite(LED_L, HIGH);
  }
  else digitalWrite(LED_L, LOW);
  
  return dist_L;
}

int US_front(){
  digitalWrite(trigPin_F, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin_F, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_F, LOW);
  
  duration_F = pulseIn(echoPin_F, HIGH);
  dist_F = duration_F * 0.0343 / 2;

  if(dist_F < 10){
    digitalWrite(LED_F, HIGH);
  }
  else digitalWrite(LED_F, LOW);
  
  return dist_F;
}

int US_right(){
  digitalWrite(trigPin_R, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin_R, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_R, LOW);
  
  duration_R = pulseIn(echoPin_R, HIGH);
  dist_R = duration_R * 0.0343 / 2;

  if(dist_R < 7){
    digitalWrite(LED_R, HIGH);
  }
  else digitalWrite(LED_R, LOW);
  
  return dist_R;
}

void Automatico(){
  digitalWrite(LED_L, HIGH);
  digitalWrite(LED_F, HIGH);
  digitalWrite(LED_R, HIGH);
  
}
