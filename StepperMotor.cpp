#include "StepperMotor.h"


StepperMotor::StepperMotor() {}

void StepperMotor::setup(int _stepPin, int _dirPin)
{
  dirPin = _dirPin;
  stepPin = _stepPin;
  pinMode(dirPin , OUTPUT);
  pinMode(stepPin, OUTPUT);
  digitalWrite(dirPin, LOW);
  digitalWrite(stepPin, LOW);

}
void StepperMotor::update( int delta, int currentPos,boolean debug)
{
  updateTime += delta;
  if ( updateTime > 50000) {

    float Kp =100;
    float accel = 40;
    float maxSpeed = 550000;


    currentAngle = (float) currentPos / (76.765625f * 300.f) * 360.f ;

    angleError =abs( currentAngle - targetAngle);
    if(angleError<0.5)angleError=0;
    currentSpeed = (currentAngle - prevAngle) / ((float) updateTime / 1000000.0f); //deg/sec

    float targetSpeed  = (targetAngle - currentAngle ) * Kp;
    float speedError  = (currentSpeed - targetSpeed) ;
   
    if (speedError < 0)
    {
      if (speedError < -accel){
        speedError = -accel;
         
      }

    } else
    {
      if (speedError > accel){
        speedError = accel;
       
      }
    }

    targetMSpeed = currentSpeed - speedError;
    targetMSpeed*=40; 
    if (targetMSpeed > maxSpeed){
      targetMSpeed = maxSpeed;
     
    };
   



    if (targetMSpeed < 0)
    {
      targetMSpeed *= -1;
      digitalWrite(dirPin, LOW);

    } else
    {
      digitalWrite(dirPin, HIGH);

    }
    if(debug){
      
    }


    float stepDeg =180.f/360.f;
    float stepsSec  =stepDeg * targetMSpeed;
    stepPauze =1000000/ stepsSec  ;
if(debug){
      
    }
    prevAngle = currentAngle;
    updateTime  = 0;
  }

  
}
void StepperMotor::updateStep(int delta,float maxAngleError)
{

  if (targetMSpeed == 0)return;
  if(angleError==0)return;
  
  float factor =maxAngleError/angleError;
  
  currentTime+=delta;
  float stime=stepPauze*factor;

  if( stepState)stime =100;
  if(currentTime> stime)
  {
      currentTime=0;

      stepState= !stepState;
      digitalWrite(stepPin,stepState);
  } 

}
void StepperMotor::setTarget(float _targetAngle)
{
  targetAngle = _targetAngle;
  
}
