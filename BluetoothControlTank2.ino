/*
   0=spot,
   2=Left, 3=Right, 1=Forward, 4=Back
   5=move forward left, 6=move forward right
   7=move backward left, 8=move backward right
*/
#include <Servo.h>
enum { pinLB = 12, pinLF = 3, pinRB = 13, pinRF = 11 };
int inputPin = 4;    // define pin for sensor echo
int outputPin = 5;   // define pin for sensor trig
int delay_time_ = 300;
int direct_ = 0; // forward=1 backward=-1 stop=0
int distance_ = 0;      // forward speed

Servo myservo;

void setup()
{
  Serial.begin(9600); // define pin for motor output
  pinMode(pinLB, OUTPUT); // pin 12
  pinMode(pinLF, OUTPUT); // pin 3 (PWM)
  pinMode(pinRB, OUTPUT); // pin 13
  pinMode(pinRF, OUTPUT); // pin 11 (PWM)
  pinMode(inputPin, INPUT);    // define input pin for sensor
  pinMode(outputPin, OUTPUT);  // define output pin for sensor
  myservo.attach(9);    // Define servo motor output pin to D9 (PWM)
  handshake();
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
  ask_pin_F();            // read the distance ahead
  if (distance_ < 15 && direct_ == 1)        // if distance ahead is <10cm and moving forvard
  {
    stopp();               // stop
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
  direct_ = 0;
  set(HIGH, HIGH, 0, 0);
}
void forward()
{
  direct_ = 1;
  set(LOW, LOW, 255, 255);
}
void backward()
{
  direct_ = -1;
  set(HIGH, HIGH, 255, 255);
}
void turn_right()
{
  set(LOW, HIGH, 255, 255);
  delay(delay_time_);
  stopp();
}

void turn_left()
{
  set(HIGH, LOW, 255, 255);
  delay(delay_time_);
  stopp();
}
void backward_left()
{
  set(HIGH, LOW, 255, 0);
  delay(delay_time_);
  stopp();
}
void backward_right()
{
  set(LOW, HIGH, 0, 255);
  delay(delay_time_);
  stopp();
}
void forward_left()
{
  set(LOW, HIGH, 255, 0);
  myservo.write(45);
  delay(delay_time_);
  if (direct_ == 1)
    forward();
  else
    stopp();
  myservo.write(90);
}
void forward_right()
{
  set(HIGH, LOW, 0, 255);
  myservo.write(180 - 45);
  delay(delay_time_);
  if (direct_ == 1)
    forward();
  else
    stopp();
  myservo.write(90);
}
void handshake()
{
  myservo.write(45);
  delay(delay_time_);
  myservo.write(180 - 45);
  delay(delay_time_);
  myservo.write(90);
}
void ask_pin_F()   // measure the distance ahead
{
  myservo.write(90);
  digitalWrite(outputPin, LOW);   // ultrasonic sensor transmit low level signal 2μs
  delayMicroseconds(2);
  digitalWrite(outputPin, HIGH);  // ultrasonic sensor transmit high level signal10μs, at least 10μs
  delayMicroseconds(10);
  digitalWrite(outputPin, LOW);    // keep transmitting low level signal
  float f_distance = pulseIn(inputPin, HIGH);  // read the time in between
  distance_ = f_distance / 5.8 / 10;  // convert time into distance (unit: cm)
}

