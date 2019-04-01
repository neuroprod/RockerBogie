#ifndef Lights_h
#define Light_h
#include <Adafruit_NeoPixel.h>
#include <arduino.h>
class Lights
{
 
 public:
  Lights();
  void setup();
  void update(int delta,bool on);
  
  void doStep(bool on);
  int currentTime=0;
  
  int stepTime=0;
  int step=0; 
  int numSteps;

  int fadePos=0;
  typedef struct {
    Tc *pTC;        // TC0, TC1, or TC2
    byte channel;   // 0-2
    byte output;    // 0 = A, 1 = B
  }  tTimerInfo;

  tTimerInfo timerLookup [14];

  uint32_t setupTimerPwm (byte pin, uint32_t frequency, unsigned dutyCycle);


   bool test=false;
  int pmwValue2 =0;
  int pmwValue3 =0;
  int pmwValue4 =0;
   int pmwValue5 =0;


  Adafruit_NeoPixel *strip;
};

#endif
