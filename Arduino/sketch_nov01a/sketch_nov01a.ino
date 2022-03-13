void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  float pwm=201;
  float duty=pwm/255;
  Serial.println(duty);
  float rpm=duty*100*500;
  Serial.println(rpm);
  delay(10000);
}
