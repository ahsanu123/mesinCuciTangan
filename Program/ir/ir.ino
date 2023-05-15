#include <SoftwareSerial.h>             //Library SoftwareSerial
#include <DFPlayer_Mini_Mp3.h>  //Library DFPlayer mini MP3

SoftwareSerial serial(10, 11);            //Deklarasi pin TX dan RX
int y=0,ir1,ir2,keadaan=0;
static unsigned long timer;
static unsigned long ulang;
int hey=1;
void setup() 
{
  serial.begin (9600);  
  mp3_set_serial (serial); 
  delay(5); 
  mp3_set_volume (100);           //Instruksi untuk mengatur volume musik
  delay(1000);
  Serial.begin(9600);
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(4,INPUT);
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);
  digitalWrite(A0,HIGH);
  digitalWrite(A1,HIGH);
  digitalWrite(A2,HIGH);
  mp3_play(3);
}

void loop() 
{
  int x=digitalRead(2);
  ir1 =digitalRead(3);
  ir2 =digitalRead(4);
  timer = millis();
  if(x==HIGH&&keadaan==0)
  {
    digitalWrite(A2,LOW);
    Serial.println(x);
    if(hey==1)mp3_play(1); 
    else if(hey==2)mp3_play(2);
    else if(hey==3)
    {
      mp3_play(3);
      hey=1;
    }
    hey++;
    while(millis()-timer < 7000)
    {
      Serial.println("Tunggu");
      ir1 = digitalRead(3);
      ir2 =digitalRead(4);
      if(ir1==LOW||ir2==LOW)
      {
          timer=millis();
          break;
      }
    }
    Serial.println("Sudah");
  }
  
  if (ir1==LOW||ir2==LOW||keadaan==1)
  {
    digitalWrite(A2,LOW);
    ulang=millis();
    while(ir1==LOW||ir2==LOW||keadaan==1)
    {
      ir1=digitalRead(3);
      ir2=digitalRead(4);
      if(keadaan==0)
      {
        mp3_play(4);
        keadaan=1;
      }
      if(millis()-ulang > 35000)
      {
        mp3_play(4);
        ulang=millis();
      }
      if(millis()-timer > 8000)
      {
        if(ir1==HIGH&&ir2==HIGH)
        {
          keadaan=3;
        }
        timer = millis();
      }
      if(ir1==LOW)
      {
        digitalWrite(A0,LOW);
        timer = millis();
      }
      else
      {
        digitalWrite(A0,HIGH);
      }
      if(ir2==LOW)
      {
        digitalWrite(A1,LOW);
        timer = millis();
      }
      else
      {
        digitalWrite(A1,HIGH);
      }
    }
  }
  ir1=digitalRead(3);
  ir2=digitalRead(4);
  if(keadaan==3&&ir1==HIGH&&ir2==HIGH)
  {
    digitalWrite(A2,LOW);
    mp3_play(5);
    keadaan=0;
    timer = millis();
    while(millis()-timer < 3000)
    {
      Serial.println("Tunggu");
      if(ir1==LOW||ir2==LOW)
      {
          timer=millis();
          break;
      }
    }
  }
  digitalWrite(A0,HIGH);
  digitalWrite(A1,HIGH);
  digitalWrite(A2,HIGH);
}
