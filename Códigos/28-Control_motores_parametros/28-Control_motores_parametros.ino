#include <math.h>

#define pot 39

#define PI 3.14159265358979323846

#define EnML 15
#define ML_A 2
#define ML_B 4

#define EnMR 5
#define MR_A 16
#define MR_B 17

#define MLenc_A 21 // Amarillo
#define MLenc_B 19 // Blanco
#define MRenc_A 22 // Amarillo
#define MRenc_B 23 // Blanco

// Configurando los parámetros de PWM
const int frecuencia = 10000;
const int canal_L = 0;
const int canal_R = 1;
const int resolucion = 12;
const int PWMmax = 4095;

int LDirection = 0;
int RDirection = 0;


volatile long L_pulses = 0; 
volatile long R_pulses = 0; 

volatile long CurrentPulsesL = 0; 
volatile long PreviousPulsesL = 0; 
volatile long DeltaPulsesL = 0; 

volatile long CurrentPulsesR = 0; 
volatile long PreviousPulsesR = 0; 
volatile long DeltaPulsesR = 0; 

volatile unsigned CurrentTime = 0;
volatile unsigned PreviousTime = 0;
double DeltaTime = 0;

float rps_L;
float WL = 0.0;
float VL = 0.0;

float rps_R;
float WR = 0.0;
float VR = 0.0;

float DC, DL, DR;
float x = 0.0;
float y = 0.0;
float phi = 0.0;
float thetha = 0.0;

//----------variables del robot
const float N = 562.0;
const float diameter = 7.0;   //Diametro en cm
const float L = 17.5;
float V = 0;
float W = 0;

//-------variables para el control
float xd = 0.0;
float yd = 0.0;
float phid = 0.0;

float ePhi = 0;
float ex = 0;
float ey = 0;

float kp = 100;

int velL;
int velR;

int estado = 0;



//----------setup-------------
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

  pinMode(MLenc_A, INPUT);    
  pinMode(MLenc_B, INPUT);
  
  pinMode(MRenc_A, INPUT);    
  pinMode(MRenc_B, INPUT);

  attachInterrupt(MLenc_A, encoderL, RISING);
  attachInterrupt(MRenc_A, encoderR, RISING);

  Serial.begin(115200);

}

//-----------------loop------------------------
void loop() {
  //control(90.0,90.0);
  switch(estado){

  case 0:
    //Serial.println("Estado 0");
    control(90.0,0.0);
    if (x > 85 && x < 95 && y > -5 && y < 5){
      estado = 1;  
    }
    
    break;

  case 1:
    //Serial.println("Estado 1");
    control(90.0,-90.0);
    if (x > 85 && x < 95 && y > -95 && y < -85){
      estado = 3;
    }
    break;

  case 2:
    //Serial.println("Estado 2");
    control(0.0,-90.0);
    if (x > -5 && x < 5 && y > -95 && y < -85){
      estado = 4;
    }
    break;
    
  case 3:
    //Serial.println("Estado 3");
    control(0.0,0.0);
    if (x > -5 && x < 5 && y > -5 && y < 5){
      estado = 4;
    }
    break;
    
  case 4:
    //Serial.println("Estado 4");
    driveRobot(0,0);
    break;
  }

  
  //delay(5000);
  //control(90.0,170.0);
  //delay(5000);
  //xd = 90.0;
  //yd = 90.0;
  
  
  
  
  
  
  
//vel = analogRead(pot);
  
  
  
//  Serial.println(frecuencia);
  
}


//--------------funciones--------------------
void driveRobot(float LSignal, float RSignal){
  //-----------Motor izquierdo---------
  if (LSignal < 0){ 
    LDirection = -1;
  }
  else if (LSignal > 0){ 
    LDirection = 1;
  }
  else {
    LDirection = 0;
  }

  if (LDirection == -1){
    digitalWrite(ML_A, HIGH);
    digitalWrite(ML_B, LOW);
  }
  else if (LDirection == 1){
    digitalWrite(ML_A, LOW);
    digitalWrite(ML_B, HIGH);
  }
  else {
    digitalWrite(ML_A, LOW);
    digitalWrite(ML_B, LOW);
  }
  
  //------------Motor derecho-----------
  if (RSignal < 0){ 
    RDirection = -1;
  }
  else if (RSignal > 0){ 
    RDirection = 1;
  }
  else {
    RDirection = 0;
  }

  if (RDirection == -1){
    digitalWrite(MR_A, HIGH);
    digitalWrite(MR_B, LOW);
  }
  else if (RDirection == 1){
    digitalWrite(MR_A, LOW);
    digitalWrite(MR_B, HIGH);
  }
  else {
    digitalWrite(ML_A, LOW);
    digitalWrite(ML_B, LOW);
  }

  if (LSignal > PWMmax) LSignal = PWMmax;
  if (LSignal < -PWMmax) LSignal = -PWMmax;
  if (RSignal > PWMmax) RSignal = PWMmax;
  if (RSignal < -PWMmax) RSignal = -PWMmax;

  if (abs(ex) < 5 && abs(ey) < 5){
    ledcWrite(canal_L, 0);
    ledcWrite(canal_R, 0);
  }
  else {
    ledcWrite(canal_L, abs(LSignal));
    ledcWrite(canal_R, abs(RSignal));
  }

  Serial.print(LSignal);
  Serial.print(" , ");
  Serial.println(RSignal);


  
}


