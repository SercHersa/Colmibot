#define LED_L 33
#define LED_F 32
#define LED_R 18

void setup() {
  pinMode(LED_L, OUTPUT);
  pinMode(LED_F, OUTPUT);
  pinMode(LED_R, OUTPUT);
}


void loop() {
  digitalWrite(LED_L, HIGH);
  digitalWrite(LED_F, HIGH);
  digitalWrite(LED_R, HIGH);
  delay(1000);
  digitalWrite(LED_L, LOW);
  digitalWrite(LED_F, LOW);
  digitalWrite(LED_R, LOW);
  delay(1000);
}
