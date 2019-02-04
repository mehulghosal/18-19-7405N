#include "main.h"

//OPCONTROL//

void testfunct();
void intake(int toggle);
void reaper(int toggle);
void flywheel(bool toggle, int speed = 200);
void old_flywheel(bool toggle, int speed = 127);
// void moveTo(double d);
void display();
void moveTo(double d);
void moveTo(double d, double speed);
void turn(double d, int i); //1 FOR LEFT; 0 FOR RIGHT
void rightTurn(double d, int speed = 100);
void leftTurn(double d, int speed = 100);
int getAutonState();
bool getParkState();
void moveReaper(int dist, bool delay);
void arm(bool toggle);
int getLimit();
void changeArm(int val);
int targetspeed = 0;
double getflywheelspeed();
void setFlywheelspeed(int speed);
double previousError = 0;
bool runFlywheel = true;
//AUTONS//
double flywheelVelocity = 0;

double flywheelaccel(double error) {
  double integral = 0;
  double derivative = 0;

  integral += error;
  derivative = error - previousError;
  double pid = (error * .8) + (integral * 0) + (derivative * .4);

  previousError = error;

  pros::lcd::print(1, "PID %f",pid);
  display();
  pros::lcd::print(7,"%d",targetspeed);
  return pid;
}



void maintainflywheel(void * a) {
  while (true) {
    if(runFlywheel){
      if (targetspeed == 0) {
        setFlywheelspeed(0);
      }
      else {
        double acceleration = flywheelaccel((targetspeed - getflywheelspeed()) * (127.0 / 200));

        flywheelVelocity = std::min(130.0 , flywheelVelocity + (acceleration * 0.020));

        pros::lcd::print(3, "Flywheel Vel: %f", flywheelVelocity);
      }

      setFlywheelspeed(flywheelVelocity);
      pros::c::delay(20);
    }
    else{
      setFlywheelspeed(125);
    }
  }
}
void changeFlywheel(bool change){
  runFlywheel = change;
}

void topBlue() { // starts about two inches in front of the wall, and 2 inches left of the mat's edge (on the left side)
  pros::lcd::print(0, "INIT Auton1");
  //turn on flywheel and intake on first
  targetspeed = 195;
  intake(1);

  //move forward to ball in front
  moveTo(2800);

  //move back and allign top flag
  moveTo(-2550);
  rightTurn(92, 80);

  //	moveTo(-400); // adjust this for top flag hitting

  //shoot top flag
while(getflywheelspeed() < 195);
  reaper(1);
  pros::c::delay(400);
  reaper(0);

  //allign and shoot middle flag
  moveTo(1700);
  reaper(1);
  while (getLimit() != 1);

  pros::c::delay(500);
  reaper(0);

  //allign and ram bottom flag
  rightTurn(15);
  moveTo(1400);
  moveTo(-1500, 90);
  leftTurn(100);
  intake(-1);
  moveTo(1400, 60);
  moveTo(-200, 90);
  intake(0);
  rightTurn(50);
  moveTo(4000, 127);

  //park
  /*moveTo(-1200);
  leftTurn(14);
  moveTo(-1700 - 600);
  leftTurn(90);
  moveTo(2500);*/

}
void backRed(){
  intake(1);
  targetspeed = 195;
  moveTo(2800, 100);
  pros::c::delay(500);
  moveTo(-2500, 100);
  leftTurn(61);
while(getflywheelspeed() < 195);
    display();
  reaper(1);
  pros::c::delay(400);

  targetspeed = 180;
  while (getLimit() != 1);
  reaper(0);
   // second shot speed
  while(getflywheelspeed() > 184);
    display();
    // second shot delay
  reaper(1);
  pros::c::delay(400);
if(getParkState())
{

    moveTo(200, 25);
    leftTurn(35);
    moveTo(1350, 25);
    rightTurn(92);
    intake(-1);
    moveTo(2000, 127);

}

}

void armBackRed() { // this is actually back red lmao

  targetspeed = 191;
  moveTo(250, 40);
  leftTurn(20);
  intake(1);
  changeArm(-127);
  moveTo(1000);
  changeArm(127);
  pros::c::delay(300); // 191 for top flag 180 to shoot middle flag	changeArm(0);
  changeArm(0);
  moveTo(-1000);
  leftTurn(36);
  //
  reaper(1);
  pros::c::delay(600);
  while (getLimit() != 1);
  reaper(0);
  targetspeed = 180;
  pros::c::delay(900);
  reaper(1);
  pros::c::delay(500);

  rightTurn(56);
  targetspeed = 200;
  moveTo(3000);
  while (getLimit() != 1);
  reaper(0);
  moveTo(-500);
  leftTurn(53);
  reaper(1);

  /*
  reaper(0);
  rightTurn(60);
  moveTo(1450);
  rightTurn(45);
  moveTo(1450);
  changeArm(127);
  pros::c::delay(500);
  changeArm(0);
  moveTo(-1450);
  leftTurn(45); // 45 to straighten + 30 to flag
  moveTo(1450);
  leftTurn(30);
  reaper(1);
  while(getLimit() != 1);
  reaper(0);
  */

}


