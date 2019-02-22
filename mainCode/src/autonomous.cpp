#include "main.h"

//OPCONTROL//
void chassisSet(int m1, int m2);
void reapermove(int val);
void setBrakehold();
void testfunct();
void intake(int toggle);
void reaper(int toggle, int speed = 127);
void flywheel(bool toggle, int speed = 200);
void display();
void moveTo(double d);
void moveTo(double d, double speed);
void turn(double d, int i); //1 FOR LEFT; 0 FOR RIGHT
void rightTurn(double d, int speed = 100);
void leftTurn(double d, int speed = 100);
int getAutonState();
bool getParkState();
void moveReaper(int dist, bool delay);
void arm(int val);
int getLimit();
void changeArm(int val);
int targetspeed = 0;
double getflywheelspeed();
void setFlywheelspeed(int speed);
double previousError = 0;
bool runFlywheel = true;
//AUTONS//
double flywheelVelocity = 0;

double flywheelaccel(double error)
{
	double integral = 0;
	double derivative = 0;

	integral += error;
	derivative = error - previousError;
	double pid = (error * 1) + (integral * 0) + (derivative *.4);

	previousError = error;

	pros::lcd::print(1, "PID %f", pid);
	display();
	pros::lcd::print(7, "%d", targetspeed);
	return pid;
}

void maintainflywheel(void *a)
{
	while (true)
	{
		if (runFlywheel)
		{
			if (targetspeed == 0)
			{
				setFlywheelspeed(0);
			}
			else
			{
				double acceleration = flywheelaccel((targetspeed - getflywheelspeed()) *(127.0 / 200));

				flywheelVelocity = std::min(130.0, flywheelVelocity + (acceleration * 0.020));

				pros::lcd::print(3, "Flywheel Vel: %f", flywheelVelocity);
			}

			setFlywheelspeed(flywheelVelocity);
			pros::c::delay(20);
		}
		else
		{
			setFlywheelspeed(125);
		}
	}
}
void changeFlywheel(bool change)
{
	runFlywheel = change;
}

void topRed()
{ // starts about two inches in front of the wall, and 2 inches left of the mat's edge (on the left side)
	pros::lcd::print(0, "INIT Auton1");
	//turn on flywheel and intake on first
	setFlywheelspeed(127);
	intake(1);
	pros::c::delay(300);
	//move forward to ball in front
	moveTo(2800);

	//move back and allign top flag
	moveTo(-2550);
	leftTurn(94.4, 80);

	//	moveTo(-400); // adjust this for top flag hitting

	//shoot top flag
	while (getflywheelspeed() < 193);
	reaper(1, 127);
	pros::c::delay(200);
	moveTo(1400, 127);

	//allign and shoot middle flag


	reaper(0);

	//allign and ram bottom flag
	leftTurn(17);
	moveTo(800);
	moveTo(-800);
	rightTurn(2);



	if (true)
	{
		moveTo(-3500);
		rightTurn(95);
		moveTo(3600);


	}
	else
	{
		//cap and midle flag
		moveTo(-200);
		rightTurn(100);
		intake(-1);
		moveTo(1400, 60);
		intake(0);
	moveTo(-200);

		intake(1);
		reaper(1);
		leftTurn(45);
		moveTo(4000, 127);
	}

}


void topBlue()
{ // starts about two inches in front of the wall, and 2 inches left of the mat's edge (on the left side)
	pros::lcd::print(0, "INIT Auton1");
	//turn on flywheel and intake on first
	setFlywheelspeed(127);
	intake(1);

	//move forward to ball in front
	moveTo(2800);

	//move back and allign top flag
	moveTo(-2560);
	rightTurn(94, 80);

	//	moveTo(-400); // adjust this for top flag hitting

	//shoot top flag
	while (getflywheelspeed() < 193);
	reaper(1, 127);
	pros::c::delay(200);
	moveTo(1400, 127);

	//allign and shoot middle flag


	reaper(0);

	//allign and ram bottom flag
	rightTurn(16);
	moveTo(750);
	pros::c::delay(100);
	moveTo(-750);
	leftTurn(3);



	if(true)
	{
		moveTo(-3400);
		leftTurn(91);
		moveTo(3500, 127);


	}
	else
	{
		//cap and midle flag

		moveTo(-100);
		leftTurn(100);
		intake(-1);
		moveTo(1400, 60);
		moveTo(-200, 90);
		intake(1);
		reaper(1);
		rightTurn(41);
		moveTo(4000, 127);
	}

}

void backRedcap()
{

	setFlywheelspeed(127);

	intake(1);


	//move forward to ball
	moveTo(2700); //this is pretty close - 2900 is perfect to intake the ball

	moveTo(-400, 40);
	leftTurn(120);
	moveTo(-1350, 40);
	arm(700);
	moveTo(444);
	leftTurn(70, 40);
	pros::c::delay(300);
	moveTo(2850, 80);
	arm(1500);
	pros::c::delay(1500);
	arm(0);
	moveTo(-2300, 127);
	rightTurn(87, 127);
	moveTo(3500, 127);


	// second shot speed




}