void Forward(){
  digitalWrite(ML_A, LOW);
  digitalWrite(ML_B, HIGH);
  digitalWrite(MR_A, LOW);
  digitalWrite(MR_B, HIGH);  
}

void Back(){
  digitalWrite(ML_A, HIGH);
  digitalWrite(ML_B, LOW); 
  digitalWrite(MR_A, HIGH);
  digitalWrite(MR_B, LOW);
}

void Stop(){
  digitalWrite(ML_A, LOW);
  digitalWrite(ML_B, LOW);
  digitalWrite(MR_A, LOW);
  digitalWrite(MR_B, LOW);
}

void encoderL(){
  if (digitalRead(MLenc_B) == HIGH){     // si B es HIGH, sentido horario
    L_pulses++ ;        // incrementa POSICION en 1
  }
  else {          // si B es LOW, sentido anti horario
    L_pulses-- ;        // decrementa POSICION en 1
  }

  CurrentPulsesL = L_pulses;
}

void encoderR(){
  if (digitalRead(MRenc_B) == HIGH){     // si B es HIGH, sentido horario
    R_pulses-- ;        // incrementa POSICION en 1
  }
  else {          // si B es LOW, sentido anti horario
    R_pulses++ ;        // decrementa POSICION en 1
  }

  CurrentPulsesR = R_pulses;
}

void speeds(){
  CurrentTime = micros();
  //Se divide entre 100,000 para tener la lectura cada 0.1 segundos
  DeltaTime = (double)(CurrentTime - PreviousTime)/100000.0; 
  
  DeltaPulsesR = CurrentPulsesR - PreviousPulsesR;
  rps_R = 10*(float)(DeltaPulsesR/N);
  WR = 2 * PI * rps_R;
  VR = WR * 0.5 * diameter;

  DeltaPulsesL = CurrentPulsesL - PreviousPulsesL;
  rps_L = 10*(float)(DeltaPulsesL/N);
  WL = 2 * PI * rps_L;
  VL = WL * 0.5 * diameter;
  
  if (DeltaTime > 1.0){
    PreviousTime = CurrentTime;
    PreviousPulsesR = CurrentPulsesR;
    PreviousPulsesL = CurrentPulsesL;
    printValues();
    odometria();
    
  }
  
}

void odometria(){
  //Distancia recorrida rueda izquierda
  DL = PI * diameter * (float)(DeltaPulsesL/N);

  //Distancia recorrida rueda izquierda
  DR = PI * diameter * (float)(DeltaPulsesR/N);
  
  //Distancia del robot
  DC = (DR + DL)/2;

  //Ecuaciones 
  x = x + DC * cos(phi);
  y = y + DC * sin(phi);

  phi = phi + ((DR - DL)/L);
  phi = atan2(sin(phi),cos(phi));
  thetha = phi/PI *180;
}

void control(float xp, float yp){
  speeds();
  //V = (VL + VR)/2;
  V = 2800;
  ex = xp - x;
  ey = yp - y;
  phid = atan2(ey,ex);
  ePhi = phid-phi;
  W = (VL-VR)/L + kp *ePhi;
  velL = V - (W*L)/2;
  velR = V + (W*L)/2;

  driveRobot(velL, velR);
  
  
}

void printValues(){
  Serial.print("ex: ");
  Serial.print(ex);

  Serial.print("  x: ");
  Serial.print(x);

  Serial.print("  ey: ");
  Serial.print(ey);
  
  Serial.print("  y: ");
  Serial.print(y);
  
  Serial.print("   VelL: ");
  Serial.print(velL);
  
  Serial.print("  VelR: ");
  Serial.print(velR);

  Serial.print("  Thetha: ");
  Serial.print(thetha);
  
  Serial.print("  phi: ");
  Serial.println(phi);
  
}
