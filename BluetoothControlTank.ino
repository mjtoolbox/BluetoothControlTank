/*
   0=spot,
   2=Left, 3=Right, 1=Forward, 4=Back
   5=move forward left, 6=move forward right
   7=move backward left, 8=move backward right
*/
enum { pinLB = 12, pinLF = 3, pinRB = 13, pinRF = 11 };
int direct = 0;

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
  int val = Serial.read();
  if (val == '1') // move forward
  {
    forward();
  }
  else if (val == '5') // move forward left
  {
    set(LOW, HIGH, 255, 0);
    delay(300);
    if (direct == 1)
      forward();
    else
      stopp();
  }
  else if (val == '6') // move forward right
  {
    set(HIGH, LOW, 0, 255);
    delay(300);
    if (direct == 1)
      forward();
    else
      stopp();
  }
  else if (val == '4') // move backward
  {
    backward();
  }
  else if (val == '7') // move backward left
  {
    set(HIGH, LOW, 255, 0);
  }
  else if (val == '8') // move backward right
  {
    set(LOW, HIGH, 0, 255);
  }
  else if (val == '2') // turn left
  {
    set(HIGH, LOW, 255, 255);
    delay(300);
    stopp();
  }
  else if (val == '3') // turn right
  {
    set(LOW, HIGH, 255, 255);
    delay(300);
    stopp();
  }
  else if ( val == '0') 
  {
    stopp();
  }
}

void stopp() // stop
{
  direct = 0;
  set(HIGH, HIGH, 0, 0);
}
void forward()
{
  direct = 1;
  set(LOW, LOW, 255, 255);
}
void backward()
{
  direct = -1;
  set(HIGH, HIGH, 255, 255);
}

