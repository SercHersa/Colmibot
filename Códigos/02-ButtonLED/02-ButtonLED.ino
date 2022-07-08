#define BTN 0
#define LED 2

bool buttonState;

void setup() {
  pinMode(BTN,INPUT);
  pinMode(LED,OUTPUT);
}

void loop() {
  buttonState = digitalRead(BTN);
  
  if (buttonState == 0){
    digitalWrite(LED,HIGH);
  }
  
  else {
    digitalWrite(LED,LOW);
  }
}
