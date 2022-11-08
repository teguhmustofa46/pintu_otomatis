#define BLYNK_TEMPLATE_ID "TMPLgGCaglk6"
#define BLYNK_DEVICE_NAME "kontrol lampu"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define BLYNK_AUTH_TOKEN "6ZXLOv2X2Av2usny3kk0wfkX210K0iyD"
  char auth[] = "6ZXLOv2X2Av2usny3kk0wfkX210K0iyD";
  char ssid[] = "Plezz9";
  char pass[] = "adgjm1922";
#include <AccelStepper.h>
#define HALFSTEP 8
#define motorPin1 16
#define motorPin2 5
#define motorPin3 4
#define motorPin4 0
AccelStepper stepper1(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);
#define pro D6
int a,b,c,d,e;
#include <EEPROM.h>  // library untuk EEPROM
void setup()
{
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.println(".");
  }
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  pinMode(pro, INPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  Serial.begin(115200);
  stepper1.setMaxSpeed(1000.0);
  stepper1.setAcceleration(100.0);
  stepper1.setSpeed(200);
  EEPROM.begin(512);
  EEPROM.read(1);
  EEPROM.read(4);
  for(int i = 0; i < 512;i++)
{
EEPROM.write(i, 0);
}
}
void obstancle(){
  if(digitalRead(pro)==LOW){
    e=1;//objec terdeteksi
    EEPROM.write(1 , e);
    EEPROM.commit();
  }
  else if (digitalRead(pro)==HIGH){
      e=2;
  }
}
BLYNK_WRITE(V1){
    if (param.asInt()==HIGH){
      a=1;
      }
   else if(param.asInt()==LOW){
      a=2;
      }
  }
BLYNK_WRITE(V2){
    if (param.asInt()==HIGH){
      b=1;
      }
   else if(param.asInt()==LOW){
      b=2;
      }
  }
void tombol(){
    if((a==2)&&(b==1)){
      c=1;//Tombol Open
      EEPROM.write(4 , c); 
      EEPROM.commit();
      }
    else if ((a==1)&&(b==2)){
      c=2;//Tombol Close
      EEPROM.write(4 , c); 
      EEPROM.commit();
      }
    else{
      c=0;//posisi netral
      }
    }
void motor(){
  if(e==1){
    c=0;
    EEPROM.write(4 , c);
    EEPROM.commit();
    }
  if (c==1){
    e=0;
    EEPROM.write(1 , e);
    EEPROM.commit();
    }
  if(EEPROM.read(1)==1){
    stepper1.moveTo(-stepper1.currentPosition());
    }
   if(EEPROM.read(4)==1){
    stepper1.moveTo(2048);
    }
   if(EEPROM.read(4)==2){
    stepper1.moveTo(-stepper1.currentPosition());
    }
}
void loop(){
  obstancle();
  Blynk.run();
  stepper1.run();
  tombol();
  motor();
}
