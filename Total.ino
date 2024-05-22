
#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int X;
int Y;
float TIME = 0;
float FREQUENCY = 0;
float WATER = 0;
float TOTAL = 0;
float LS = 0;
const int input = A0;
float setpoint = 0.3;            //// setpoint = 50% => 0.8 liter
float PID_error = 0;
float previous_error = 0;
float elapsedTime, Time, timePrev;
float PID_value = 0;
float PI_value = 0;
float PD_value = 0;
const int sw1 = 2; // on/off
const int sw2 = 3; // automatic
const int sw3 = 4; // PID
const int sw4 = 5; // PI
const int sw5 = 6; // PD
const int sw6 = 7;  // P
const int en = 8;  // Enable for switch on/off
int sw_v1=0;
int sw_v2=0;
int sw_v3=0;
int sw_v4=0;
int sw_v5=0;
int sw_v6=0;

//PID constants
//////////////////////////////////////////////////////////
int kp = 50;   int ki = 3;   int kd = 0.3;
//////////////////////////////////////////////////////////

int PID_p = 0;    int PID_i = 0;    int PID_d = 0;

void setup()
{
pinMode(sw1, INPUT);
pinMode(sw2, INPUT);
pinMode(sw3, INPUT);
pinMode(sw4, INPUT);
pinMode(sw5, INPUT);
pinMode(sw6, INPUT);
myservo.attach(9);  // attaches the servo on pin 9 to the servo object
myservo.write(180);
Serial.begin(9600);
delay(2000);
pinMode(input,INPUT);
Time = millis();
}
void loop()
{
 sw_v1 = digitalRead(sw1);
 sw_v2 = digitalRead(sw2);
 sw_v3 = digitalRead(sw3);
 sw_v4 = digitalRead(sw4);
 sw_v5 = digitalRead(sw5);
 sw_v6 = digitalRead(sw6);


// myservo.write(90); // open
X = pulseIn(input, HIGH);
Y = pulseIn(input, LOW);
TIME = X + Y;
FREQUENCY = 100000/TIME;
WATER = FREQUENCY/7.5;
LS = WATER/60;
if(FREQUENCY >= 0)
{
if(isinf(FREQUENCY))
{
}
else
{
TOTAL = TOTAL + LS;
//Serial.println(TOTAL);
//Next we calculate the error between the setpoint and the real value
PID_error = TOTAL - setpoint ;
//Calculate the P value
PID_p = 1*kp * PID_error;
//Calculate the I value
PID_i = 0.1*PID_i + (ki * PID_error);
//For derivative we need real time to calculate speed change rate
timePrev = Time;                            // the previous time is stored before the actual time read
Time = millis();                            // actual time read
elapsedTime = (Time - timePrev) / 1000; 
//Now we can calculate the D calue
PID_d = kd*((PID_error - previous_error)/elapsedTime);
//Final total PID value is the sum of P + I + D
PID_value = PID_p + PID_i + PID_d;
//We define bottel size range between 0 and 800mL
  if(PID_value < 0)
  {    PID_value = 0;    }
  if(PID_value > 0.3)  
  {    PID_value = 0.3;  }
//Final total PID value is the sum of P + I
PI_value = PID_p + PID_i;
//We define bottel size range between 0 and 800mL
  if(PI_value < 0)
  {    PI_value = 0;    }
  if(PI_value > 0.3)  
  {    PI_value = 0.3;  }
//Final total PID value is the sum of P + D
PD_value = PID_p + PID_d;
//We define bottel size range between 0 and 800mL
  if(PD_value < 0)
  {    PI_value = 0;    }
  if(PD_value > 0.3)  
  {    PI_value = 0.3;  }
}
}
///////////////////////////////////////////////////////////////////////
//x2:
      if(sw_v1== HIGH){
  myservo.write(90); // closed
  //goto next;
  }
else {
 myservo.write(180); // open
 goto x1;
  }
  
///////////////////////////////////////////////////////////////////////
 x1:     
       if(sw_v2 == HIGH){
myservo.write(90); // open
      if(TOTAL>=0.3){
  myservo.write(180); // closed
  }
else {
  myservo.write(90); // open
  }
       }     
      else if(sw_v2 == LOW){
       //myservo.write(180); // closed
      // goto x2;
        }
       
      
///////////////////////////////////////////////////////////////////////
if(sw_v3 == HIGH){
myservo.write(90); // closed
      if(PID_value>=0.3){
  myservo.write(180); // closed
  }
else {
  myservo.write(90); // open
  }
      }
      else if(sw_v3 == LOW){
     //  myservo.write(180); // closed
        }
///////////////////////////////////////////////////////////////////////
if(sw_v4 == HIGH){
myservo.write(90); // closed
      if(PI_value>=0.3){
  myservo.write(180); // closed
  }
else {
  myservo.write(90); // open
  }
      }
      else if(sw_v4 == LOW){
       /// myservo.write(180); // closed
        }
////////////////////////////////////////////////////////////////////////
if(sw_v5 == HIGH){
myservo.write(90); // closed
      if(PD_value>=0.01){
  myservo.write(180); // closed
  }
else {
  myservo.write(90); // open
  }
      }
      else if(sw_v5 == LOW){
       // myservo.write(180); // closed
        }
        
///////////////////////////////////////////////////////////////////////
if(sw_v6 == HIGH){
myservo.write(90); // closed
      if(PID_p>=0.01){
  myservo.write(180); // closed
  }
else {
  myservo.write(90); // open
  }
      }
      else if(sw_v6 == LOW){
       // myservo.write(180); // closed
        }

Serial.println(PD_value);
Serial.println(TOTAL);
delay(1000);

}
