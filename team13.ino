#include <HCSR04.h>
HCSR04 hc(9,10);
HCSR04 hc2(11,12); //initialisation class HCSR04 (trig,echo);
#define buttonPin 14
#define ia1 1
#define ia2 2
#define ib1 3
#define ib2 4 
#define ic1 5 
#define ic2 6 
#define id1 7 
#define id2 8 
#define S2 13
#define S3 0
#define SBt A0 
#define maxSpd 255    // motor max speed
int buttonState = 0;  


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
  pinMode(buttonPin, INPUT);
 
 
}

void loop() {
  int speed = maxSpd;
  int sensorValue = analogRead(A0);
  int T;
   if (buttonState == HIGH) //attack
   {
   if(sensorValue>=1900&&sensorValue<=2100) //detect green and returnT then Go plan goR
      {
          Serial.println(sensorValue); 
          delay(200);    
          Serial.println("Colour is Green ");
          delay(200);  
          Reward(speed);
          T = 1;
      }
      else if(sensorValue>=1150&&sensorValue<=1350)
      {
            Serial.println(sensorValue);
            delay(200);       
            Serial.println("Colour is Yellow");
            delay(200);  
            Forward(speed); 
            T = 2 ; 
      }
      else if(sensorValue>=2500&&sensorValue<=2700 ) // detect black
      {
         RTurnleft(speed);
         delay(200);  
         RTurnRight(speed);
         delay(200);  
         RTurnleft(speed);
         delay(200);  
      }
       else if(T=1 && (sensorValue>=1900&&sensorValue<=2100))
      {
        GoR();
      }
      else if(T=2 && (sensorValue>=1150&&sensorValue<=1350))
      {
        Break();
      }
      else
      {
        GoF();
      }
} 
 if (buttonState == LOW) //defend
 {
  Sensor5();
   Sensor6();
}
   
      
}

void GoF(){
  Sensor1();
  Sensor2();
  Sensor3();
}
void GoR(){
  Sensor4();
  RSensor2();
  RSensor3();
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
        RTurnleft(speed);} 
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
        RTurnRight(speed);} 
        else{
   Reward(speed);
        }
}
void Sensor4() //ultrasonic
{
   int speed = maxSpd;
  Serial.println(hc2.dist() ); //showdistantfromfront
    if((hc2.dist()>=10) && (hc2.dist()<=15)){
       RSlow(speed);}
    else if ((hc2.dist()>=5) && (hc2.dist()<10)){
        Break();}
    else if ((hc2.dist()>=0) && (hc2.dist()<5)){
        Forward(speed);}
    else{
        Reward(speed);}
}
void Sensor5() //ultrasonic
{
   int speed = maxSpd;
  Serial.println(hc2.dist() ); //showdistantfromfront
    if((hc2.dist()>=0) && (hc2.dist()<=15)){
       Forward(speed);}
    else{
        Break();}
}
void Sensor6() //ultrasonic
{
   int speed = maxSpd;
  Serial.println(hc2.dist() ); //showdistantfromfront
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
