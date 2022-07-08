#define EnML 13
#define ML_A 12
#define ML_B 14

// Configurando los parámetros de PWM
const int frecuencia = 8000;
const int canal = 0;
const int resolucion = 12;
int vel = 4095;

void setup() {
  pinMode(EnML, OUTPUT);
  pinMode(ML_A, OUTPUT);
  pinMode(ML_B, OUTPUT);
  
  ledcSetup(canal, frecuencia, resolucion);
  
  ledcAttachPin(EnML, canal);

  ledcWrite(canal, vel);
  
  Serial.begin(115200);
}

void loop() {
  Forward();
  delay(2000);

  Stop();
  delay(1000);

  Back();
  delay(2000);

  Stop();
  delay(1000);
}

void Forward(){
  digitalWrite(ML_A, LOW);
  digitalWrite(ML_B, HIGH); 
  Serial.println("Forward");
}

void Back(){
  digitalWrite(ML_A, HIGH);
  digitalWrite(ML_B, LOW); 
  Serial.println("Back");
}

void Stop(){
  digitalWrite(ML_A, LOW);
  digitalWrite(ML_B, LOW);
  Serial.println("Stopped");  
}
