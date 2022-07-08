0#define LED_L 33
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

//--------------------setup----------------
void setup() {
  pinMode(LED_L, OUTPUT);
  pinMode(LED_F, OUTPUT);
  pinMode(LED_R, OUTPUT);
  
  pinMode(trigPin_L, OUTPUT);   // Se define el pin trigger como SALIDA
  pinMode(echoPin_L, INPUT);    // Se define el pin echo como entrada
  pinMode(trigPin_F, OUTPUT);   // Se define el pin trigger como SALIDA
  pinMode(echoPin_F, INPUT);    // Se define el pin echo como entrada
  pinMode(trigPin_R, OUTPUT);   // Se define el pin trigger como SALIDA
  pinMode(echoPin_R, INPUT);    // Se define el pin echo como entrada
  
  Serial.begin(115200);       // Se inicializa la comunicación Serial del la 
                              //   ESP32 a 115,200 baudios
}

void loop() {
  US_left();
  US_front();
  US_right();
  
  Serial.print("L: ");
  Serial.print(dist_L);
  Serial.print("  F: ");
  Serial.print(dist_F);
  Serial.print("  R: ");
  Serial.println(dist_R);
}

//----------funciones------------

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

  if(dist_F < 7){
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
