/*
Maintainer:gongwenbo
Time:2016.1.19
pin 1 and pin 2 connect encode
pin 9 output PWM
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

/*******encoder ********/
#define ENCODER_A_PIN 2         //interrupt 0 interface    
#define ENCODER_B_PIN 3         //interrupt 1 interface
long m_position;
float a;
float b;
float w;
/*******encoder ********/

ros::Publisher chatter("motor_odom", &call_msg);

void servo_cb ( const logitech::logitech& msg)
{
  x_axis.a=(msg.a + 0.5)*100;
  x_axis.a = map(x_axis.a, 0, 100, 0, 255); 
  digitalWrite(13, HIGH-digitalRead(13));  //toggle led  
 // call_msg.a=x.a;
}

ros::Subscriber<logitech::logitech> sub("logitech_msg", servo_cb);

void setup()
{
  //Serial.begin(9600);	//设置通讯的波特率为9600
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(chatter);
  
 /*******encoder initialize port ********/ 
  pinMode(ENCODER_A_PIN, INPUT);
  pinMode(ENCODER_B_PIN, INPUT);
  attachInterrupt(0, read_quadrature, CHANGE);      //intialize interrupt function 
 /*******encoder initialize port ********/ 
  
  
}

 void loop()
 {
  call_msg.a=m_position;
  analogWrite(9,x_axis.a);
  chatter.publish( &call_msg );
  nh.spinOnce();
  delay(1);
  
  a=m_position;
  delay(10);
  b=m_position;
  w=(b-a)*100*60/16/131;
  call_msg.c=w;
  
}

/***************************Interrupt subroutine in encoder*****************/
void read_quadrature()
{  
                                                                        
  if (digitalRead(ENCODER_A_PIN) == LOW)       // found a low-to-high on channel A 
  {   
                                                                            
    if (digitalRead(ENCODER_B_PIN) == LOW)      // check channel B to see which way 
      m_position++;
  }
                                                                        
  else                                                                    // found a high-to-low on channel A
  {
                                                                        
     if (digitalRead(ENCODER_B_PIN) == LOW)      // check channel B to see which way 
       m_position--;
  }
}
/***************************Interrupt subroutine in encoder*****************/







