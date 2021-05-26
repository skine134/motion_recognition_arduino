/* MotionRecognition.h */
#ifndef __MOTION_RECOGNITION_H__
#define __MOTION_RECOGNITION_H__

#include <StepMotor.h>
#include <Arduino.h>

class MotionRecognition
{
private:
    String data;
    String direction;
    float preYaw;
    float parent;
    int speedHz;
    float delayTime;
    unsigned long preTime;
    StepMotor stepMotor;
    
public:
    void begin(int rotationSize,float delayTime);
    void ActionStepMoter(float yaw);
    void rotationStepMoter(String data);
    float readYaw(String data);
};
extern MotionRecognition gMotionRecognition;
#endif
