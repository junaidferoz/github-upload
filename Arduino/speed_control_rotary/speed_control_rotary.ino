#include<LiquidCrystal.h>


#define button  13  // Rotary encoder push-button pin (SW) is connected to Arduino pin 4
#define pwm1    8   // PWM1 output
#define pwm2    7   // PWM2 output

// variable declarations
boolean motor_dir = 0;
uint8_t last_read;
int8_t  quad = 0, change;
int16_t motor_speed = 0;
LiquidCrystal lcd(12,11,5,4,3,2);
void setup()
{
  pinMode(1, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(button, INPUT_PULLUP);
  pinMode(pwm1,   OUTPUT);
  pinMode(pwm2,   OUTPUT);

  last_read = digitalRead(6) << 1 | digitalRead(1);
  attachInterrupt(0, encoder_read, CHANGE);
  attachInterrupt(1, encoder_read, CHANGE);
  lcd.begin(16,2);
}


void encoder_read()
{
  uint8_t encoderRead = 0;

  encoderRead = digitalRead(6) << 1 | digitalRead(1);

  if(encoderRead == last_read)
    return;

  if(bitRead(encoderRead, 0) == bitRead(last_read, 1))
    quad -= 1;
  else
    quad += 1;
  last_read = encoderRead; 

  
}

int8_t EncoderGet(void)
{
  int8_t val = 0;
  while(quad >= 4){
    val += 1;
    quad -= 4;
  }
  while(quad <= -4){
    val -= 1;
    quad += 4;
  }
  return val;
}

bool debounce()
{
  byte count = 0;
  for(byte l = 0; l < 5; l++) {
    if (digitalRead(button) == 0)
      count++;
    delay(10);
  }
  if(count > 2)  return 1;
  else           return 0;
}

void loop()
{
  if(digitalRead(button) == 0)  // if Button is pressed
    if(debounce())              // call debounce function
    {
      motor_dir = !motor_dir;  // invert direction variable
      set_speed(motor_speed);
      while(debounce());  // call debounce function (wait for button to be released)
    }
  
  change = EncoderGet();
    if(change){
      motor_speed += change;

      if(motor_speed > 255)
        motor_speed = 255;
      if(motor_speed < 0)
        motor_speed = 0;

      set_speed(motor_speed);
      int duty=(motor_speed/255)*100;
      int spd_rpm=duty*500;
      lcd.setCursor(0,0);
      lcd.print("RPM="+String(spd_rpm));
  }
  
  delay(50);  // wait 50 ms

}

void set_speed(byte pwm_duty)
{
  switch (motor_dir)
  {
    case 0: digitalWrite(pwm1, 0);
            analogWrite(pwm2, motor_speed);
            break;

    case 1: digitalWrite(pwm2, 0);
            analogWrite(pwm1, motor_speed);
  }
}
// end of code.
