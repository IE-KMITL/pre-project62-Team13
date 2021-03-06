#include <HCSR04.h>
HCSR04 hc(10,11);
HCSR04 hc2(12,13); //initialisation class HCSR04 (trig,echo);
#define SwitchPin A3
#define ia1 2
#define ia2 3
#define ib1 4
#define ib2 5 
#define ic1 6 
#define ic2 7 
#define id1 8 
#define id2 9 
#define S2 A2
#define S3 A1
#define SBt A0 
#define maxSpd 255    // motor max speed
int SwitchState = 0;  
int T=0;
int B=0;
int sensorValue = analogRead(A0);
int speed = maxSpd;

void setup() {
  pinMode(ia1, OUTPUT);
  pinMode(ia2, OUTPUT);
  pinMode(ib1, OUTPUT);
  pinMode(ib2, OUTPUT);
  pinMode(ic1, OUTPUT);
  pinMode(ic2, OUTPUT);
  pinMode(id1, OUTPUT);
  pinMode(id2, OUTPUT);
  pinMode(S2,INPUT);
  pinMode(S3,INPUT);
  pinMode(SBt,INPUT);
  Serial.begin(9600);
  pinMode(SwitchPin, INPUT);
 
 
}

void loop() {
   if (SwitchState == HIGH) //attack
   {
  GoF();
  } 
 if (SwitchState == LOW) //defend
 {
  Defend();
  }
   
      
}
void Defend(){
   DSensor1();
   DSensor2();
}

void GoF(){
  Sensor1();
  Sensor2();
  Sensor3();
  DetectRed();
  DetectBlack();
  if(T=1 && (sensorValue>=1700&&sensorValue<=1850)) //Red
      {
        GoR();
      }
}
void GoR(){
  Sensor4();
  RSensor2();
  RSensor3();
  RDetectYellow();
  RDetectBlack();
  if(T=6)
      {
        Break();
      }
}
void DetectRed(){
  if(sensorValue>=1700&&sensorValue<=1850) 
      {
       
          Reward(speed);
          delay(100);
          T = 1;
      }
  }

void RDetectYellow(){
  if(sensorValue>=1900&&sensorValue<=2100)
      {
            
            Reward(speed); 
            delay(100);
            T+=1; 
      }
}
void DetectBlack(){
  if(sensorValue>=2400&&sensorValue<=2600) // detect black
      {  if(B%2==0){
         RTurnleft(speed);
         delay(100); 
          if(!(sensorValue>=2400&&sensorValue<=2600 )){
          B+=1;
          }
          }
          else if(B%2==1){
            RTurnRight(speed);
            delay(100);  
           if(!(sensorValue>=2400&&sensorValue<=2600 )){
           B+=1;
          }
           }
          
          else{
            Forward(speed);
          }
         
      }
}
void RDetectBlack(){
  if(sensorValue>=2400&&sensorValue<=2600) // detect black
      {  if(B%2==0){
         Turnleft(speed);
         delay(100);  
         if(!(sensorValue>=2400&&sensorValue<=2600 )){
          B+=1;
          }
      }
          else if(B%2==1){
            TurnRight(speed);
            delay(100);  
              if(!(sensorValue>=2400&&sensorValue<=2600 )){
                 B+=1;
           }
          }
          else{
            Reward(speed);
          }
         
      }
}

void Sensor1() //ultrasonic
{
   int speed = maxSpd;
  Serial.println(hc.dist() ); //showdistantfromfront
    if((hc.dist()>=10) && (hc.dist()<=15)){
       Slow(speed);}
    else if ((hc.dist()>=5) && (hc.dist()<10)){
        Break();}
    else if ((hc.dist()>=0) && (hc.dist()<5)){
        Reward(speed);}
    else{
        Forward(speed);}
}
void Sensor2(){
    int speed = maxSpd;
  if(digitalRead(S2)==LOW){
        Serial.println("sensor detected object from left side");
        delay(20);   
        Turnleft(speed);} 
   else{
    Forward(speed);
   }
}
void RSensor2(){
    int speed = maxSpd;
  if(digitalRead(S2)==LOW){
        Serial.println("sensor detected object from left side");
        delay(20);   
        RTurnRight(speed);} 
   else{
    Reward(speed);
   }
}
void Sensor3(){
    int speed = maxSpd;
  if(digitalRead(S3)==LOW){
        Serial.println("sensor detected object from right side");
        delay(20);   
        TurnRight(speed);} 
        else{
    Forward(speed);
        }
}
void RSensor3(){
    int speed = maxSpd;
  if(digitalRead(S3)==LOW){
        Serial.println("sensor detected object from right side");
        delay(20);   
        RTurnleft(speed);} 
        else{
   Reward(speed);
        }
}
void Sensor4() //ultrasonic
{
   int speed = maxSpd;
  Serial.println(hc2.dist() ); 
    if((hc2.dist()>=10) && (hc2.dist()<=15)){
       RSlow(speed);}
    else if ((hc2.dist()>=5) && (hc2.dist()<10)){
        Break();}
    else if ((hc2.dist()>=0) && (hc2.dist()<5)){
        Forward(speed);}
    else{
        Reward(speed);}
}
void DSensor1() //ultrasonic
{
   int speed = maxSpd;
  Serial.println(hc2.dist() ); 
    if((hc2.dist()>=0) && (hc2.dist()<=15)){
       Forward(speed);}
    else{
        Break();}
}
void DSensor2() //ultrasonic
{
   int speed = maxSpd;
  Serial.println(hc2.dist() ); 
    if((hc2.dist()>=0) && (hc2.dist()<=15)){
       Reward(speed);}
    else{
        Break();}
}

