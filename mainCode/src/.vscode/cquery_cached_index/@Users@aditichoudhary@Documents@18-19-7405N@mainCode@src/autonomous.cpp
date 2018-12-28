#include "main.h"

//OPCONTROL//
pros::ADIDigitalIn limit ('A');
void testfunct();
void intake(int toggle);
void reaper(int toggle);
void flywheel(bool toggle, int speed = 127);
// void moveTo(double d);
void moveTo(double d);
void moveTo(double d, double speed);
void turn(double d, int i); //1 FOR LEFT; 0 FOR RIGHT
void rightTurn(double d, int speed = 100);
void leftTurn(double d, int speed = 100);
int getAutonState();
bool getParkState();
void moveReaper(int dist, bool delay);
void arm(bool toggle);



//AUTONS//
void topBlue(){
	pros::lcd::print(0,"INIT Auton1");
	//move forward to ball in front

	flywheel(true); // flywheel first, flameo - josh
	intake(1);

	moveTo(3000);//this is pretty close - 2900 is perfect to intake the ball
	//pros::c::delay(1000);


	moveTo(-2730);
	rightTurn(95);
	//moveReaper(2000, true);
	reaper(1);
	pros::c::delay(500);
	reaper(0);
	//pros::c::delay(1000);
	moveTo(1800);
	reaper(1);
	pros::c::delay(1500);
	reaper(0);
	rightTurn(20);
	moveTo(1800);
	moveTo(-1500);
	leftTurn(90);


	//park
	/*moveTo(-1200);
	leftTurn(14);
	moveTo(-1700 - 600);
	leftTurn(90);
	moveTo(2500);*/

}


void topRed(){
	pros::lcd::print(0, "INIT auton2");


	flywheel(true); // flywheel first, flameo - josh
	intake(1);

	moveTo(3000);//this is pretty close - 2900 is perfect to intake the ball
	//pros::c::delay(1000);

	moveTo(-2800);
	leftTurn(90);
	//moveReaper(2000, true);
	reaper(1);
	pros::c::delay(500);
	reaper(0);

	//pros::c::delay(1000);
	moveTo(1800);
	reaper(1);
	pros::c::delay(1500);
	reaper(0);
	pros::c::delay(50);
	leftTurn(20);
	//leftTurn(14);
	moveTo(1300);
		moveTo(-1300);


	//park
	/*moveTo(-1200);
	rightTurn(14);
	moveTo(-1700 - 600);
	rightTurn(90);
	moveTo(2500);*/

}

void backBlue(){
	pros::lcd::print(0, "INIT auton3");
	//backred
	flywheel(true, 119); // flywheel first, flameo - josh
	intake(1);
	pros::c::delay(1500);
	moveTo(3000);//this is pretty close - 2900 is perfect to intake the ball
	pros::c::delay(1500);

	moveTo(-150, 25);
	rightTurn(88);
	moveTo(-700, 30);
	reaper(1);
	pros::c::delay(300);
	flywheel(true, 119);
	while(limit.get_value() != 1);
	reaper(0);
	// intake(0);
	pros::c::delay(300);
	reaper(1);
	pros::c::delay(1000);
	if(getParkState())
	{

	rightTurn(10);
	intake(-1);
	moveTo(3100, 127);
}
}
void backRed(){ // back blue
	pros::lcd::print(0, "INIT auton3");
	//backred
	flywheel(true, 120); // flywheel first, flameo - josh
	intake(1);
	pros::c::delay(1500);
	moveTo(3000);//this is pretty close - 2900 is perfect to intake the ball
	pros::c::delay(1500);

	moveTo(-150, 25);
	leftTurn(84);
	moveTo(-700, 30);
	reaper(1);
	pros::c::delay(300);
	flywheel(true, 117);
	while(limit.get_value() != 1);
	reaper(0);
	// intake(0);
	pros::c::delay(300);
	reaper(1);
	pros::c::delay(1000);
	if(getParkState())
	{
	leftTurn(10);
	intake(-1);
	moveTo(3000, 127);
}
}

void autonskills(){
	pros::lcd::print(0, "INIT autonskills");

	flywheel(true); // flywheel first, flameo - josh
	intake(1);
	pros::c::delay(1500);
	moveTo(2700, 60);//this is pretty close - 2900 is perfect to intake the ball
	pros::c::delay(2000);
	// intakes second ball
	reaper(1);
	while(limit.get_value() != 1);
	reaper(0);
	intake(-1);
	pros::c::delay(1000);
	// moves to flip first cap
	moveTo(650, 20);
	pros::c::delay(1500);

	moveTo(-3100);
	rightTurn(88, 40);
	moveTo(3000);

	// shoots first ball
	reaper(1);
	pros::c::delay(300);
	// indexes second ball
	while(limit.get_value() != 1);
	reaper(0);
	// scores second flag
	moveTo(600);
	reaper(1);
	pros::c::delay(1000);
	rightTurn(10, 20);
	// scores low flag
	moveTo(600);
	moveTo(-600);
	leftTurn(12, 20);
	// goes to cube
	moveTo(-1800);
	leftTurn(91, 40);
	intake(1);
	moveTo(3000);
	// intakes ball
	while(limit.get_value() != 1);
	reaper(0);
	intake(-1);
	pros::c::delay(1000);
	// flips second cap
	moveTo(1000, 20);
	moveTo(-1100);
	rightTurn(110,40);
	moveTo(2000);
	reaper(1);
	pros::c::delay(1000);
	moveTo(1500);


}

void test(){
	moveTo(2600);
	//right turn by 90 degrees
	turn(90, 0);
}
// std::string autonstateNames[] = {"top blue", "top red", "back blue", "back red", "codeSkills"};
void autonomous(){

	int aS = getAutonState();
	if(aS == 1){
		topBlue(); // top blue
	}
	else if(aS == 2){
		topRed(); // top red
	}
	else if(aS == 3){
		backBlue(); // back blue
	}
	else if(aS == 4){
		backRed(); // back red
	}
	else if(aS == 5){
		autonskills();
	}
	//auton1();
	//test();
}
