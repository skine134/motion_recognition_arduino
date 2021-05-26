#include <MotionRecognition.h>


#define SM_DIR 74
#define SM_STEP 3
#define SM_MS1 41
#define SM_MS2 40
#define SM_SLEEP 38
#define HZ 1
#define UNIT_CYCLE 1.8
#define MIN_HZ 100
#define MAX_HZ 400

void MotionRecognition::begin(int rotationSize)
{

    Serial.begin(9600);
    stepMotor.begin(SM_DIR,SM_STEP,SM_MS1,SM_MS2,SM_SLEEP);
    stepMotor.setSpeed(speedHz);

    preYaw=0;
    speedHz=HZ;
    preTime=0;
    stepMotor.setStep(rotationSize);
}
void MotionRecognition::rotationStepMoter(String data,int delayTime)
{
    float inputData = readYaw(data);
    ActionStepMoter(inputData,delayTime);

}
float readYaw(String data)
{
    

    // Sample Data : "\n14.2451<EOF>"

    return data.toFloat();
}
void MotionRecognition::ActionStepMoter(float yaw,int delayTime)
{

// delay time보다 빨리 들어온 데이터는 버린다. (단위 : millisecond)
  unsigned long currentTime = millis();
  if(currentTime-preTime<delayTime*1000)
    return;
  // preTime 초기화
  preTime=currentTime;
  
  // 각도 차이만큼 회전시킨다.
  if (preYaw>inputYaw)
  {
    Serial.write("forward : ");
    stepMotor.setDirection(1);  //LEFT
  }
  else
  {
    Serial.write("reverse : ");
    stepMotor.setDirection(0);  //RIGHT
  } 
  long child = abs(inputYaw-preYaw);    //분자 : 이전 각도와 현재 각도 차이의 절대값
  float parent=(delayTime)*HZ;          //분모 : 설정된 경계 각도차
  /**
   * 
   * 이론 : 200Hz의 StepMotor가 1초동안 360도 돈다. -> xHz의 StepMotor는 t초동안 1.8 * x * t만큼 회전한다.
   * 공식 : y(각도) = 1.8*x(주파수)* t(초) -> x(주파수) = y(각도)/(1.8 * t(초))
   *
   */
  speedHz= child/parent; // 각도차이 / 각도
  
  // 최소 회전 각도보다 낮으면 버린다.
  if(child<MIN_HZ*(delayTime)*HZ){//delay_time milliseconds를 seconds로 변환
    stepMotor.off();
    return;
  }
  // 최대 속도보다 크면 최대 속도로 고정한다.
  if(speedHz>=MAX_HZ)
    speedHz=MAX_HZ;
  stepMotor.setSpeed(speedHz);
  stepMotor.on(1);
  Serial.println("yaw : ");
  Serial.println(inputYaw);
  Serial.println("hz : ");
  Serial.println(speedHz);

  // 이전 각도(preYaw) 초기회
  preYaw=inputYaw;
}