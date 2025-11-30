 int IR1=18;
int IR2=19;
int LED1=21;
int LDR=25;
int sense=0;
void setup() {
  pinMode(LED1,OUTPUT);
  pinMode(IR1,INPUT);
  pinMode(IR2,INPUT);
  pinMode(LDR,INPUT);
  Serial.begin(9600);
  }
 
 
 
 void loop(){
   int ldr = analogRead(25);
  // Serial.println(ldr);
  int firstir = digitalRead(IR1);
  int secondir = digitalRead(IR2);
  // Serial.print(firstir);
  //   Serial.print("    ");
  // Serial.println(secondir);
  if (ldr < 2000) {
    analogWrite(LED1, 0);
    Serial.println(" day   ");
  } else {
    
    if ((firstir == 0) && (sense == 1)) {
      analogWrite(LED1, 250);
      sense = 2;
      Serial.println(" ir1   ");
    }
    if ((secondir == 0) && (sense == 2)) {
      analogWrite(LED1, 5);
      Serial.println(" ir2   ");
      sense = 0;
    }
    if (sense == 0) {
      analogWrite(LED1, 5);
      Serial.println(" night   ");
      sense = 1;
    }
  }
 
Serial.print("    ");
    Serial.println(sense);
  delay(300);
 }
