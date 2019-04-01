#ifndef Input_h
#define Input_h

#include <arduino.h>
class Input
{
 
 public:
  Input();
 
  
  void update(int delta);
  void doStep();
 float mapAnalog(float value);
  float mapAnalog2(float value);
  void updateSteeringAngles();
  int currentTime=0;
  
  int stepTime=0;
  int step=0; 
  int numSteps;

  //
  bool hasRC =true;
  int mainControleFrontBackRaw=0;
  float mainControleFrontBack=0;
  
  int mainControleLeftRightRaw=0;
  float mainControleLeftRight=0;


  float leftWheelAngle =0;
  float rightWheelAngle =0;
  float turnDistance =1000;
  
  float powerRaw =0;
    float power =0;

    bool lightOn =false;
    int lightCount =0;
};

#endif
