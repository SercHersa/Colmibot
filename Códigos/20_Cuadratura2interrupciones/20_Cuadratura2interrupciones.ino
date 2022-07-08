#define MLenc_A 21 // Amarillo
#define MLenc_B 19 // Blanco
#define MRenc_A 22 // Amarillo
#define MRenc_B 23 // Blanco  

volatile int left = 0; 
volatile int right = 0; 
        
void setup() {
  pinMode(MLenc_A, INPUT);    
  pinMode(MLenc_B, INPUT);  
  
  pinMode(MRenc_A, INPUT);    
  pinMode(MRenc_B, INPUT);    

  Serial.begin(115200);   

  attachInterrupt(MLenc_A, encoderL, RISING);
  attachInterrupt(MRenc_A, encoderR, RISING);
}


void loop() {
    Serial.print(left); 
    Serial.print("   "); 
    Serial.println(right); 
}

void encoderL(){
  
    if (digitalRead(MLenc_B) == HIGH)     // si B es HIGH, sentido horario
    {
      left++ ;        // incrementa POSICION en 1
    }
    else {          // si B es LOW, sentido anti horario
      left-- ;        // decrementa POSICION en 1
    }
}    

void encoderR(){
  
    if (digitalRead(MRenc_B) == HIGH)     // si B es HIGH, sentido horario
    {
      right-- ;        // incrementa POSICION en 1
    }
    else {          // si B es LOW, sentido anti horario
      right++ ;        // decrementa POSICION en 1
    }    
}
    
    
  
