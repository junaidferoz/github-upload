//#include<LiquidCrystal.h> // header file to use the lcd display
#define RPM_MAX 500   //defined maximum rpm of the motor used.
float motor_speed=0;float duty_cycle=0;   //initial declarations
//float val;
int en=11;    //defines the various PWM values given to the driver IC (actually regulates the speed)
int in1=12;   //digital pins used to give power and isolates the motor from the controller.
int in2=13;   //if not isolated, the UNO board might heat up and break down. 
//LiquidCrystal lcd(7,6,5,4,3,2);  //instantiation of lcd object
void setup() {
  // put your setup code here, to run once:
  pinMode(en,OUTPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);    //initially the motor is in the OFF state
  //lcd.begin(16,2);   //initialization
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(in1,LOW);        //turning the motor ON
  digitalWrite(in2,HIGH);
  for(int i=150;i<255;i+=10){
    analogWrite(en,i);
    Serial.print("PWM="+String(i));
    Serial.println("RPM="+String(display_speed((float)i)));
    //lcd.setCursor(0,0);
    //lcd.print("RPM="+String(display_speed((float)i)));  //displaying the rotations per minute in the serial monitor
    delay(4500);
    if(i>=230){ //detection of overspeeding
        //lcd.setCursor(0,0);
        Serial.println("Overspeeding...\nReducing Speed...");
        for(int j=230;j>=150;j-=10){      //reduction in speed begins
          analogWrite(en,j);
          //lcd.setCursor(0,1);
          Serial.print("PWM="+String(j));
          Serial.println("RPM : "+String(display_speed((float)j)));  
          delay(4500);}//introduce delays to effectively observe the changes in the rotation of the motor
          exit(0);}
}
}
float display_speed(float pwm){       //utility program to calculate the speed of the motor in rotation
  duty_cycle=(pwm/255);
  motor_speed=duty_cycle*RPM_MAX;
  return motor_speed;
}
