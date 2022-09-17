const int ledA  = 3; //3번핀에 연결된 LED를 사용한다.
const int ledB  = 5; //5번핀에 연결된 LED를 사용한다.
const int ledC  = 6; //6번핀에 연결된 LED를 사용한다.
const int ledD  = 9; //9번핀에 연결된 LED를 사용한다.
const int ledE  = 11; //11번핀에 연결된 LED를 사용한다.
int brightnessA = 100; // 3번핀에 연결된 LED의 밝기를 조절하기 위한 변수를 선언하고 초기값을 저장한다.
int brightnessB = 125; //5번핀에 연결된 LED의 밝기를 조절하기 위한 변수를 선언하고 초기값을 저장한다.
int brightnessC = 150; //6번핀에 연결된 LED의 밝기를 조절하기 위한 변수를 선언하고 초기값을 저장한다.
int brightnessD = 175; //9번핀에 연결된 LED의 밝기를 조절하기 위한 변수를 선언하고 초기값을 저장한다.
int brightnessE = 200; //11번핀에 연결된 LED의 밝기를 조절하기 위한 변수를 선언하고 초기값을 저장한다.

int incrementA =1; //3번핀에 연결된 LED밝기의 증감을 위한 변수를 선언한다.
int incrementB =1; //5번핀에 연결된 LED의 밝기의 증감을 위한 변수를 선언한다.
int incrementC =1; //6번핀에 연결된 LED의 밝기의 증감을 위한 변수를 선언한다.
int incrementD =1; //9번핀에 연결된 LED의 밝기의 증감을 위한 변수를 선언한다.
int incrementE =1; //11번핀에 연결된 LED의 밝기의 증감을 위한 변수를 선언한다.



void setup()  //한 번만 수행할 것을 여기에 넣는다.
{
}
void loop() //반복해서 수행할 것을 여기에 넣는다.
{
  analogWrite(ledA,255-brightnessA); //3번핀에 연결된 LED를 점등시킨다.
  analogWrite(ledB,255-brightnessB); //5번핀에 연결된 LED를 점등시킨다.
  analogWrite(ledC,255-brightnessC); //6번핀에 연결된 LED를 점등시킨다.
  analogWrite(ledD,255-brightnessD); //9번핀에 연결된 LED를 점등시킨다.
  analogWrite(ledE,255-brightnessE); //11번핀에 연결된 LED를 점등시킨다.

  brightnessA = brightnessA + incrementA; //3번핀에 연결된 LED의 밝기를 조절한다.
  brightnessB = brightnessB + incrementB; //5번핀에 연결된 LED의 밝기를 조절한다.
  brightnessC = brightnessC + incrementC; //6번핀에 연결된 LED의 밝기를 조절한다.
  brightnessD = brightnessD + incrementD; //9번핀에 연결된 LED의 밝기를 조절한다.
  brightnessE = brightnessE + incrementE; //11번핀에 연결된 LED의 밝기를 조절한다.
      if((brightnessA >=255)||(brightnessA<=0)) incrementA = - incrementA; // 3번핀에 연결된 LED의 밝기가 증가 후 다시 감소할 수 있도록 설정한다.
      if((brightnessB >=255)||(brightnessB<=0)) incrementB = - incrementB; // 5번핀에 연결된 LED의 밝기가 증가 후 다시 감소할 수 있도록 설정한다.
      if((brightnessC >=255)||(brightnessC<=0)) incrementC = - incrementC; // 6번핀에 연결된 LED의 밝기가 증가 후 다시 감소할 수 있도록 설정한다.
      if((brightnessD >=255)||(brightnessD<=0)) incrementD = - incrementD; // 9번핀에 연결된 LED의 밝기가 증가 후 다시 감소할 수 있도록 설정한다.
      if((brightnessE >=255)||(brightnessE<=0)) incrementE = - incrementE; // 11번핀에 연결된 LED의 밝기가 증가 후 다시 감소할 수 있도록 설정한다.
  delay(10); //0.01초간 지연시킨다. 
   

 }
