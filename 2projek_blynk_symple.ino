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
int a;
int b;
int c;
int d;
int e;
#include <EEPROM.h>  // library untuk EEPROM
//#define EEPROM_SIZE 256  //Ukuran size pada EEPROM
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
  EEPROM.read(1);                    //menginputkan nilai ke EEPROM dengan ADDRES (1);
  EEPROM.read(4);                    //menginputkan nilai ke EEPROM dengan ADDRES (1);
  for(int i = 0; i < 512;i++)
{
EEPROM.write(i, 0);
}
}
void obstancle(){
  if(digitalRead(pro)==LOW){
    digitalWrite(D4, HIGH);
    e=1;
    Serial.print("nilai E = ");
    Serial.println(e);
    EEPROM.write(1 , e);              //memasukkan Nilai "b" kedalam EEPROM dengan Address (1)
    EEPROM.commit();
  }
  else if (digitalRead(pro)==HIGH){
      e=2;
    Serial.print("nilai E = ");
    Serial.println(e);
    Serial.println("Object no terdeteki");
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
  if(EEPROM.read(1)==1){
    d=2;
    stepper1.moveTo(-stepper1.currentPosition());
    }
   if(EEPROM.read(4)==1){
    d=1;
    stepper1.moveTo(6144);
    }
   if(EEPROM.read(4)==2){
    d=2;
    stepper1.moveTo(-stepper1.currentPosition());
    }
  
/* if(e==2){
        //d=2;//pintu tertutup
        //stepper1.moveTo(6144);
         if(EEPROM.read(4)==1){
          d=1;//pintu terbuka
          //stepper1.moveTo(-stepper1.currentPosition());
          }
        else if(EEPROM.read(4)==2){
        d=2;//pintu tertutup
        //stepper1.moveTo(6144);
    }
    }

    else if (EEPROM.read(1)==1){
      d=2;
      }*/

}
void loop(){
  obstancle();
  Blynk.run();
  stepper1.run();
  tombol();
  motor();
  Serial.print("Nilai C = ");
  Serial.println(c);
  Serial.print("Nilai D = ");
  Serial.println(d);
  Serial.print("Nilai EEPROM E=");
  Serial.println(EEPROM.read(1));
  Serial.print("Nilai EEPROM C=");
  Serial.println(EEPROM.read(4));
}
