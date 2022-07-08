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
int vel;

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

float N = 562.0;
float diameter = 7.0;   //Diametro en cm

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
float L = 17.5;


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

  if (x > -90){
    Back();
  }
  else {
    Stop();
  }
  
  speeds();
  
vel = analogRead(pot);
  
  ledcWrite(canal_L, vel);//1550);
  ledcWrite(canal_R, vel);//2550);
  
//  Serial.println(frecuencia);
  
}


//--------------funciones--------------------
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

void printValues(){
//  Serial.print("rps_L: ");
//  Serial.print(rps_L);
//
//  Serial.print("  WL: ");
//  Serial.print(WL);
//
//  Serial.print("  Delta: ");
//  Serial.print(DeltaPulsesL);
//  
//  Serial.print("  DC: ");
//  Serial.print(DC);
  
  Serial.print("  X: ");
  Serial.print(x);
  
  Serial.print("  y: ");
  Serial.println(y);

  //Serial.print("  Thetha: ");
  //Serial.println(thetha);
  
//  Serial.print("  phi: ");
//  Serial.println(phi);
  
}
