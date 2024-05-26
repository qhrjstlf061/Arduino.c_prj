#include <SoftwareSerial.h>
#include <Servo.h>

int trigPin = 8;
int echoPin =9;
int servoPin = 10;
Servo servo;
int motorASpeed = 255;
int motorBSpeed = 255;
int led_1 = 2;
int A_1A = 6;
int A_1B = 11;
int B_1A =3;
int B_1B =5;
int btRxPin = 12;
int btTxPin = 13;

SoftwareSerial bluetoothSerial(btRxPin,btTxPin);
char cmd = 's';

float getStableDistanceCM();

void setup() 
{
  bluetoothSerial.begin(9600);
  pinMode(A_1A, OUTPUT);
  pinMode(A_1B, OUTPUT);
  pinMode(B_1A, OUTPUT);
  pinMode(B_1B, OUTPUT);
  pinMode(led_1, OUTPUT);
  digitalWrite(A_1A, LOW);
  digitalWrite(A_1B, LOW);
  digitalWrite(B_1A, LOW);
  digitalWrite(B_1B, LOW);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin,INPUT);
  servo.attach(servoPin);
  servo.write(90);
  delay(1000);
}

void loop() 
{
  int cm = getStableDistanceCM();
  long leftDistance = 0; 
  long rightDistance = 0;

  if(cm < 25)
  {
    stop();
    delay(500);

    servo.write(150);
    delay(500);
    leftDistance = getStableDistanceCM();
    delay(500);

    servo.write(30);
    delay(500);
    rightDistance = getStableDistanceCM();
    delay(500);

    servo.write(90);
    delay(1000);
    back();
    delay(500);
    if (leftDistance > rightDistance)
    {
      left();
    }
    else
    {
      right();
    }
  }
  else
  {
    forward();
  }
  
//  char cmd = bluetoothSerial.read();
//  switch (cmd)
//  {
//    case 'f':
//    digitalWrite(led_1,LOW);
//    analogWrite(A_1A, motorASpeed);
//    analogWrite(A_1B, 0);
//    analogWrite(B_1A, motorBSpeed);
//    analogWrite(B_1B, 0);
//    break;
//    case 'b':
//    digitalWrite(led_1,LOW);
//    analogWrite(A_1A, 0);
//    analogWrite(A_1B, motorASpeed);
//    analogWrite(B_1A, 0);
//    analogWrite(B_1B, motorBSpeed);
//    break;
//    case 'r':
//    digitalWrite(led_1,HIGH);
//    analogWrite(A_1A, 0);
//    analogWrite(A_1B, 0);
//    analogWrite(B_1A, motorBSpeed);
//    analogWrite(B_1B, 0);
//    break;
//    case 'l':
//    analogWrite(A_1A, motorASpeed);
//    analogWrite(A_1B, 0);
//    analogWrite(B_1A, 0);
//    analogWrite(B_1B, 0);
//    digitalWrite(led_1,HIGH);
//    break;
//    case 's':
//    analogWrite(A_1A, 0);
//    analogWrite(A_1B, 0);
//    analogWrite(B_1A, 0);
//    analogWrite(B_1B, 0);
//    digitalWrite(led_1,LOW);
//    break;
//  }
}

float getDistanceCM()
{
  digitalWrite(echoPin,LOW);
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  float distance = pulseIn(echoPin, HIGH)/29.0/2.0;

  return distance;
}

float getStableDistanceCM()
{
  int CmSum = 0;
  for(int i = 0; i < 7; i++)
  {
    CmSum += getDistanceCM();
  }
  return CmSum / 10;
}

void forward()
{
  analogWrite(A_1A, motorASpeed);
  analogWrite(A_1B, 0);
  analogWrite(B_1A, motorBSpeed);
  analogWrite(B_1B, 0);
}

void back()
{
  analogWrite(A_1A, 0);
  analogWrite(A_1B, motorASpeed);
  analogWrite(B_1A, 0);
  analogWrite(B_1B, motorBSpeed); 
}

void left()
{
  analogWrite(A_1A, motorASpeed);
  analogWrite(A_1B, 0);
  analogWrite(B_1A, 0);
  analogWrite(B_1B, 0);
}

void right()
{
  analogWrite(A_1A, 0);
  analogWrite(A_1B, 0);
  analogWrite(B_1A, motorBSpeed);
  analogWrite(B_1B, 0);
}

void stop()
{
  analogWrite(A_1A, 0);
  analogWrite(A_1B, 0);
  analogWrite(B_1A, 0);
  analogWrite(B_1B, 0);
}
//void Lccambbakey()
//{
//  while(cmd = 'l')
//  {
//    digitalWrite(led_1,HIGH);
//    delay(500);
//    digitalWrite(led_1,LOW);
//    delay(500);
//  }
//}