void topRed() {
  pros::lcd::print(0, "INIT auton2");

  //turn on flywheel
  targetspeed = 195;
  intake(1);

  //move forward to ball
  moveTo(3000);

  //move back and allign top flag
  moveTo(-2600);
  leftTurn(92);

  //shoot top flag
  while(getflywheelspeed() < 195);
  reaper(1);
  pros::c::delay(400);
  reaper(0);

  //allign and shoot middle flag
  moveTo(2000);
  reaper(1);
  while (getLimit() != 1);
  pros::c::delay(400);
  reaper(0);

  //allign and ram bottom flag
  leftTurn(15);
  moveTo(1200);
  moveTo(-1500);
  rightTurn(112);
  intake(-1);

  moveTo(1400, 60);
  pros::c::delay(50);
  moveTo(-200, 127);
  leftTurn(38);
  moveTo(4000, 127);

  //park
  /*moveTo(-1200);
  rightTurn(14);
  moveTo(-1700 - 600);
  rightTurn(90);
  moveTo(2500);*/

}

void newTopRedCauseImBored(){
  targetspeed = 191;
  intake(1);
  changeArm(-127);
  moveTo(1000,70);
  changeArm(0);
  moveTo(-1000, 60);
  leftTurn(128);
  changeArm(25);
  moveTo(500);
  changeArm(0);
  reaper(1);
  while(getLimit() != 1);
  pros::c::delay(400);
  reaper(1);
  moveTo(1300);
  while(getLimit() != 1);
  pros::c::delay(400);
  reaper(1);
  moveTo(1500);

}

void backBlue() {
  pros::lcd::print(0, "INIT auton3");

  //turn on flywheel and intake first
/*  targetspeed = 200;
  pros::c::delay(7500);

  targetspeed = 180;
  pros::c::delay(1500);
  pros::lcd::print(6, "changing speed");
  pros::c::delay(9500);

*/
targetspeed = 200;
intake(1);
  pros::c::delay(1500);

  //move forward to ball
  moveTo(3000); //this is pretty close - 2900 is perfect to intake the ball
  pros::c::delay(750);

  //allign top flag
  moveTo(-2750);
  rightTurn(55);
  moveTo(-200, 25);
while(getflywheelspeed() < 194);
  //shoot top flag
  display();
  reaper(1);
  pros::c::delay(300);

  targetspeed = 180;
  while (getLimit() != 1);
  reaper(0);

  //shoot middle flag
while(getflywheelspeed() > 184);
  display();
  reaper(1);
  pros::c::delay(500);

  //park
  if (getParkState()) {
    moveTo(200, 25);
    rightTurn(35);
    moveTo(1350, 25);
    leftTurn(90);
    intake(-1);
    moveTo(2000, 127);
  }

}



void autonskills() {
  pros::lcd::print(0, "INIT autonskills");
  targetspeed = 200;
  intake(1);

  moveTo(2500); //this is pretty close - 2900 is perfect to intake the ball

  // intakes second ball
  reaper(1);
  while (getLimit() != 1);
  reaper(0);
  intake(-1);
  pros::c::delay(200);
  // moves to flip first cap
  moveTo(1000, 40);
  moveTo(-3200);
  leftTurn(90, 30);
  moveTo(3300);

  while(getflywheelspeed() < 195);
  reaper(1);
  pros::c::delay(400);
  reaper(0);

  //allign and shoot middle flag
  moveTo(2000);
  reaper(1);
  while (getLimit() != 1);
   pros::c::delay(400);
  reaper(0);

  leftTurn(20, 20);
  // scores low flag
  moveTo(1100, 40);
  moveTo(-1100, 40);
  rightTurn(15, 20);
  // goes to cube
  moveTo(-2000);
  rightTurn(93, 40);
  intake(1);
  moveTo(2300, 40);
  // intakes ball
  while (getLimit() != 1);
  reaper(0);
  intake(-1);
  pros::c::delay(1000);
  // flips second cap
  moveTo(1000, 20);

  leftTurn(95, 40);
  moveTo(1650, 40);
  reaper(1);
  pros::c::delay(1000);
  leftTurn(15, 20);
  moveTo(1000);
  moveTo(-1400);
  rightTurn(108, 20);
  intake(-1);
  moveTo(1500);
  moveTo(2000, 40);
  moveTo(-1300, 40);
  rightTurn(90, 20);
  moveTo(1400);
  leftTurn(92, 40);
  moveTo(1300);
  rightTurn(92, 40);
  moveTo(1600);
  rightTurn(92, 40);
  moveTo(-1000);
  moveTo(6300, 127 );

  /*moveTo(1000);
  leftTurn(90, 20);
  moveTo(1000);
  rightTurn(90, 20);
  moveTo(1000);
  rightTurn(90, 20);
  moveTo(1000);
  moveTo(-500);
  moveTo(5000, 127);
  */
}

void checkAutonSpeed() {
  targetspeed = 160;
}

void test() {
  moveTo(2600);
  //right turn by 90 degrees
  turn(90, 0);
}
// std::string autonstateNames[] = {"top blue", "top red", "back blue", "back red", "codeSkills"};
void autonomous() {
  pros::Task flyWhlPID(maintainflywheel);

  int aS = getAutonState();
  if (aS == 1) {
    autonskills(); // top blue
  } else if (aS == 2) {
    topRed(); // top red
  } else if (aS == 3) {
    backBlue(); // back blue
  } else if (aS == 4) {
    backRed(); // back red
  } else if (aS == 5) {
    autonskills();
  }
  //auton1();
  //test();
}
