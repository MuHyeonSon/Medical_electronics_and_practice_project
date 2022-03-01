//201804594 손무현 의용전자및실습 기말프로젝트

#include <Wire.h>  
#include <LiquidCrystal_I2C.h> //LCD 모듈
#include <DHT.h> //(온습도센서모듈)
#include <SoftwareSerial.h> // 소프트웨어 시리얼 라이브러리 불러옴 (블루투스 모듈)
#include <talkie.h> // 스피커&앰프 모듈
#define DHTPIN 7     // 디지털 7번핀 사용 (온습도 센서 모듈)
#define DHTTYPE DHT11   // DHT 11 모델사용 (DHT21/22 사용 가능) (온 습도 센서 모듈)
int Huimidifier = 13; //가습기 모듈은 13번핀을 사용(실제로는 릴레이 모듈을 연결하고 그 릴레이 모듈을 13번핀으로 제어함으로써 릴레이 모듈에 연결되어 있는 가습기 모듈을 제어)
int BT_RXD = 9; // 아두이노측 수신부 RXD는 9번핀(HC-09측 송신부 TXD와 연결) (블루투스 모듈)
int BT_TXD = 10; // 아두이노측 송신부 TXD는 10번핀(HC-10측 수신부 RXD와 연결) (블루투스 모듈)
Talkie voice; //(스피커 모듈)
SoftwareSerial bluetooth(10,9);   // 소프트웨어 시리얼 bluetooth 객체 선언

