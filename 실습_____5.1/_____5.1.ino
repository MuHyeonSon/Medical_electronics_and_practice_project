const int ledA = 3; // 첫번 째 LED를 3번으로 정의하는 변수를 선언한다.
const int ledB = 5; // 두번 쨰 LED를 5번으로 정의하는 변수를 선언한다.

int G=100;  // 지연시간에 대한 변수를 선언하고 0.1초만큼의 시간을 저장한다.
void setup() {  // 한 번만 수행해도 되는 것을 여기에 넣는다.

     pinMode(ledA, OUTPUT); // 3번핀에 연결 된 첫번 째 LED를 출력으로 사용한다. 
     pinMode(ledB, OUTPUT); // 5번핀에 연결 된 두번 째 LED를 출력으로 사용한다.
     
}

void loop() {      // 반복해서 수행 할 것을 여기에 넣는다.
  digitalWrite(ledA,HIGH); // 3번핀에 열결 된 첫번 째 LED를 점등한다.
  digitalWrite(ledB,LOW);  // 5번핀에 연결 된 두번 쩨 LED를 소등한다.
  delay(G);  // 지연시간에 대한 변수에 저장 된 시간 만큼 지연시킨다.
  digitalWrite(ledA,LOW); //3번핀에 연결 된 첫번 쩨 LED를 소등한다.
  digitalWrite(ledB,HIGH); //5번핀에 연결 된 두번 째 LED를 점등한다.
  delay(G);  // 지연시간에 대한 변수에 저장 된 시간 만큼 지연시킨다.
  G=G+100;  // 지연시간을 0.1초씩 증가시킨다.
  
  if(G==5000){  // 만약 지연시간이 5초가 되면 아래의 식을 실행한다.
     while(G>100){  // 지연시간이 0.1초보다 크지 않게 될 때까지 아래의 식을 반복해서 실행한다.
      G=G-100;   // 지연시간을 0.1초씩 감소시킨다. 
      
  digitalWrite(ledA,HIGH); // 3번핀에 열결 된 첫번 째 LED를 점등한다.
  digitalWrite(ledB,LOW);  // 5번핀에 연결 된 두번 쩨 LED를 소등한다.
  delay(G);                // 지연시간에 대한 변수에 저장 된 시간 만큼 지연시킨다.
  digitalWrite(ledA,LOW);  //3번핀에 연결 된 첫번 쩨 LED를 소등한다.
  digitalWrite(ledB,HIGH); //5번핀에 연결 된 두번 째 LED를 점등한다.
  delay(G);                // 지연시간에 대한 변수에 저장 된 시간 만큼 지연시킨다.
   
     }
     
     }
  

 
  


}
