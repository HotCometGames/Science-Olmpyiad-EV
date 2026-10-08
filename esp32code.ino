#include <Arduino.h>


const int motorPinFWD = 11;
const int breakDirection = 10;
const int forwardDirection = 9;




double distance = 4; // m
double mass = 0.1; // kg                figure out
double torque = 0.0363; // N*m          figure out
double wheelRadius = 0.04; // m         figure out
double mew = 0.3; // tile friction      figure out
double Vmax = 3.0; // m/s               figure out




double Fmotor = torque / wheelRadius;
double a_accel = (Fmotor / mass) - (mew * 9.8);
double a_brake = mew * 9.8;




double accelDist = (Vmax * Vmax) / (2 * a_accel);
double brakeDist = (Vmax * Vmax) / (2 * a_brake);
double coastDist = distance - (accelDist + brakeDist);




double t_accel = Vmax / a_accel;
double t_coast = coastDist / Vmax;
double t_total_on = t_accel + t_coast;




// time braking will take
double t_brake = Vmax / a_brake;




void setup() {
  Serial.begin(115200);


  pinMode(LED_BUILTIN, OUTPUT);




  pinMode(motorPinFWD, OUTPUT);
  pinMode(breakDirection, OUTPUT);
  pinMode(forwardDirection, OUTPUT);




  Serial.println("Starting run...");
  Serial.print("Accel time: "); Serial.println(t_accel);
  Serial.print("Coast time: "); Serial.println(t_coast);
  Serial.print("Brake time: "); Serial.println(t_brake);


  delay(2000);
  //driveFor2Sec();
 
  // Accelerate
  //driveForward();
  //delay(t_accel * 1000);




  // Coast
  //driveForward();
  digitalWrite(forwardDirection, HIGH);
  digitalWrite(breakDirection, LOW);
  digitalWrite(motorPinFWD, HIGH);
  delay(1500);
  //delay(t_coast * 1000);




  // Brake
  driveReverse();
  delay(800); // ms — tune this


  stopMotor();




  Serial.println("Done!");
}




void loop() { //use to test if connected


  digitalWrite(LED_BUILTIN, HIGH); // Turn LED on
  //digitalWrite(motorPinFWD, HIGH);
  delay(3000); // Wait for 1 second
  digitalWrite(LED_BUILTIN, LOW); // Turn LED off
  //digitalWrite(motorPinFWD, LOW);
  delay(1000); // Wait for 1 second


}




void driveForward() {
  digitalWrite(forwardDirection, HIGH);
  digitalWrite(breakDirection, LOW);
  digitalWrite(motorPinFWD, HIGH);
}




void driveReverse() {
  digitalWrite(forwardDirection, LOW);
  digitalWrite(breakDirection, HIGH);
  digitalWrite(motorPinFWD, HIGH);
}




void brakeHold() {
  digitalWrite(motorPinFWD, HIGH);
}




void stopMotor() {
  digitalWrite(motorPinFWD, LOW);
}


void driveFor2Sec()
{
  driveForward();
  delay(2000);
}



