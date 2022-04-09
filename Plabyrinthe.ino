#include <AFMotor.h>
#include <Ultrasonic.h>
#include <Servo.h>
Ultrasonic CapF(A0,A1), CapD(A5,A4), CapG(A2,A3);
AF_DCMotor motorD(3),motorG(4);
int pos =90,distanceG=0,distanceD=0,posD=0,posG=180,posF=90; 
Servo myservo; 
int Z, DistD=CapD.Ranging(CM),  DistG=CapG.Ranging(CM), VD, VG;

void setup() {
  // put your setup code here, to run once:

  motorD.setSpeed(200);
  motorG.setSpeed(200);
  motorD.run(RELEASE);
  motorG.run(RELEASE);
  Serial.begin(9600); 
  myservo.attach(10);
  myservo.write(pos);

}

void loop() {
  // put your main code here, to run repeatedly:
    DistD=CapD.Ranging(CM),  DistG=CapG.Ranging(CM);
//    Serial.print(" Face ");
//    Serial.println(CapF.Ranging(CM));
//    Serial.println("");
//    Serial.print(" Droite ");
//    Serial.println(DistD);
//    Serial.println("");
//    Serial.print(" Gauche ");
//    Serial.println(DistG);
//    Serial.println("");
    Z=DistD-DistG;
//    Serial.print("Z = ");
//    Serial.println(Z);

    VD = 128 - 2.8*Z;
    if(VD>255) VD=255;
    else if(VD<0) VD=0;
//    Serial.print("VD = ");
//    Serial.println(VD);
    VG = 128 + 2.8*Z;
    if(VG>255) VG=255;
    else if(VG<0) VG=0;
//    Serial.print("VG = ");
//    Serial.println(VG);
//    Serial.println("");
      if(CapF.Ranging(CM)>20)avancer();
      else arreter();
  }

 void avancer(){
  motorD.run(FORWARD);
  motorG.run(FORWARD);
  motorD.setSpeed(VD);
  motorG.setSpeed(VG);
}

void reculer(){
  motorD.run(BACKWARD);
  motorG.run(BACKWARD);
}

void droite(){
  motorD.run(RELEASE);
  motorG.run(FORWARD);
}
void Tdroite(){
  reculer();
  delay(100);
  droite();
  delay(350);
  arreter();
}

void gauche(){
  motorD.run(FORWARD);
  motorG.run(RELEASE);
}
void Tgauche(){
  reculer();
  delay(100);
  gauche();
  delay(1280);
  arreter();
}

void demiT(){
  reculer();
  delay(500);
  arreter();
  delay(100);
  gauche();
  delay(640);
  arreter();
}

void arreter(){
 motorD.run(RELEASE);
 motorG.run(RELEASE);
}
