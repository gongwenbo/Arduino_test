/*
gongwenbo at tarsbot in 2016.1.19

*/
 #include <ros.h>
#include <geometry_msgs/Twist.h>
#include <logitech/logitech.h>

#define pinA 2              /*****encoder define******/
#define pinB 3
 unsigned long time=0;
 long count=0;
 long num=0;                /*****encoder define******/


ros::NodeHandle  nh;
logitech::logitech x,call_a_msg;
ros::Publisher chatter("motor_encoder_msg", &call_a_msg);

//ros::Publisher chatter("chatter_1", &str_msg);

void servo_cb ( const logitech::logitech& msg)
{
  x.a=(msg.a + 0.5)*100;
  x.a = map(x.a, 0, 100, 0, 255); 
  digitalWrite(13, HIGH-digitalRead(13));  //toggle led  
  
}

ros::Subscriber<logitech::logitech> sub("logitech_msg", servo_cb);

void setup()
{
  Serial.begin(9600);	//设置通讯的波特率为9600
  pinMode(9, OUTPUT);
  pinMode(13, OUTPUT);
     
  pinMode(pinA,INPUT);     /****encoder pin *****/
  pinMode(pinB,INPUT);   
  time=millis();                     /**** time initial ******/
  
  nh.initNode();
  nh.subscribe(sub);
  //nh.advertise(chatter);
}

 void loop()
 {
  analogWrite(9,x.a);
  nh.spinOnce();
  //chatter.publish( &str_msg );
  chatter.publish( &call_a_msg );     /****publish encoder data*****/
  
  delay(1);
}

/*********interrupt function block ************/
void blinkA()
{
  if ((millis()-time)>3) 
     count++;
     call_a_msg.a=count;
   time=millis();  

}
void blinkB()
{
  if ((millis()-time)>3) 
     count--;
     call_a_msg.a=count;
   time=millis();  

}
/*********interrupt function block ************/







