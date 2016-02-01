/*
Maintainer:gongwenbo
Time:2016.1.19
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
logitech::logitech x;
logitech::logitech call_msg;

ros::Publisher chatter("chatter_1", &call_msg);

void servo_cb ( const logitech::logitech& msg)
{
  x.a=(msg.a + 0.5)*100;
  x.a = map(x.a, 0, 100, 0, 255); 
  digitalWrite(13, HIGH-digitalRead(13));  //toggle led  
  call_msg.a=x.a;
}

ros::Subscriber<logitech::logitech> sub("logitech_msg", servo_cb);

void setup()
{
  //Serial.begin(9600);	//设置通讯的波特率为9600
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(chatter);
}

 void loop()
 {
  analogWrite(9,x.a);
  chatter.publish( &call_msg );
  nh.spinOnce();
  delay(1);
}








