#define EnMR 5
#define MR_A 16
#define MR_B 17

#define MRenc_A 22 // Amarillo
#define MRenc_B 23 // Blanco

// Configurando los parámetros de PWM
const int frecuencia = 5000;

const int canal_R = 1;
const int resolucion = 12;

volatile long L_pulses = 0; 
volatile long R_pulses = 0; 
volatile long CurrentPulses = 0; 
volatile long PreviousPulses = 0; 
volatile long DeltaPulses = 0; 

volatile unsigned CurrentTime = 0;
volatile unsigned PreviousTime = 0;
double DeltaTime = 0;
double freq_R = 0;
double W_R = 0;
double V_R = 0;

float N = 562.0;
float rps;
float WR = 0.0;
float VR = 0.0;
float diameter = 9.0;   //Diametro en cm


//----------setup-------------
void setup() {
  pinMode(EnMR, OUTPUT);
  pinMode(MR_A, OUTPUT);
  pinMode(MR_B, OUTPUT);

  ledcSetup(canal_R, frecuencia, resolucion);
  
  ledcAttachPin(EnMR, canal_R);

  pinMode(MRenc_A, INPUT);    
  pinMode(MRenc_B, INPUT);

  attachInterrupt(MRenc_A, encoderR, RISING);

  Serial.begin(115200);
  
  ledcWrite(canal_R, 4000);
}

//-----------------loop------------------------
void loop() {
  
  Forward();
  speedR();

  
  //Serial.println(freq_R);
  
}


//--------------funciones--------------------
void Forward(){
  ledcWrite(canal_R, 1550);
  digitalWrite(MR_A, LOW);
  digitalWrite(MR_B, HIGH);  
  
  
}

void encoderR(){
  if (digitalRead(MRenc_B) == HIGH){     // si B es HIGH, sentido horario
    R_pulses++ ;        // incrementa POSICION en 1
  }
  else {          // si B es LOW, sentido anti horario
    R_pulses-- ;        // decrementa POSICION en 1
  }

  CurrentPulses = R_pulses;
  
  
}

void speedR(){
  CurrentTime = micros();
  DeltaTime = (double)(CurrentTime - PreviousTime)/1000000.0;
  DeltaPulses = CurrentPulses - PreviousPulses;
  rps = (float)(DeltaPulses/N);
  WR = 2*3.14159265*rps;
  VR = WR * 0.5 * diameter;
  
  if (DeltaTime > 1.0){
    PreviousTime = CurrentTime;
    PreviousPulses = CurrentPulses;
    printValues();
  }
  
  
  
}

void printValues(){
  Serial.print("rps: ");
  Serial.print(rps);
  Serial.print("   WR: ");
  Serial.print(WR);
  Serial.print("  VR: ");
  Serial.println(VR);
  
}