void Break() // motor break
{
  digitalWrite(ia1, HIGH);   
  digitalWrite(ia2, HIGH);  
  digitalWrite(ib1, HIGH);   
  digitalWrite(ib2, HIGH); 
  digitalWrite(ic1, HIGH);   
  digitalWrite(ic2, HIGH);   
  digitalWrite(id1, HIGH);   
  digitalWrite(id2, HIGH);  
}


void Forward(int speed) //goforward
{
  digitalWrite(ia1, LOW);   
  analogWrite(ia2, speed);   
  digitalWrite(ib1, LOW);   
  analogWrite(ib2, speed); 
  digitalWrite(ic1, LOW);   
  analogWrite(ic2, speed); 
  digitalWrite(id1, LOW);   
  analogWrite(id2, speed); 
  
}
void Slow(int speed) //goforwardwithSlowspeed
{
  digitalWrite(ia1, LOW);   
  analogWrite(ia2, speed*0.3);   
  digitalWrite(ib1, LOW);   
  analogWrite(ib2, speed*0.3); 
  digitalWrite(ic1, LOW);   
  analogWrite(ic2, speed*0.3); 
  digitalWrite(id1, LOW);   
  analogWrite(id2, speed*0.3); 
}
void RSlow(int speed) //RewardwithSlowspeed
{
  digitalWrite(ia2, LOW);   
  analogWrite(ia1, speed*0.3);   
  digitalWrite(ib2, LOW);   
  analogWrite(ib1, speed*0.3);  
  digitalWrite(ic2, LOW);   
  analogWrite(ic1, speed*0.3);  
  digitalWrite(id2, LOW);   
  analogWrite(id1, speed*0.3); 
}

void Reward(int speed) //goReward
{
  digitalWrite(ia2, LOW);   
  analogWrite(ia1, speed);   
  digitalWrite(ib2, LOW);   
  analogWrite(ib1, speed);  
  digitalWrite(ic2, LOW);   
  analogWrite(ic1, speed);  
  digitalWrite(id2, LOW);   
  analogWrite(id1, speed);  
}
void Turnleft(int speed) //turnleftandgoforward
{
  digitalWrite(ia1, LOW);   
  analogWrite(ia2, speed*0.7);
  digitalWrite(ib2, LOW);   
  analogWrite(ib1, speed*0.3);  
  digitalWrite(ic1, LOW);   
  analogWrite(ic2, speed*0.5);  
  digitalWrite(id1, LOW);   
  analogWrite(id2, speed*0.5);
}
void TurnRight(int speed) //turnrightandgoforward
{
  digitalWrite(ia2, LOW);   
  analogWrite(ia1, speed*0.3); 
  digitalWrite(ib1, LOW);   
  analogWrite(ib2, speed*0.7);  
  digitalWrite(ic1, LOW);   
  analogWrite(ic2, speed*0.5);  
  digitalWrite(id1, LOW);   
  analogWrite(id2, speed*0.5);
}
void RTurnleft(int speed) //turnleftandReward
{
  digitalWrite(ia1, LOW);   
  analogWrite(ia2, speed*0.5); 
  digitalWrite(ib2, LOW);   
  analogWrite(ib1, speed*0.5);  
  digitalWrite(ic1, LOW);   
  analogWrite(ic2, speed*0.7);  
  digitalWrite(id1, LOW);   
  analogWrite(id2, speed*0.3);
}
void RTurnRight(int speed) //turnrightandReward
{
  digitalWrite(ia1, LOW);   
  analogWrite(ia2, speed*0.5); 
  digitalWrite(ib2, LOW);   
  analogWrite(ib1, speed*0.5);  
  digitalWrite(ic1, LOW);   
  analogWrite(ic2, speed*0.3);  
  digitalWrite(id1, LOW);   
  analogWrite(id2, speed*0.7);
}
