#define EnML 15
#define ML_A 2
#define ML_B 4

#define EnMR 5
#define MR_A 16
#define MR_B 17

#define pot 39

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
}

void loop() {
  Forward();
  delay(2000);

  Right();
  delay(2000);
  
  Back();
  delay(2000);

  Left();
  delay(2000);
  
  Stop();
  delay(1000);
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
