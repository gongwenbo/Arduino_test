/*
Maintainer:gongwenbo 
Time: 2016.1.20 
*/
#define ENCODER_A_PIN 2         //interrupt 0 interface 
#define ENCODER_B_PIN 3         //interrupt 1 interface
long position;
void setup()
{
  pinMode(ENCODER_A_PIN, INPUT);
  pinMode(ENCODER_B_PIN, INPUT);
  attachInterrupt(0, read_quadrature, CHANGE);      //intialize interrupt function 
  Serial.begin(9600);
}
 
void loop()
{
   Serial.print("Position: ");
   Serial.println(position, DEC);
 }
 
void read_quadrature()
{  
                                                                        
  if (digitalRead(ENCODER_A_PIN) == LOW)       // found a low-to-high on channel A 
  {   
                                                                            
    if (digitalRead(ENCODER_B_PIN) == LOW)      // check channel B to see which way 
      position++;
  }
                                                                        
  else                                                                    // found a high-to-low on channel A
  {
                                                                        
     if (digitalRead(ENCODER_B_PIN) == LOW)      // check channel B to see which way 
       position--;
  }
}
