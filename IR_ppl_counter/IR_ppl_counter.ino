#include <Time.h>
#include <SoftwareSerial.h>

int ppl_in=0;// count of people in
int ppl_out=0;// count of people out
int set_up=5;// time allowed for ckt to set up
int sensor1;// first IR sensor
int sensor2;// second IR sensor

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
  Serial.println("\nSensor setup complete");
  
}

void loop()
{
  sensor1=digitalRead(8);// assigns sensor1 to the value read at pin 8
  sensor2=digitalRead(9);// assigns sensor2 to the value read at pin 9


    if((sensor1==LOW) && (sensor2==LOW))// no activity from sensors
    {
      delay(1);
    }
  
    if((sensor1==HIGH) && (sensor2==LOW))// person enters room
    {      
      ppl_in++;// increment count of ppl entering
      Serial.println(ppl_in);
      //delay(100);
      
      while(sensor1==HIGH && sensor2==LOW)
       {
           sensor1=digitalRead(8);
           sensor2=digitalRead(9);
       }
      Serial.print("exited loop");
      //ADD DEBOUNCE TO INPUTS!
    }
    if((sensor1==LOW) && (sensor2==HIGH))// person exits the room
    {
      ppl_out++;// increment count of ppl exiting
      delay(100);
    }
    if((sensor1==HIGH) && (sensor2==HIGH))
    {
     delay(10);// nothing needs to be done if both are high 
    }
}  
