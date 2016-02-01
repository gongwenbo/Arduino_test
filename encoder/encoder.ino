#define PinA 2  //中断0
#define PinB 3  //中断1

unsigned long time = 0; 
long count = 0; //计数值
long num = 0;

//初始化
void setup()
{
  Serial.begin(9600); //窗口初始化

  pinMode(PinA,INPUT); //D2脚为输入
  pinMode(PinB,INPUT); //D3脚为输入

  attachInterrupt(0, blinkA, RISING);  //注册中断0调用函数blinkA
  attachInterrupt(1, blinkB, RISING);  //注册中断1调用函数blinkB

  time = millis(); //时间初值
}

//主体程序
void loop()
{
  while (num != count)
  {
    num = count;
    Serial.println(num);
  }
}

//中断0调用函数
void blinkA()
{
  if ((millis() - time) > 3) //防抖动处理
        count ++; 
        
  time = millis();
}

//中断1调用函数
void blinkB()
{
  if ((millis() - time) > 3)  //防抖动处理
        count --;
  time = millis();
}

