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

void loop()
{
  if (Serial.available())
  {
    char val = Serial.read();

    switch (val)
    {
      case '0': stopp(); break;
      case '1': forward(); break;
      case '4': backward(); break;
      case '3': turn_right(); break;
      case '2': turn_left(); break;
      case '5': forward_left(); break;
      case '6': forward_right(); break;
      case '7': backward_left(); break;
      case '8': backward_right(); break;
    }
  }
}

void set(bool LB, bool RB, int LF, int RF)
{
  digitalWrite(pinLB, LB);
  digitalWrite(pinRB, RB);
  analogWrite(pinLF, LF);
  analogWrite(pinRF, RF);
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
void turn_right()
{
  set(LOW, HIGH, 255, 255);
  delay(300);
  stopp();
}

void turn_left()
{
  set(HIGH, LOW, 255, 255);
  delay(300);
  stopp();
}
void backward_left()
{
  set(HIGH, LOW, 255, 0);
  delay(300);
  stopp();
}
void backward_right()
{
  set(LOW, HIGH, 0, 255);
  delay(300);
  stopp();
}
void forward_left()
{
  set(LOW, HIGH, 255, 0);
  delay(300);
  if (direct == 1)
    forward();
  else
    stopp();
}
void forward_right()
{
  set(HIGH, LOW, 0, 255);
  delay(300);
  if (direct == 1)
    forward();
  else
    stopp();
}

