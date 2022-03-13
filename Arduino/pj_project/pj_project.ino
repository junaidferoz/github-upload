int IRsensor=2;
int LED=9;
void setup() {
  pinMode(8,INPUT);
  pinMode(LED,OUTPUT);
  Serial.begin(9600); //initialise serial monitor
  pinMode(IRsensor,INPUT);
}

void loop() {
  int temp=digitalRead(8);
  int stat=digitalRead(IRsensor);//assign value of LDR sensor to a temporary variable
  Serial.println("Intensity="); //print on serial monitor using ""
  Serial.println(temp);         //display output on serial monitor
  delay(300);
  if(temp==HIGH){
      digitalWrite(LED,LOW); //if light is not present,LED on
  }      
  else if(temp==LOW){
    if(stat==HIGH){
      digitalWrite(LED,HIGH);
    }
  }
}
