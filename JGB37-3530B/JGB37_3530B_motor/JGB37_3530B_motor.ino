/*
gongwenbo at tarsbot 2016.1.18
 */
int bringhtness=0;
int fadeamount=3;
void setup()
{
  pinMode(9,OUTPUT);
  Serial.begin(9600);
}
void loop()

{
   
  analogWrite(9,bringhtness);
  Serial.println(bringhtness) ;
  bringhtness=bringhtness+fadeamount;

  if(bringhtness>255)
  {
    while(bringhtness)
    {
     bringhtness=bringhtness-fadeamount;
      analogWrite(9,bringhtness);
      Serial.println(bringhtness);
      delay(100);
    }
  }
    delay(100);   
}






