#define LED 18

int brillo = 1023;
int canal = 0;
int frec = 1000;
int res = 10;

void setup() {
  //Asignamos un canal al pin del LED
  //Hay 16 canales, del 0 al 15
  ledcAttachPin(LED, canal); 
  
  // Configuramos los canales
  // ledcSetup(canal, frecuencia, bits_de_resolucíon);
  // canales 0-15, 12 kHz, resolución 1-16 bits, frecuencia límite dependerá de la resolución
  ledcSetup(canal, frec, res); 
}

void loop() {
  ledcWrite(canal, 0); 
  delay(1000);
  ledcWrite(canal, 1000); 
  delay(1000);
  ledcWrite(canal, 2000); 
  delay(1000);
  ledcWrite(canal, brillo); 
  delay(1000);
}
