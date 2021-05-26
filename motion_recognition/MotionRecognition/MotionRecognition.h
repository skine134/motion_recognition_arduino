/* MotionRecognition.h */
#ifndef __MOTION_RECOGNITION_H__
#define __MOTION_RECOGNITION_H__

# include <StepMotor.h>

class MotionRecognition
{
private:
    StepMotor stepMotor;
    String data;
    float preYaw;
    float inputYaw;
    int speedHz;
    unsigned long preTime;
public:
    void begin(int delayTime);
    void ActionStepMoter(float yaw,int delayTime);
    void rotationStepMoter(String data,int delayTime);
    float readYaw(String dta);
};
extern MotionRecognition gMotionRecognition;
#endif
