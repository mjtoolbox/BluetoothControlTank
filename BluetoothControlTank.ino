/*
   2=Left, 3=Right, 1=Forward, 4=Back
   5=move forward left, 6=move forward right
*/

int pinLB = 12; // define pin 12
int pinLF = 3; // define pin 3
int pinRB = 13; // define pin 13
int pinRF = 11; // define pin 11
int val;


void setup()
{
  Serial.begin(9600); // define pin for motor output
  pinMode(pinLB, OUTPUT); // pin 12
  pinMode(pinLF, OUTPUT); // pin 3 (PWM)
  pinMode(pinRB, OUTPUT); // pin 13
  pinMode(pinRF, OUTPUT); // pin 11 (PWM)
}

void set(bool LB, bool RB, int LF, int RF)
{
  digitalWrite(pinLB, LB); 
  digitalWrite(pinRB, RB); 
  analogWrite(pinLF, LF);
  analogWrite(pinRF, RF);
}

void loop()
{
  val = Serial.read();
  if (val == '1') // move forward
  {  
    set(LOW, LOW, 255, 255);
  }
  if (val == '5') // move forward left
  {
    set(HIGH, LOW, 0, 255);
  }
  if (val == '6') // move forward right
  {
    set(LOW, HIGH, 255, 0);
  }
  if (val == '4') // move backward
  {
    set(HIGH, HIGH, 255, 255);
  }
  if (val == '2') // turn left
  {
    set(HIGH, LOW, 255, 255);
    delay(600);
    stopp();
  }
  if (val == '3') // turn right
  {
    set(LOW, HIGH, 255, 255);
    delay(600);
    stopp();
  }
  if ( val == '0') {
    stopp();
  }
}

void stopp() // stop
{
  digitalWrite(pinLB, HIGH);
  digitalWrite(pinRB, HIGH);
  analogWrite(pinLF, 0);
  analogWrite(pinRF, 0);
}
