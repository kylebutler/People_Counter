#include <Time.h>
#include <SoftwareSerial.h>

int ppl_in=0;// count of people in
int ppl_out=0;// count of people out
int set_up=5;// time allowed for ckt to set up
int sensor1;// first IR sensor
int sensor2;// second IR sensor
int state;// switch variable
boolean flag=true;// flag for state of sensor 

void setup()
{
  Serial.begin(9600);
  pinMode(8, INPUT);// input for IR Sensor 1
  pinMode(9, INPUT);// Input for IR Sensor 2
  
  Serial.print("Setting up sensors");
  for(int i=0; i<set_up; i++)// allows sensors time to setup (5s)
  {
    Serial.print(".");
    delay(1000);
  }
  Serial.print("\nSensor setup complete");
  
}

void loop()
{
  sensor1=digitalRead(8);// assigns sensor1 to the value read at pin 8
  sensor2=digitalRead(9);// assigns sensor2 to the value read at pin 9
  
  if((sensor1==LOW) && (sensor2==LOW))// no activity from sensors
  {
   state=0; 
   flag=true;
  }
  if((sensor1==HIGH) && (sensor2==HIGH));// nothing needs to be done if both are high
  {
   state=0;
   //flag=true; 
  }
  if((sensor1==HIGH) && (sensor2==LOW) && (flag==true))// person enters room
  {
   state=1; 
  }
  if((sensor1==LOW) && (sensor2==HIGH) && (flag==true))// person exits the room
  {
   state=2; 
  }
  
  switch(state)
  {
    case(0):// do nothing for both high/low
      state=0;
    break;
    
    case(1):// person enters
      ppl_in++;// increment count of ppl entering
      Serial.println(ppl_in);
      state=0;
      flag=false;
    break; 
    
    case(2):// person exits
      ppl_in--;// decrement count of entered ppl
      ppl_out++;// increment count of ppl exiting
      if(ppl_in>=0)
      {
        Serial.println(ppl_in);
      }
      state=0;       
      flag=false;     
    break;
    
    default:
      state=0;
  }
  //delay(300);// wait .3s before looping again
}  
