/*
Designer:gongwenbo 
 Time:2016.1.26
 */
 #if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif
 
#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <logitech/logitech.h>
 
ros::NodeHandle  nh;
logitech::logitech x_axis;
logitech::logitech call_msg;
 
 
#define IN1 8
#define IN2 7
#define ENA 9
#define analogPin A5
long var=0;

ros::Publisher chatter("motor_odom", &call_msg);

void servo_cb ( const logitech::logitech& msg)
{
  x_axis.a=msg.a;
   //call_msg.a=x_axis.a;
  x_axis.a=(msg.a + 0.5)*100;
  x_axis.a = map(x_axis.a, 0, 100, -255, 255); 
  call_msg.a=x_axis.a;
  
  var=long(x_axis.a);
  if(var>0)
   {
     digitalWrite(IN1,HIGH);
     digitalWrite(IN2,LOW);
     //analogWrite(ENA,var);
   }
  
  else
  {
     digitalWrite(IN1,LOW);
     digitalWrite(IN2,HIGH);
     var=-var;
     //analogWrite(ENA,-var);
  }
 
  // call_msg.a=x.a;
}

ros::Subscriber<logitech::logitech> sub("logitech_msg", servo_cb);



void setup()
{
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(ENA,OUTPUT);
  //Serial.begin(9600);
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(chatter);
  
  
  
}

void loop()
{
 
  chatter.publish( &call_msg );
  nh.spinOnce();
  delay(30);
  analogWrite(ENA,var);
  //var= analogRead(analogPin);
  //var=map(var,0,1023,-255,255);
 /*
  if(var>0)
   {
     digitalWrite(IN1,HIGH);
     digitalWrite(IN2,LOW);
     //analogWrite(ENA,var);
   }
  
  else
  {
     digitalWrite(IN1,LOW);
     digitalWrite(IN2,HIGH);
     //analogWrite(ENA,-var);
  
  }
    analogWrite(ENA,-var);
  //Serial.println(var);
 // analogWrite(ENA,var/4);
  //Serial.println(var);
  
  */
}







