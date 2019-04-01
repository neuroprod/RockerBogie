#include "Motors.h"
//17 back
//16 mid
//15 front
Motors::Motors()
{
  
}
void Motors::setup()
{
  
  numSteps=6;
  stepTime =1000000 /60/numSteps;

  Serial1.begin(9600);
   pinMode(17, OUTPUT);
   pinMode(16, OUTPUT);
   pinMode(15, OUTPUT);
 }
void Motors::update( int delta)
{
   currentTime+=delta;
  if(currentTime>stepTime)
  {
    currentTime=0;
    doStep() ;
    step++;
    step=step%numSteps;
  } 
}

void Motors::setMotorSpeeds(int fl,int fr,int ml,int mr,int bl,int br)
{  
  frontLeft=fl;
  frontRight=fr;
  midLeft=ml;
  midRight=mr;
  backLeft=bl;
  backRight=br;
}

void Motors::doStep()
{
   
    if(step==0)
    {
      digitalWrite(15,LOW);
      digitalWrite(17,HIGH);
      byte sendb  =64+ frontLeft;
      Serial1.write(sendb);
    } 
    else if (step==1)
    {
      byte sendb  =191+ frontRight;
      Serial1.write(sendb);
    } 
    else if(step==2)
    {
      digitalWrite(17,LOW);
      digitalWrite(16,HIGH);
      byte sendb  =64+ midLeft;
      Serial1.write(sendb);
    }  
    else if(step==3)
    {
       byte sendb  =191 + midRight;
       Serial1.write(sendb);
     }
   else if(step==4)
    {
      digitalWrite(16,LOW);
      digitalWrite(15,HIGH);
      byte sendb  =64+ backLeft;
      Serial1.write(sendb);
    }  
    else if(step==5)
    {
       byte sendb  =191 + backRight;
       Serial1.write(sendb);
    }
  
}
