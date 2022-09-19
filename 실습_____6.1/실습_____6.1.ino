const byte number[16] = { //0부터 F까지 LED에 표시하기 위한 상수를 설정한다.
  B11000000, //0       DP,G,F,E,D,C,B,A 순으로 점등할 LED 자리에 0을 입력한다.
  B11111001, //1
  B10100100, //2
  B10110000, //3
  B10011001, //4
  B10010010, //5
  B10000010, //6
  B11111000, //7
  B10000000, //8
  B10010000, //9
  B10001000, //A
  B10000011, //b
  B11000110, //C
  B10100001, //d
  B10000110, //E
  B10001110  //F
};

void setup() {   // 한 번만 수행할 것을 여기에 넣는다.
 for(int i=2;i<=9;++i){     // 2번에서 9번 핀을 a b c d e f g dot 순서로 사용한다.
  pinMode(i,OUTPUT); //출력핀을 초기화 시킨다. 2번부터 9번핀을 출력으로 사용한다.
}
  digitalWrite(9,HIGH); //9번 핀에 연결 된 dot은 사용하지 않는다.
}
void loop() {  // 반복해서 수행할 것을 여기에 넣는다.
    for(int k=0;k<=15; ++k){   //0부터 F까지 총 15개의 값을 display하기 위해 각각의 숫자의 해당하는 fndisplay 값을 호출한다.
      fndDisplay(k);    // k값을 출력한다.
      delay(1000); //1초간 지연시킨다.
    }
} 

void fndDisplay(int displayValue){  //FND를 동작시키는 함수를 만든다.
  boolean bitValue; //참, 거짓 중 하나의 값을 가질 수 있는 boolean형 bitValue 변수를 선언한다.    

  for(int i=2;i<=9;++i){ // 2번부터 9번까지에 해당하는 핀을 불러온다.
    digitalWrite(i,HIGH); // 2번부터 9번에 해당하는 모든 핀을 소등시킴으로써 초기화 시킨다.
  }
  for(int i=0; i<=7;++i){ //0부터 7까지의 i값을 늘려가면서 segment를 켜주거나 꺼준다.
    bitValue = bitRead(number[displayValue],i); //k에 해당하는 값을 읽어와서 2진수로 만들어준다.
    digitalWrite(i+2,bitValue);  //비트 값을 핀에 디지털 출력을 한다.
    }
}
