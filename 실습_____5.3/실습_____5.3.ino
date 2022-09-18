const int RedLed    = 3; // 3번핀에 연결 된 LED의 R을 사용하기 위한 변수를 선언한다.
const int GreenLed  = 5; // 5번핀에 연결 된 LED의 G를 사용하기 위한 변수를 선언한다.
const int BlueLed   = 6; // 6번핀에 연결 된 LED의 B를 사용하기 위한 변수를 선언한다.
 
void ledOutput(int Red, int Green, int Blue){ //R,G,B를 사용하기 위해 사용자 지정함수를 선언한다 
      analogWrite(RedLed,Red);      //3번핀에 연결 된 LED의 R를 점등시킨다.
      analogWrite(GreenLed,Green);  //5번핀에 연결 된 LED의 G를 점등시킨다.
      analogWrite(BlueLed,Blue);    //6번핀에 연결 된 LED의 B를 점등시킨다.
    }

void setup()   //한 번만 수행할 것을 여기에 넣는다.
{
}

void loop() // 반복해서 수행할 것을 여기에 넣는다.
{
    ledOutput(139,69,19); // cyan색을 출력하기 위해서 RGB에 각각 0,255,255의 값을 입력하여 구성한다.
    delay(3000);   //3초간 지연시킨다.
    
}

    
    
