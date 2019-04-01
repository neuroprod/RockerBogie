#ifndef Motors_h
#define Motors_h

#include <arduino.h>
class Motors
{
 
 public:
  Motors();
  void setup();
  void update(int delta);
  void setMotorSpeeds(int fl,int fr,int ml,int mr,int bl,int br);
  void doStep();
  int currentTime=0;
  
  int stepTime=0;
  int step=0; 
  int numSteps;

  int frontLeft=0;
  int frontRight=0;
  int midLeft=0;
  int midRight=0;
  int backLeft=0;
  int backRight=0;
};

#endif
