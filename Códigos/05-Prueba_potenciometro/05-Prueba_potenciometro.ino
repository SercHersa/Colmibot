#define pot 39

int val;

void setup() {
  Serial.begin(115200);
}

void loop() {
  val = analogRead(pot);
  Serial.print("Valor: ");
  Serial.println(val);
}
