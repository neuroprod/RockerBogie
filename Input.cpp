#include "Input.h"
//pin9 rcbtn
//pin 12 lightbtn
//pin 11 lockalbtn
//locak pot A2
//lock pot A3
Input::Input()
{
  numSteps = 6;
  stepTime = 1000000 / 40 / numSteps;
  analogReadResolution(12);
  pinMode(11, INPUT);
  pinMode(9, INPUT);
  pinMode(12, INPUT);
}

void Input::update( int delta)
{
  currentTime += delta;
  if (currentTime > stepTime)
  {
    currentTime = 0;
    doStep() ;
    step++;
    step = step % numSteps;
  }
}

void Input::doStep()
{

  if (step == 0)
  {
    //checkRC
    hasRC = true;
    if(digitalRead(11)==LOW)
    {
       if(digitalRead(9)==LOW)
        {
        hasRC = false;
        }
     }else
     {
      hasRC = false;
      }
 
    
  }
  if (!hasRC)
  {
    if (step == 1)
    {

      mainControleFrontBackRaw = analogRead(A0)+30;
      mainControleFrontBack  = mapAnalog2((float) mainControleFrontBackRaw );
          
    }
    else if (step == 2)
    {
      mainControleLeftRightRaw = 4096 - (analogRead(A1)) -22;
      mainControleLeftRight  =  mapAnalog2((float) mainControleLeftRightRaw );
     
    }
    else if (step == 3)
    {
      powerRaw = analogRead(A3);
      power =0.125 +(powerRaw/4096.f *0.875);
    }
  }
  if (hasRC)
  {
    if (step == 1)
    {

      mainControleFrontBackRaw = 4096 - analogRead(A11) - 20;
      mainControleFrontBack  =  mapAnalog((float) mainControleFrontBackRaw );
    }
    else if (step == 2)
    {
      mainControleLeftRightRaw = analogRead(A10) + 40;
      mainControleLeftRight  = mapAnalog((float) mainControleLeftRightRaw );
    }
    else if (step == 3)
    {
      powerRaw = analogRead(A9);
      power =0.125 +(powerRaw/4096.f *0.875);
    }

  }


  if (step == 4)
  {
    updateSteeringAngles();
  }
  if (step == 5)
  {
    if(digitalRead(12))
    {
      
      lightCount++;
      if(lightCount==5)
      {
        lightOn = !lightOn;
        Serial.println(lightOn);
      }
      
     }else
     {
        lightCount =0;
     }
  }
}

void Input::updateSteeringAngles()
{
  float distance = ( pow((1 - abs(mainControleLeftRight)) , 8.f)) * 1000;

  turnDistance += (distance-turnDistance)/10;
  leftWheelAngle = atan2(0.5, turnDistance + 0.35) / 3.1415 * 180;
  rightWheelAngle = atan2(0.5, turnDistance - 0.35) / 3.1415 * 180;

  if (mainControleLeftRight < 0)
  {
    float temp = rightWheelAngle;
    rightWheelAngle= leftWheelAngle;
    leftWheelAngle = temp ;
    rightWheelAngle*=-1;
    leftWheelAngle*=-1;
  }
 
  
}
float Input::mapAnalog2(float value)
{
  value -= 2048;
value*=5;
  if (value < 0)
  {
    value += 40;
    value = constrain(value, -1800, 0);

  } else
  {
    value -= 40;
    value = constrain(value, 0, 1800);
  }
  return value / 1800.f;
}
float Input::mapAnalog(float value)
{
  value -= 2048;

  if (value < 0)
  {
    value += 40;
    value = constrain(value, -1800, 0);

  } else
  {
    value -= 40;
    value = constrain(value, 0, 1800);
  }
  return value / 1800.f;
}