void backBlueassist()
{
	pros::lcd::print(0, "INIT auton3");

	//turn on flywheel and intake first
	/*  setFlywheelspeed(127);
	  pros::c::delay(7500);

	  targetspeed = 180;
	  pros::c::delay(1500);
	  pros::lcd::print(6, "changing speed");
	  pros::c::delay(9500);

	*/
	setFlywheelspeed(127);
	intake(1);
	pros::c::delay(1500);

	//move forward to ball
	moveTo(3000); //this is pretty close - 2900 is perfect to intake the ball
	pros::c::delay(300);

	//allign top flag
	if (getParkState())
	{
	moveTo(-2750);
	rightTurn(46);
	moveTo(-200, 25);
	while (getflywheelspeed() < 194);
	//shoot top flag
	display();
	reaper(1);
	pros::c::delay(1000);
	moveTo(200, 25);
	rightTurn(35);
	moveTo(1350, 25);
	leftTurn(90);
	intake(-1);
	moveTo(2500, 127);
	}
	//shoot middle flag


	//park






}




void autonskills() {
  pros::lcd::print(0, "INIT autonskills");

	setFlywheelspeed(127);

	intake(1);


	//move forward to ball
	setFlywheelspeed(127);

	intake(1);


	//move forward to ball
	moveTo(2700); //this is pretty close - 2900 is perfect to intake the ball

	moveTo(-400, 40);
	leftTurn(120);
	moveTo(-1350, 40);
	arm(700);
	moveTo(445);
	leftTurn(70, 40);
	pros::c::delay(300);
	moveTo(2850, 80);
	arm(1500);
	pros::c::delay(1500);
	arm(0);
	moveTo(-350);
	rightTurn(95);
	moveTo(3800);
	pros::c::delay(300);
	rightTurn(6);
	pros::c::delay(1000);
	reaper(1, 127);
	pros::c::delay(200);
	moveTo(1400, 127);

	//allign and shoot middle flag


	reaper(0);

	//allign and ram bottom flag
	leftTurn(17);
	moveTo(800);
	moveTo(-800);
	rightTurn(9);



	if (true)
	{
		moveTo(-3500);
		rightTurn(95);
		chassisSet(-50, -50);
		pros::c::delay(3500);
		moveTo(6800, 127);


	}


  /*setFlywheelspeed(127);
  intake(1);
  moveTo(3300);

 //this is pretty close - 2900 is perfect to intake the ball

  // intakes second ball
  reaper(1);
  while (getLimit() != 1);
  reaper(0);
  intake(-1);
  pros::c::delay(200);
  // moves to flip first cap
  moveTo(1000);
  moveTo(-3850);
  leftTurn(86);
  moveTo(3300);

  while(getflywheelspeed() < 195);
  reaper(1);
  pros::c::delay(150);
  reaper(0);

  //allign and shoot middle flag
  moveTo(2000);
  reaper(1);
  while (getLimit() != 1);
   pros::c::delay(200);
  reaper(0);
  leftTurn(15);
  // scores low flag
  moveTo(1300);
  moveTo(-1100);
  rightTurn(11);
  // goes to cube
  moveTo(-2000);
  rightTurn(80);
  moveTo(-1500);
  intake(1);
  moveTo(3200);
  // intakes ball
  reaper(1);
  while (getLimit() != 1);
  reaper(0);
  intake(-1);

  // flips second cap
  moveTo(1000);

  leftTurn(90);
  moveTo(1650);
  reaper(1);
  pros::c::delay(300);
  leftTurn(15, 20);
  moveTo(1300);
  moveTo(-1600);
  rightTurn(107);
  intake(-1);
  moveTo(1500);
  moveTo(2000, 40);
  moveTo(-1300, 40);
  rightTurn(90);
  moveTo(1400);
  moveTo(-400);
  leftTurn(92);
  moveTo(1300);
  rightTurn(92);
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

void backBluecap()
{
	setFlywheelspeed(127);

	intake(1);


	//move forward to ball
	moveTo(2700); //this is pretty close - 2900 is perfect to intake the ball

	moveTo(-400, 40);
	rightTurn(115);
	moveTo(-1350, 40);
	arm(700);
	moveTo(275);
	rightTurn(65);
	moveTo(2850);
	arm(1500);
	pros::c::delay(1500);
	arm(0);
	moveTo(-2300);
	leftTurn(90);
	moveTo(3500, 127);




}
void checkAutonSpeed()
{
	targetspeed = 160;
}

void test()
{
	moveTo(2600);
	//right turn by 90 degrees
	turn(90, 0);
}
// std::string autonstateNames[] = {"top blue", "top red", "back blue", "back red", "codeSkills"};
void autonomous()
{


	int aS = getAutonState();
	if (aS == 1)
	{
			topBlue();
		//  topBlue(); // top blue
	}
	else if (aS == 2)
	{
		topRed(); // top red
	}
	else if (aS == 3)
	{
		backBluecap(); // back blue
	}
	else if (aS == 4)
	{
		backRedcap(); // back red
	}
	else if (aS == 5)
	{
		autonskills();
	}
	//auton1();
	//test();
}