//습도가 40%밑으로 내려갔습니다. 가습기를 가동합니다. (스피커 모듈)
const uint8_t spdhumid[] PROGMEM = {0x80, 0xc8, 0xc8, 0x3d, 0xd2, 0xdc, 0xb6, 0xa2, 0x9a, 0x12, 0x8b, 0x30, 0x3b, 0x08, 0xe8, 0xca, 0x9c, 0x00, 0x4d, 0x5a, 0x14, 0x3c, 0xa9, 0x88, 0x72, 0x8f, 0x33, 0x30, 0xb1, 0xaa, 0xc3, 0xac, 0xae, 0xc2, 0x9d, 0x8b, 0xcc, 0xd0, 0x38, 0x48, 0xb2, 0x26, 0xbc, 0xc2, 0x6d, 0x07, 0x32, 0x1b, 0x8f, 0x30, 0xb1, 0xbd, 0x08, 0xd1, 0x2b, 0xdc, 0xa5, 0xc9, 0x21, 0x74, 0x0d, 0xf7, 0xc6, 0xa4, 0x83, 0x94, 0x5d, 0x62, 0x06, 0xd2, 0x3a, 0x96, 0x4e, 0xee, 0x4d, 0xad, 0xb2, 0x48, 0x95, 0x22, 0x32, 0xa9, 0xde, 0xa1, 0x6d, 0xed, 0x54, 0xe3, 0x38, 0x87, 0xf6, 0xa9, 0xdc, 0x4d, 0x9a, 0x1e, 0x2a, 0xe4, 0xf0, 0x50, 0x69, 0x7a, 0x98, 0x50, 0xca, 0x5c, 0xb8, 0xc9, 0x11, 0x43, 0x0e, 0x33, 0xa1, 0x26, 0xd7, 0x5c, 0x82, 0xcc, 0x11, 0xce, 0xb2, 0x34, 0x89, 0xb0, 0x6e, 0x66, 0x4a, 0x53, 0x27, 0x24, 0x1c, 0x11, 0x65, 0x89, 0x03, 0xd3, 0x64, 0x84, 0xab, 0xc7, 0x56, 0x40, 0xf1, 0x15, 0x8b, 0x2c, 0x3e, 0xdc, 0xd5, 0x62, 0x2f, 0x52, 0xa5, 0x48, 0x93, 0x6a, 0xba, 0x48, 0x99, 0xa3, 0x8c, 0x2b, 0x59, 0x23, 0x79, 0xd8, 0x4c, 0xf5, 0xa4, 0x02, 0x18, 0x22, 0x4c, 0x00, 0x93, 0x87, 0x15, 0x36, 0x12, 0xaf, 0xf1, 0x88, 0x7b, 0x28, 0xee, 0x66, 0xa7, 0x38, 0x49, 0x61, 0x69, 0x9c, 0xce, 0x92, 0x54, 0x82, 0x0a, 0x3c, 0x32, 0xcb, 0x13, 0x23, 0x56, 0xe8, 0xca, 0x0c, 0x8f, 0x95, 0xf8, 0xe8, 0xd5, 0xc2, 0x23, 0x56, 0x63, 0xf8, 0x16, 0x1f, 0xb1, 0xa5, 0x8b, 0x96, 0x43, 0xaa, 0x51, 0x9b, 0x0c, 0x86, 0x6e, 0xb7, 0x52, 0x8b, 0x97, 0x38, 0x6e, 0xab, 0xba, 0x2c, 0x29, 0x01, 0x9a, 0x55, 0x6d, 0x0c, 0x4b, 0xd5, 0xa3, 0x52, 0x6f, 0xd1, 0x3c, 0x74, 0x27, 0xfb, 0xbc, 0xc1, 0xd0, 0xdc, 0x5d, 0xe4, 0x4b, 0x03, 0x0b, 0x5f, 0x4f, 0x52, 0xce, 0x11, 0x1c, 0xf8, 0x6e, 0x6c, 0x61, 0x9a, 0xc9, 0xe0, 0xbb, 0x5b, 0xb8, 0x65, 0x68, 0x58, 0x54, 0x1e, 0xed, 0x52, 0xb3, 0x30, 0xd2, 0xfa, 0x8c, 0x48, 0xec, 0x45, 0x93, 0x32, 0x5b, 0xae, 0x75, 0x0f, 0x25, 0xec, 0x4c, 0x15, 0x35, 0x3b, 0x34, 0xf7, 0xdd, 0xe9, 0xdc, 0xb6, 0xb1, 0x68, 0xbb, 0x47, 0x7b, 0x92, 0x22, 0x82, 0x1f, 0xa6, 0xcd, 0x71, 0x8a, 0x02, 0x7e, 0x3b, 0x85, 0xc5, 0x19, 0x32, 0xc8, 0xbf, 0x29, 0xe4, 0xb4, 0x89, 0x60, 0xfc, 0xa6, 0x72, 0x5c, 0x23, 0x82, 0xf7, 0xa3, 0x2c, 0x71, 0x10, 0x8f, 0xe2, 0x6d, 0x86, 0x59, 0x01, 0x18, 0x69, 0x95, 0xa2, 0x55, 0x22, 0xa7, 0xb0, 0x24, 0xd7, 0x4c, 0x51, 0xec, 0xc1, 0xe3, 0xb4, 0x1d, 0x25, 0x49, 0x0e, 0xcd, 0x52, 0x65, 0x8f, 0x3a, 0x3b, 0x34, 0x6b, 0x91, 0x39, 0xec, 0x6c, 0xd1, 0x7c, 0x69, 0x64, 0x50, 0xdd, 0x45, 0x89, 0x21, 0x15, 0xaa, 0x4d, 0x17, 0x2d, 0x7a, 0x78, 0x04, 0x35, 0x6d, 0x12, 0x78, 0x15, 0xe6, 0xdc, 0x24, 0xc8, 0xe0, 0x9b, 0x71, 0x7a, 0xed, 0x26, 0x81, 0xdf, 0x1d, 0x22, 0x75, 0x96, 0x80, 0xfa, 0xa6, 0x98, 0xd4, 0x5d, 0x02, 0xac, 0x97, 0x1c, 0x9a, 0xac, 0x09, 0xb0, 0xce, 0xa6, 0x72, 0xda, 0xc3, 0x39, 0x15, 0x13, 0x8a, 0x69, 0x0e, 0xeb, 0x4a, 0x97, 0x87, 0x28, 0x3e, 0x8c, 0x6f, 0x16, 0x53, 0xa4, 0xb8, 0xb0, 0xba, 0x8a, 0x4f, 0x72, 0x92, 0x45, 0x9b, 0xa2, 0x31, 0x4e, 0x49, 0x0e, 0xe9, 0x72, 0x79, 0x38, 0x36, 0x39, 0x84, 0xc9, 0x15, 0x2e, 0xdc, 0x76, 0x11, 0xbc, 0x76, 0x99, 0x45, 0x9b, 0x84, 0x5b, 0x39, 0x99, 0x6e, 0xb1, 0x43, 0x52, 0xb8, 0xab, 0x0b, 0xdb, 0x0e, 0x66, 0x90, 0x61, 0x2a, 0x96, 0xc4, 0xe9, 0xde, 0x96, 0x8a, 0x6a, 0x52, 0xc7, 0xc2, 0x7f, 0xa2, 0x15, 0xa1, 0x02, 0x07, 0x7e, 0x68, 0x74, 0x92, 0x75, 0x12, 0xf8, 0xae, 0x3e, 0x46, 0x27, 0xe9, 0xe0, 0x5d, 0xa3, 0xad, 0xe1, 0xe4, 0x80, 0x77, 0xc1, 0x9a, 0xb6, 0x8b, 0x0f, 0xf2, 0x95, 0x40, 0x94, 0x0e, 0x31, 0x18, 0x57, 0x0c, 0x5a, 0xb9, 0xc8, 0xc2, 0x44, 0x5a, 0x46, 0xe4, 0xc5, 0x19, 0x5d, 0xa5, 0xca, 0x75, 0x4e, 0x12, 0x5c, 0x05, 0x29, 0x25, 0x3e, 0x7c, 0x72, 0x91, 0xac, 0x98, 0xf8, 0xf0, 0xc9, 0x79, 0x88, 0x51, 0xea, 0xc3, 0x67, 0xed, 0xc1, 0x46, 0xa9, 0x15, 0xb0, 0xac, 0x24, 0x02, 0x46, 0x0c, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x40, 0xab, 0xec, 0x0a, 0x68, 0x89, 0xfc, 0x28, 0xca, 0x79, 0x98, 0x59, 0xdb, 0x23, 0xd9, 0x62, 0x46, 0xee, 0x73, 0x8f, 0x28, 0x43, 0x24, 0x6b, 0x34, 0x49, 0x12, 0x2a, 0xdd, 0xa1, 0xda, 0x34, 0xc9, 0x45, 0x99, 0xbb, 0x6a, 0x62, 0x04, 0xb4, 0xac, 0x62, 0xd4, 0x62, 0x91, 0xad, 0x3c, 0x31, 0x92, 0x8a, 0x20, 0xf3, 0xc8, 0x46, 0xd0, 0xb8, 0x02, 0xbc, 0x32, 0x3c, 0xf1, 0xa2, 0x35, 0xaf, 0xbb, 0xe4, 0xc4, 0x87, 0xf6, 0x2c, 0x76, 0x86, 0xdd, 0x0c, 0x5e, 0xa8, 0xde, 0x2e, 0x72, 0x74, 0x68, 0x23, 0x6b, 0x3a, 0xc4, 0xd9, 0xa1, 0x03, 0xaf, 0x6e, 0x63, 0xb7, 0x97, 0xbe, 0xf4, 0x60, 0x94, 0xea, 0x71, 0xe7, 0xb4, 0x49, 0x2a, 0x8e, 0x2c, 0xdc, 0x93, 0x18, 0xa0, 0x25, 0x8e, 0xa5, 0x0a, 0xe7, 0x9e, 0xa1, 0x69, 0x8f, 0x6c, 0x82, 0xa6, 0x99, 0x36, 0x3d, 0x92, 0x2f, 0xe1, 0xaa, 0x52, 0xe7, 0x88, 0x26, 0x44, 0x1a, 0x4b, 0xdd, 0x21, 0xa3, 0x5a, 0xed, 0xa2, 0x71, 0x8d, 0x02, 0x7e, 0x77, 0xa9, 0x58, 0x1e, 0x3c, 0x4b, 0xd1, 0x65, 0x1a, 0x77, 0x31, 0xac, 0x59, 0x95, 0x72, 0xb3, 0x41, 0xf3, 0xc1, 0x39, 0xaa, 0x75, 0x03, 0x83, 0x1f, 0xf7, 0x86, 0x3b, 0x4b, 0x14, 0x7e, 0x63, 0x16, 0xd1, 0xf4, 0x90, 0xd6, 0x75, 0xb8, 0x58, 0xb3, 0x43, 0x7a, 0x17, 0xed, 0x62, 0x49, 0x07, 0x25, 0x72, 0xa5, 0xa9, 0x35, 0x75, 0x24, 0xf9, 0xea, 0x51, 0x15, 0xdb, 0x50, 0xf8, 0xb3, 0x77, 0x7a, 0x6c, 0x43, 0xa3, 0x5f, 0x1c, 0x61, 0xb6, 0x03, 0x0f, 0x7e, 0xa9, 0xa4, 0x2b, 0x0a, 0x2a, 0xf8, 0x2d, 0x14, 0x2d, 0x57, 0xb9, 0xe0, 0xb7, 0xa0, 0x95, 0xdd, 0xe4, 0x78, 0x65, 0x23, 0x9c, 0x71, 0x4e, 0xe8, 0x6c, 0xa7, 0x22, 0xd7, 0x39, 0x7c, 0xc8, 0x15, 0xc4, 0x5c, 0xfb, 0x08, 0x31, 0x46, 0xb0, 0x70, 0xec, 0x23, 0x24, 0x1f, 0xc1, 0x4a, 0xb1, 0x97, 0x98, 0x5c, 0x18, 0x3b, 0xd7, 0x1e, 0x51, 0x51, 0xe1, 0x1c, 0xe4, 0x84, 0x01, 0xc3, 0x56, 0x21, 0xa0, 0x95, 0x10, 0x80, 0xff};
//습도가 60%이상으로 올라갔습니다. 가습기를 가동을 멈춥니다. (스피커 모듈)
const uint8_t spahumid[] PROGMEM = {0x40, 0xbc, 0x4c, 0xd5, 0xd3, 0xd5, 0x4a, 0xf0, 0xba, 0xe4, 0x2c, 0x77, 0xcb, 0xc9, 0x29, 0x52, 0x32, 0xc2, 0x6c, 0x0f, 0x52, 0xa5, 0x4a, 0x77, 0x4b, 0x7a, 0x08, 0x97, 0x2a, 0x3c, 0x28, 0xd9, 0x21, 0x7c, 0x8a, 0x08, 0xe5, 0xb8, 0x8b, 0x14, 0xc9, 0xbb, 0xc4, 0xea, 0x25, 0x92, 0x7c, 0x6f, 0xa9, 0xae, 0xeb, 0x28, 0xfc, 0x2d, 0xb5, 0xc6, 0x54, 0x22, 0xa3, 0x72, 0x77, 0x8d, 0x26, 0x85, 0x60, 0x79, 0xbb, 0x9c, 0xe3, 0x1c, 0xd2, 0xc9, 0xea, 0x1d, 0x68, 0x72, 0x48, 0xab, 0xaa, 0xb7, 0xa8, 0xc9, 0x21, 0x59, 0x9a, 0xee, 0x94, 0xb8, 0x89, 0x21, 0x65, 0xba, 0x5c, 0x93, 0x04, 0xa6, 0x08, 0xb3, 0x70, 0x75, 0xda, 0xa8, 0xa2, 0xdd, 0xd3, 0xc5, 0xee, 0xc0, 0xbc, 0xb3, 0x99, 0x54, 0x67, 0x0d, 0x13, 0x23, 0xc6, 0xd5, 0xea, 0x32, 0x3d, 0xe8, 0xa8, 0x70, 0xb3, 0x0d, 0x8d, 0x70, 0x2e, 0x32, 0x5d, 0xd3, 0x1c, 0x42, 0xb6, 0x08, 0x37, 0x49, 0x77, 0x08, 0x55, 0xc3, 0x7c, 0x31, 0x6e, 0x23, 0xf9, 0xe0, 0xde, 0xa4, 0xb4, 0x4e, 0x00, 0x27, 0xa6, 0xc3, 0xe3, 0x0c, 0x51, 0xa5, 0xa8, 0x70, 0xb6, 0x7a, 0x44, 0x17, 0xaa, 0xd3, 0x29, 0xce, 0x11, 0x63, 0x88, 0x0a, 0x47, 0x3b, 0x47, 0x88, 0x29, 0x32, 0x15, 0xa3, 0x5c, 0xe1, 0x08, 0xc1, 0x57, 0x85, 0x50, 0xbc, 0x23, 0x69, 0xb7, 0xed, 0x8a, 0x71, 0x9b, 0x06, 0xc2, 0x4d, 0x22, 0xa7, 0x5d, 0x2a, 0x34, 0xb7, 0xe7, 0x64, 0xeb, 0x48, 0x54, 0xd7, 0x75, 0x9b, 0xe2, 0x26, 0xc0, 0xde, 0xdd, 0xa3, 0x8a, 0x83, 0x4a, 0x6c, 0xd5, 0xb4, 0x3b, 0x49, 0x7a, 0xe7, 0x6c, 0x15, 0x6e, 0x27, 0x09, 0xcb, 0x88, 0x86, 0x8a, 0x9d, 0x22, 0x0e, 0x69, 0xee, 0x66, 0xb6, 0x05, 0xb0, 0xb4, 0xea, 0x20, 0x78, 0xbc, 0x6d, 0x97, 0xc4, 0x8b, 0xe0, 0x7e, 0x77, 0x93, 0xdd, 0x18, 0x52, 0x9a, 0xee, 0x4a, 0x4f, 0x84, 0x80, 0x6c, 0x22, 0x1a, 0x9d, 0xac, 0x5b, 0x84, 0xdb, 0x5a, 0x84, 0x1e, 0x92, 0x45, 0x36, 0xfb, 0x10, 0x6a, 0x4a, 0x86, 0x78, 0xe3, 0x42, 0xf2, 0x5a, 0x91, 0xee, 0x69, 0x93, 0xdc, 0xb4, 0x79, 0xaa, 0x3a, 0x4e, 0x54, 0x94, 0x96, 0x13, 0x12, 0x77, 0x10, 0x7c, 0xb6, 0x8a, 0xe5, 0xb2, 0x41, 0xc8, 0x59, 0x22, 0x9e, 0xeb, 0x03, 0x49, 0x5f, 0xa9, 0x79, 0x2f, 0x13, 0x14, 0x79, 0x5d, 0xa6, 0x51, 0x07, 0x09, 0xce, 0x84, 0x27, 0x67, 0x94, 0xd6, 0x07, 0x63, 0x69, 0xa4, 0x91, 0x12, 0x8d, 0xe7, 0x6d, 0xb1, 0xc4, 0x6e, 0x14, 0x3e, 0x3f, 0xe6, 0x96, 0xf4, 0x50, 0x42, 0xcf, 0x75, 0x6b, 0xd2, 0xc5, 0x2b, 0x56, 0x37, 0x21, 0x51, 0x87, 0x84, 0xcd, 0x5e, 0x09, 0xd7, 0x1d, 0x12, 0x8c, 0x77, 0xa1, 0x5c, 0x27, 0x49, 0xa0, 0xed, 0x96, 0x71, 0x63, 0xc7, 0x3b, 0xee, 0xd9, 0xe9, 0x4d, 0x83, 0x10, 0x85, 0x64, 0x99, 0x26, 0x1d, 0xac, 0x8a, 0x51, 0x2a, 0xd1, 0xf6, 0x30, 0x2e, 0x79, 0x8a, 0x5a, 0xbb, 0xc3, 0xea, 0x1c, 0x6e, 0xe2, 0xeb, 0x06, 0x87, 0x5e, 0x78, 0x4a, 0x2e, 0x09, 0x02, 0xf8, 0x62, 0xe6, 0x19, 0x27, 0x09, 0xe0, 0x9b, 0xa7, 0x6a, 0x93, 0x21, 0x80, 0x3b, 0xae, 0x29, 0x6d, 0x9a, 0x0a, 0xc6, 0xa4, 0x06, 0xa7, 0x59, 0x32, 0x69, 0x1d, 0x6a, 0xac, 0xf6, 0x08, 0x62, 0x95, 0x46, 0x12, 0xdb, 0xc5, 0x8b, 0x65, 0x52, 0x0d, 0x5e, 0x06, 0xa7, 0x17, 0xd9, 0x27, 0xa8, 0x6d, 0xa2, 0xdd, 0x2c, 0x3f, 0xa0, 0xa6, 0x50, 0xba, 0x17, 0xc6, 0xa3, 0xec, 0xc2, 0x8b, 0xd9, 0x18, 0xaf, 0x88, 0x87, 0xcd, 0x6e, 0x70, 0xac, 0xd0, 0x5d, 0x16, 0x5a, 0xe5, 0xd6, 0x2c, 0x67, 0x18, 0x70, 0xc4, 0x18, 0xa3, 0xbd, 0xa5, 0xc2, 0x32, 0x15, 0x01, 0x6e, 0x86, 0x0c, 0xda, 0x64, 0x06, 0x64, 0x39, 0x82, 0x4d, 0x51, 0x49, 0xb4, 0xe4, 0xf0, 0x3e, 0x87, 0x1b, 0x73, 0x93, 0xc3, 0xda, 0x12, 0xe6, 0xa2, 0x4d, 0x07, 0xcf, 0x6b, 0x9b, 0x99, 0x36, 0x49, 0x3c, 0x0d, 0xd3, 0x91, 0x9c, 0xe4, 0xb0, 0xc1, 0x74, 0x6b, 0x70, 0xa2, 0x43, 0x7b, 0x5f, 0xa5, 0xc6, 0x8d, 0x07, 0xcd, 0x63, 0x4d, 0x3a, 0xb7, 0x71, 0x6c, 0x14, 0xe6, 0x15, 0x96, 0xc4, 0xb1, 0x4d, 0x84, 0xb9, 0x69, 0x62, 0x27, 0x57, 0xea, 0x16, 0xc2, 0x56, 0x9c, 0x04, 0xde, 0x86, 0x89, 0x4e, 0x2e, 0x2a, 0xf8, 0xeb, 0x66, 0x3e, 0x2a, 0x58, 0xe0, 0xbb, 0xdb, 0x24, 0x95, 0xe4, 0x82, 0xb7, 0xc1, 0x31, 0xa2, 0x43, 0x00, 0xce, 0x39, 0xe8, 0x8a, 0x09, 0x01, 0xa8, 0x57, 0x04, 0x35, 0x39, 0x44, 0xa0, 0x6d, 0x23, 0xd8, 0xec, 0x12, 0x07, 0xe3, 0xa1, 0xca, 0xb5, 0x17, 0xaf, 0x74, 0x97, 0x29, 0xd5, 0x39, 0x7c, 0x34, 0x55, 0xca, 0x54, 0xe7, 0x08, 0x29, 0x54, 0xb2, 0x52, 0xe2, 0x23, 0x24, 0x1b, 0x41, 0xc6, 0xae, 0x0f, 0x5f, 0x5d, 0x04, 0x3b, 0xb9, 0x59, 0x51, 0x31, 0x51, 0x94, 0xe4, 0x9a, 0x00, 0xc3, 0x5a, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0xa0, 0x15, 0x36, 0x03, 0xb4, 0x4c, 0x7e, 0x14, 0x6d, 0x3d, 0xcc, 0xb5, 0xed, 0x91, 0x6c, 0x55, 0xa3, 0xf0, 0xb9, 0x47, 0x94, 0x31, 0x92, 0x35, 0x9a, 0x14, 0x09, 0x95, 0x6a, 0x57, 0xab, 0x9b, 0xe4, 0xaa, 0xcc, 0x43, 0x35, 0x36, 0x02, 0x5a, 0x56, 0x31, 0x45, 0xb1, 0xc8, 0x16, 0x9e, 0x98, 0xa8, 0x45, 0x92, 0x59, 0x64, 0x23, 0x06, 0x4c, 0x65, 0x31, 0x58, 0xc3, 0x66, 0x3b, 0xbc, 0xce, 0xa2, 0x85, 0xda, 0x2d, 0xf7, 0xa4, 0x83, 0x66, 0x71, 0x26, 0x5d, 0x92, 0x24, 0x21, 0x2b, 0x8a, 0x0c, 0x4b, 0xd2, 0xac, 0x62, 0x44, 0xc3, 0xc8, 0xc9, 0x11, 0xad, 0xb3, 0x30, 0xb1, 0x66, 0x47, 0x14, 0x2e, 0xd2, 0xd5, 0xe6, 0x2e, 0x1d, 0xd6, 0x6a, 0x65, 0x9f, 0x6d, 0x5c, 0xf0, 0xb7, 0x44, 0x24, 0xce, 0x30, 0xb8, 0xf5, 0x1a, 0x95, 0xc4, 0x47, 0x64, 0xa3, 0xd2, 0x04, 0x9b, 0x0e, 0x91, 0x1d, 0xf3, 0x54, 0xa8, 0x9b, 0x44, 0xf0, 0xa9, 0xcb, 0x34, 0x69, 0x92, 0xc0, 0x17, 0xeb, 0xd2, 0xb8, 0x59, 0x5a, 0x02, 0x5c, 0x1d, 0x9e, 0xdc, 0xe4, 0x70, 0x3c, 0x54, 0x56, 0x70, 0xd2, 0xc3, 0x2a, 0x5b, 0x59, 0xc9, 0x6e, 0x0f, 0xcf, 0x62, 0x65, 0x26, 0x3b, 0x4d, 0x0a, 0xf8, 0xe1, 0x1e, 0x6a, 0x37, 0x19, 0xe0, 0x4b, 0x65, 0x0a, 0x9d, 0x66, 0x80, 0x27, 0x36, 0xc5, 0x4e, 0x96, 0xc6, 0x06, 0xdb, 0x06, 0x37, 0x19, 0x12, 0x1b, 0x94, 0xe7, 0x5c, 0x2f, 0x48, 0xe0, 0xf3, 0x9c, 0x49, 0x52, 0x23, 0x82, 0x1f, 0xae, 0xee, 0xa2, 0x95, 0x08, 0xfe, 0x54, 0xba, 0x59, 0x4e, 0x74, 0x11, 0x61, 0x1a, 0x66, 0x47, 0x00, 0x55, 0x87, 0x37, 0x9a, 0x96, 0xee, 0x71, 0x89, 0x93, 0x28, 0xfc, 0xa3, 0xd2, 0x22, 0xb5, 0xa3, 0xd0, 0x57, 0xcf, 0x34, 0xdb, 0x81, 0x81, 0x5f, 0x33, 0xd2, 0x2d, 0x47, 0x2e, 0x49, 0xe0, 0xb7, 0x4a, 0x25, 0xa3, 0xa2, 0x81, 0xbf, 0x4e, 0xba, 0x52, 0x82, 0x0b, 0xde, 0xa9, 0x48, 0x44, 0x75, 0x01, 0x08, 0xe1, 0x95, 0x1e, 0xe7, 0x70, 0x32, 0x54, 0x1a, 0x6b, 0xd4, 0x23, 0xfa, 0x10, 0x29, 0xa4, 0x75, 0x4f, 0x16, 0x4a, 0x38, 0x98, 0xc4, 0x3e, 0x42, 0x0c, 0x96, 0xa2, 0xd8, 0xf8, 0x88, 0xc9, 0x6b, 0x88, 0x51, 0xea, 0x25, 0x56, 0x2f, 0xae, 0x4e, 0x49, 0x9a, 0xd0, 0x82, 0x29, 0x17, 0xdb, 0x4d, 0x69, 0x8b, 0x66, 0x9a, 0x60, 0x5b, 0x88, 0xd5, 0x8b, 0x79, 0x90, 0x13, 0x78, 0xff};

 
LiquidCrystal_I2C lcd(0x27,16,2); //LCD 설정 (I2C주소는 LCD의 종류에 따라 다르기때문에 LCD가 0x3F, 0x20, 0x27인지 확인하세요)
DHT dht(DHTPIN, DHTTYPE); //DHT 설정
 
