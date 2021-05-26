
#include <MotionRecognition.h>
#include <SoftwareSerial.h>

#define TX_PIN 2
#define RX_PIN 3

#define ROTATION_SIZE 0   //0 : FULL(1-1.8), 1 : HALF(1-0.9), 2 : QUART(1-0.45) [ Hz - angle ]
#define DELAY_TIME 0.1    // 초 단위

String data;
SoftwareSerial btSerial(TX_PIN, RX_PIN);
MotionRecognition motionRecognition;
void setup()
{
  // Serial3.begin(115200);
  btSerial.begin(115200);
  motionRecognition.begin(ROTATION_SIZE);
}
void loop()
{
  /*
  * 주석은 Mega2560 전용
  */
  // if(!Serial3.available())
  /****
   * 
   * read String
   * 
   ****/
  if(!btSerial.available())
    return;  
  // char tmp = Serial3.read();
  char tmp = btSerial.read();
  data+=tmp;
  int endIndex = data.indexOf("<EOF>");
  if(endIndex == -1)
    return;
  /****
   * 
   *   yaw 측정용
   *
   ****/
  //  Serial.println("yaw : "+String(inputYaw,3));
  motionRecognition.rotationStepMoter(data.substring(1,endIndex),DELAY_TIME);
  /***
   * 데이터 처리후 data 초기화 
   */
  data="";
}
