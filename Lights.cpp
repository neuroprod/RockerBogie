#include "Lights.h"

Lights::Lights()
{

}
void Lights::setup()
{
  strip = new Adafruit_NeoPixel(12, 8, NEO_GRB + NEO_KHZ800);
  numSteps = 6;
  stepTime = 1000000 / 31 / numSteps;

  int count = 0;

  timerLookup[count++] = {NULL, 0, 0}; // 0
  timerLookup[count++] = {NULL, 0, 0};
  timerLookup[count++] = {TC0, 0, 0}; // pin 2 = TIOA0
  timerLookup[count++] = {TC2, 1, 0}; // pin 3 = TIOA7
  timerLookup[count++] = {TC2, 0, 1}; // pin 4 = TIOB6
  timerLookup[count++] = {TC2, 0, 0}; // pin 5 = TIOA6
  pinMode(4, OUTPUT);

  analogWrite (2, 128);
  analogWrite (3, 128);
  analogWrite (4, 128);
  analogWrite (5, 128);
  setupTimerPwm (2, 2000, 128);
  setupTimerPwm (3, 2000, 128);
  setupTimerPwm (4, 2000, 128);
  setupTimerPwm (5, 2000, 128);


  strip->begin();
  strip->setBrightness(100);
  strip->show();
}



void Lights::update( int delta,bool lightOn)
{
  currentTime += delta;
  if (currentTime > stepTime)
  {
    currentTime = 0;
    doStep(lightOn) ;
    step++;
    step = step % numSteps;
  }
}



void Lights::doStep(bool lightOn)
{

  if (step == 0)
  {



    pmwValue3 = (pmwValue3 + 5) % 512;
    int val = max(3, abs (pmwValue3 - 255));
    if(lightOn){
      setupTimerPwm (2, 1000, 255);
      }else{
    setupTimerPwm (2, 1000, 5);
      }
    setupTimerPwm (4, 1000, val);
    setupTimerPwm (3, 1000, val);
    setupTimerPwm (5, 1000, val);

  }
  else if (step == 1)
  {


    fadePos++;
    fadePos = fadePos % 24;
    int pos = abs(  fadePos - 12);
    for (int i = 0; i < strip->numPixels(); i++) {
      if (i == pos)
      {
        strip->setPixelColor(i, strip->Color(255, 160, 0));
      }else if (i == pos-1 || i == pos+1)
      {
        strip->setPixelColor(i, strip->Color(50, 40, 0));
      }
      else
      {
        strip->setPixelColor(i, strip->Color(0, 0, 0));
      }
    }

  }
  else if (step == 2)
  {

    strip->show();
  }
  else if (step == 3)
  {
    // setupTimerPwm (4, 2000, abs( pmwValue2-256));

  }
  else if (step == 4)
  {
    // setupTimerPwm (5, 2000, abs( pmwValue2-256));
  }
  else if (step == 5)
  {

  }

}


uint32_t Lights::setupTimerPwm (byte pin, uint32_t frequency, unsigned dutyCycle)
{
  uint32_t count = VARIANT_MCK / 2 / frequency;
  tTimerInfo *pTimer = &timerLookup[pin];

  if (pTimer != NULL)
  {
    TC_SetRC (pTimer->pTC, pTimer->channel, count);
    if (pTimer->output == 0)
      TC_SetRA (pTimer->pTC, pTimer->channel, count * dutyCycle / 256);
    else
      TC_SetRB (pTimer->pTC, pTimer->channel, count * dutyCycle / 256);

    return count;
  }
  else
    return 0;
}