void setup()          // 한 번만 수행할 것들
{
  lcd.init(); //LCD 화면을 초기화
  Serial.begin(9600);  //9600속도로 시리얼 통신 시작
  bluetooth.begin(9600);  // 블루투스 통신 시작
  dht.begin(); //
  pinMode(13,OUTPUT); //가습기 동작은 디지털핀 13번핀 사용(13번핀을 출력으로 사용)
  pinMode(12,OUTPUT);
  lcd.backlight(); // LCD의 백라이트 점등시킨다.
  lcd.clear(); //LCD 화면의 모든 내용을 지움
  
}
 
void loop() {                 //반복해서 수행할 것들
  // 온 습도 모듈과 LCD 화면 출력*************************************************************************************
  float h = dht.readHumidity(); // 변수 h에 습도 값을 저장
  float t = dht.readTemperature(); // 변수 t에 온도 값을 저장
   
  lcd.backlight(); //LCD의 백라이트 점등
  lcd.display();
  lcd.print("TEMP:     "); //LCD 화면에 문자열 :"TEMP:     "를 출력
  lcd.print(t);   //LCD 화면에 온도값 출력
  lcd.setCursor(0,1); // LCD 화면에 문자열을 출력할 위치를 설정 (즉, 커서를 두번 쨰 줄 첫번 째 칸으로 설정)
  lcd.print("HUMIDITY: "); // LCD 화면에 "HUMIDITY:   " 출력
  lcd.print(h); //LCD 화면에 습도 값 출력
 
 /* Serial.print("습도: ");  (시리얼 모니터를 통해 온습도에 대한 정보를 모니터링 하고자 하면 해당 주석처리를 지우면 됨)
  Serial.print(h);
  Serial.print(" 온도: ");
  Serial.print(t);
  Serial.println();  */
  delay(2000); //2초 간격으로 업데이트
  lcd.clear(); //LCD 화면의 모든 내용을 지움
 //****************************************************************************************************

 // 가습기 모듈(릴레이모듈)과 음성출력************************************************************************
  if(h>60){                 //습도가 60%위로 올라갔을떄 
     digitalWrite(13,HIGH); //가습기 가동
     voice.say(spahumid);   //습도가 60%위로 올라갔다는 알림음 출력
     }
  else if(h==61){           //습도가 60%위로 올라갔을떄 
       
     voice.say(spahumid);   //습도가 60%위로 올라갔다는 알림음 출력
     }
  else if(h==39){           //습도가 40%밑으로 내려갔을떄
       
       voice.say(spdhumid); //습도가 40%밑으로 내려갔다는 알림음 출력
     }
  else{
      digitalWrite(13,LOW); //가습기 가동
  }

 /* 시연 영상에서는 임시로 영상촬영을 위해 위에 있는 코드를 사용하였습니다.
  -실제로 구현하려한 것에 대한 코드
  
  if(h==61){                //습도가 60%위로 올라갔을떄 
     
     voice.say(spahumid);/ / 습도가 60%위로 올라갔다는 알림음 출력
     }

  else if(h>60){  
     
     digitalWrite(13,LOW); //가습기 중단
     }
  
  else if(h==39){    //습도가 40%밑으로 내려갔을떄
       
       voice.say(spdhumid);//습도가 40%밑으로 내려갔다는 알림음 출력
     }
 
  else{
      digitalWrite(13,HIGH); //가습기 가동
  }
  */ 
//******************************************************************************************************


// 블루투스 모듈******************************************************************************************
    if (bluetooth.available()) {      // 블루투스 통신에 데이터가 입력되면(스마트폰 -> 아두이노)
    Serial.write(bluetooth.read()); // 블루투스 통신에 입력된 데이터를 시리얼 모니터로 출력(스마트폰 -> 아두이노 -> PC)

    
    char bt = bluetooth.read();
    Serial.write(bt); // 블루투스 통신에 입력된 데이터를 시리얼 모니터로 출력(스마트폰 -> 아두이노 -> PC)
 /* 작동시키고자 하는 방향대로 코드를 짜보았지만 정상적으로 작동하지 않아(문자열을 아두이노 측에서 정상적으로 인식하지 못해서) 계속해서 임의로 수정하고 한 번 누를 때마다 ON/OFF 모드가 바뀌는 스위치에 대한 코드를 참고하여 작성했습니다. 
 결과적으로 목표한 작동/멈춤에 대한 제어가 정상적으로 이루어 지도록 하는 것에 성공했습니다.어차피 a를 입력해도 a라고 인식하지 못하기 때문에 그 점을 반대로 이용하여 입력값이 'a'가 아니라면 작동(혹은 멈춤)시키도록 했습니다.
 따라서 a가 아닌 어떠한 임의의 문자열을 입력하더라도 동작과 멈춤이 정상적으로 실행됩니다.*/
    if(bt != 'a'){     //스마트폰으로 입력한 문자열이 'a'가 아니라면
     while(bt != 'a'){
     digitalWrite(13,HIGH); //가습기 작동
  
     if (bluetooth.available()) {    //블루투스 통신에 데이터가 입력되면
      Serial.write(bluetooth.read()); //블루투스 통신에 입력된 데이터를 시리얼 모니터로 출력(스마트폰 -> 아두이노 -> PC)
      bt = bluetooth.read(); //블루투스 통신에 입력된 데이터를 bt라는 변수에 저장
      if(bt != 'a'){break;}  //입력된 데이터가 'a'가 아니라면
      }
     }
     }
    else if(bt != 'a'){      //스마트폰으로 입력한 값이 'a'가 아니라면
     digitalWrite(13,LOW);   //가습기 멈춤
     
     delay(7000);            //7초 동안 딜레이

//*****************************************************************************************************
     }
    }
  }
  }
