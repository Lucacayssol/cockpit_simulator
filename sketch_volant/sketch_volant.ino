#include <Wire.h>
#include <Joystick.h>

Joystick_ Joystick;

const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
int angle;

float filteredAngle =0;        // valeur lissée (float pour précision du filtre)
const float alpha = 0.35;       // 0.05 = très lisse mais lent, 0.5 = réactif mais moins lisse
int centre_deadzone = 30;       //Deadzone centrale
int lastSentAngle = 0;          // dernière valeur envoyée au joystick
const int deadzone = 3;         // seuil en dessous duquel on ignore le changement

void setup(){
  pinMode(10,OUTPUT);
  pinMode(9,INPUT);
  digitalWrite(10,HIGH);
  delay(3000);
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(9600);
  Joystick.begin();
}

void loop(){
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();
  AcY=Wire.read()<<8|Wire.read();
  AcZ=Wire.read()<<8|Wire.read();
  Tmp=Wire.read()<<8|Wire.read();
  GyX=Wire.read()<<8|Wire.read();
  GyY=Wire.read()<<8|Wire.read();
  GyZ=Wire.read()<<8|Wire.read();

  int rawAngle = map(AcY,-4800,5400,256,768);
  rawAngle = constrain(rawAngle,256,768);

  // 1) Filtre passe-bas
  filteredAngle = alpha * rawAngle + (1 - alpha) * filteredAngle;

  // 2) Deadzone
  if (abs((int)filteredAngle - lastSentAngle) > deadzone) {
    lastSentAngle = (int)filteredAngle;
    lastSentAngle = map(lastSentAngle,256,768,0,1023);
    lastSentAngle = constrain(lastSentAngle,0,1023);
    if (lastSentAngle>(512-centre_deadzone) and lastSentAngle<(512+centre_deadzone)){
      lastSentAngle=512;
    }
    Joystick.setXAxis(lastSentAngle);
  }

  Joystick.setButton(1, analogRead(9));

  Serial.print("raw="); Serial.print(rawAngle);
  Serial.print(" | filtered="); Serial.print(filteredAngle);
  Serial.print(" | sent="); Serial.println(lastSentAngle);

  delay(10);
}
