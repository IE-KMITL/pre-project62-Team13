#include <HCSR04.h>
HCSR04 hc(1,2); //initialisation class HCSR04 (trig,echo);
#define ia1 3 //left 1
#define ia2 4 //left 2
#define ib1 5 //right 1
#define ib2 6 //right 2
#define ic1 7 //front 2
#define ic2 8 //front 2
#define S2 11
#define S3 12
#define maxSpd 255    // motor max speed


void setup() {
  pinMode(ia1, OUTPUT);
  pinMode(ia2, OUTPUT);
  pinMode(ib1, OUTPUT);
  pinMode(ib2, OUTPUT);
  pinMode(ic1, OUTPUT);
  pinMode(ic2, OUTPUT);
  pinMode(S2,INPUT);
  pinMode(S3,INPUT);
  Serial.begin(9600);
 
 
}

void loop() {
  int speed = maxSpd;
  Sensor1();
  Sensor2();
  Sensor3();


}
void Sensor1() //ultrasonic
{
   int speed = maxSpd;
  Serial.println(hc.dist() ); //showdistantfromfront
    if((hc.dist()>=5) && (hc.dist()<=10)){
       Slow(speed);}
    else if ((hc.dist()>=3) && (hc.dist()<5)){
        Break();}
    else if ((hc.dist()>=0) && (hc.dist()<3)){
        Reward(speed);}
    else{
        Forward(speed);}
}
void Sensor2(){
    int speed = maxSpd;
  if(digitalRead(S2)==LOW){
        Serial.println("sensor detected object from left side");
        delay(200);   
        Turnleft(speed);} 
   else{
    Forward;
   }
}
void Sensor3(){
    int speed = maxSpd;
  if(digitalRead(S3)==LOW){
        Serial.println("sensor detected object from right side");
        delay(200);   
        TurnRight(speed);} 
        else{
    Forward(speed);
        }
}

void Break() // motor break
{
  digitalWrite(ia1, HIGH);   
  digitalWrite(ia2, HIGH);  
  digitalWrite(ib1, HIGH);   
  digitalWrite(ib2, HIGH); 
  digitalWrite(ic1, HIGH);   
  digitalWrite(ic2, HIGH);   
}


void Forward(int speed) //goforward
{
  digitalWrite(ia1, LOW);   
  analogWrite(ia2, speed);   
  digitalWrite(ib1, LOW);   
  analogWrite(ib2, speed); 
  digitalWrite(ic1, LOW);   
  analogWrite(ic2, speed); 
  
}
void Slow(int speed) //goforwardwithSlowspeed
{
  digitalWrite(ia1, LOW);   
  analogWrite(ia2, speed*0.3);   
  digitalWrite(ib1, LOW);   
  analogWrite(ib2, speed*0.3); 
  digitalWrite(ic1, LOW);   
  analogWrite(ic2, speed*0.3); 
}

void Reward(int speed) //goReward
{
  digitalWrite(ia2, LOW);   
  analogWrite(ia1, speed);   
  digitalWrite(ib2, LOW);   
  analogWrite(ib1, speed);  
  digitalWrite(ic2, LOW);   
  analogWrite(ic1, speed);  
}
void Turnleft(int speed) //turnleftandgoforward
{
  digitalWrite(ia1, LOW);   
  analogWrite(ia2, speed*0.7); //leftforward
  digitalWrite(ib2, LOW);   
  analogWrite(ib1, speed*0.3);  //rightreward
  digitalWrite(ic1, LOW);   
  analogWrite(ic2, speed*0.5);  //frontforward
}
void TurnRight(int speed) //turnrightandgoforward
{
  digitalWrite(ia2, LOW);   
  analogWrite(ia1, speed*0.3); //leftreward
  digitalWrite(ib1, LOW);   
  analogWrite(ib2, speed*0.7);  //rightforward
  digitalWrite(ic1, LOW);   
  analogWrite(ic2, speed*0.5);  //frontforward
}