#ifndef StepperMotor_h
#define StepperMotor_h

#include <arduino.h>
class StepperMotor
{
 
 public:
  StepperMotor();
  void setup(int stepPin,int dirPin);
  void update(int delta,int currentPos, boolean debug);
  void updateStep(int delta,float maxAngleError);
  void setTarget(float target);
  
  int dirPin;
  int stepPin;
  
  int pos =0;
  int targetAngle=0;
  int currentTime=0;
  float stepTime =1000;

  bool stepState =false;

  int dir =0;

 float currentAngle =0;
 float currentSpeed =0;
   float prevAngle =0;
   int updateTime =0;

   float targetMSpeed =0;
   float stepPauze =1000000;

   float angleError =0;
};

#endif
