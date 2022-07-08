#define LED 18
#define pot 39

int brillo = 4095;
int canal = 0;
int frec = 1000;
int res = 12;
int val;

void setup() {
  Serial.begin(115200);
  
  ledcAttachPin(LED, canal); 
  ledcSetup(canal, frec, res); 
}

void loop() {
  val = analogRead(pot);
  Serial.print("Valor: ");
  Serial.println(val);
  ledcWrite(0, val); 
}
