

#include "Input.h"
#include "Motors.h"
#include "StepperMotor.h"
#include "Lights.h"

Input input;
Motors motors;

Lights lights;

StepperMotor steeringFL;
StepperMotor steeringFR;
StepperMotor steeringBL;
StepperMotor steeringBR;

unsigned long prevTime;
int delta =0;

volatile int stepper1Pos = 0;
volatile int stepper2Pos = 0;
volatile int stepper5Pos = 0;
volatile int stepper6Pos = 0;

void setup() {

  Serial.begin(9600);
  
  motors.setup();

  steeringFL.setup(37,35);
  steeringFR.setup(33,31);
  steeringBL.setup(29,27);
  steeringBR.setup(25,23);


  lights.setup();

  
  pinMode(22, INPUT);
  pinMode(24, INPUT);
  attachInterrupt(22, stepper1Change, RISING);

  pinMode(26, INPUT);
  pinMode(28, INPUT);
  attachInterrupt(26, stepper2Change, RISING);


  pinMode(30, INPUT);
  pinMode(32, INPUT);
  attachInterrupt(30, stepper5Change, RISING);


  pinMode(34, INPUT);
  pinMode(36, INPUT);
  attachInterrupt(34, stepper6Change, RISING);



  
  prevTime = micros();
}

void loop() {
  
   unsigned long curTime =micros();
    delta =0;
   if(prevTime<curTime)
   {
      delta =curTime - prevTime;
      
   }
   prevTime=curTime;
   
   input.update(delta);

  
   int ip = (float)input.mainControleFrontBack*64.0*input.power;
   motors.setMotorSpeeds(ip,ip,ip,ip,ip,ip);
   motors.update(delta);




   

   steeringFL.setTarget(input.leftWheelAngle);
   steeringFL.update(delta,-stepper1Pos,false);
   steeringFR.setTarget(input.rightWheelAngle);
   steeringFR.update(delta,-stepper2Pos,false);
   steeringBL.setTarget(input.leftWheelAngle);
   steeringBL.update(delta,stepper5Pos,false);
   steeringBR.setTarget(input.rightWheelAngle);
   steeringBR.update(delta,stepper6Pos,true);

   float maxAngleError =0;
   maxAngleError =max(maxAngleError,steeringFL.angleError);
   maxAngleError =max(maxAngleError,steeringFR.angleError);
   maxAngleError =max(maxAngleError,steeringBL.angleError);
   maxAngleError =max(maxAngleError,steeringBR.angleError);



   steeringFL.updateStep(delta,maxAngleError);
   steeringFR.updateStep(delta,maxAngleError);
   steeringBL.updateStep(delta,maxAngleError);
   steeringBR.updateStep(delta,maxAngleError);
   
   lights.update(delta,input.lightOn);
   
  // debug(delta);
}


void stepper1Change()
{
    if( digitalRead(24))
    {
       stepper1Pos++;
    }else 
    {
       stepper1Pos--;
    }
}
void stepper2Change()
{
    if( digitalRead(28))
    {
       stepper2Pos++;
    }else 
    {
       stepper2Pos--;
    }
}
void stepper5Change()
{
    if( digitalRead(32))
    {
       stepper5Pos++;
    }else 
    {
       stepper5Pos--;
    }
}
void stepper6Change()
{
    if( digitalRead(36))
    {
       stepper6Pos++;
    }else 
    {
       stepper6Pos--;
    }
}

int debugTime =0;
void debug(int delta)
{
 
  debugTime+=delta;
  if(debugTime>1000000/20)
  {
    debugTime =0;
    
 
   //Serial.println(input.power);
  /* Serial.print("fb: ");
    Serial.print(input.leftWheelAngle);
    Serial.print(" lr: ");
    Serial.println(steeringBL.angleError);
   /* Serial.print("s1: ");
    //Serial.println(stepper1Pos);

    //encoder 300 per rotation /2

    //float fullRot = 76.765625*300.f;
    float fullRot =23029;

    float rot1 = (float)stepper1Pos/fullRot *360;
     Serial.print(rot1);
     Serial.print(" ");

     float rot2 = (float)stepper2Pos/fullRot *360;
     Serial.print(rot2);
     Serial.print(" ");

    float rot5 = (float)stepper5Pos/fullRot *360;
     Serial.print(rot5);
     Serial.print(" ");
     
    float rot6 = (float)stepper6Pos/fullRot *360;
     Serial.print(rot6);
     Serial.println(" ");
      Serial.print(digitalRead(30));
       Serial.print(digitalRead(32));
     Serial.println(" ");
  // Serial.println(delta);*/
  }
  
}
