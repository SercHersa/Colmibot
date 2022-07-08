#define echoPin 12//25//27 //12
#define trigPin 13//26//14 //13

// Variables
long duration;                // Variable para guardar la duración del viaje 
                              //   de la onda de sonido
int distance;                 // Variable para la medición de la distancia

void setup() {
  pinMode(trigPin, OUTPUT);   // Se define el pin trigger como SALIDA
  pinMode(echoPin, INPUT);    // Se define el pin echo como entrada
  
  Serial.begin(115200);       // Se inicializa la comunicación Serial del la 
                              //   ESP32 a 115,200 baudios
}

void loop() {
  US_front();
  
  // Mostramos en el monitor serial la distancia en centímetros
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
}

int US_front(){
  // Se pone en bajo el pin de trigger de inicio
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Se pone en alto el pin de Trigger por 10 microsecondos
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Se lee el pin de Echo, con el cual guardaremos el tiempo en microsegundos 
  //   del viaje de la onda de sonido
  duration = pulseIn(echoPin, HIGH);
  
  // Calculamos la distancia
  distance = duration * 0.0343 / 2;     // La velocidad del sonido en cm/Us dividido 
                                        // entre 2 (ida y vuelta)
  return distance;
}
