#include "main.h"

//OPCONTROL//

void testfunct();
void intake(int toggle);
void reaper(int toggle);
void flywheel(bool toggle, int speed = 200);
void old_flywheel(bool toggle, int speed = 127);
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
int getLimit();



//AUTONS//
void topBlue(){
	pros::lcd::print(0,"INIT Auton1");

	//turn on flywheel and intake on first
	flywheel(true, 195);
	intake(1);

	//move forward to ball in front
	moveTo(3000);

	//move back and allign top flag
	moveTo(-2730);
	rightTurn(91);
	moveTo(300);

	//shoot top flag
	reaper(1);
	pros::c::delay(500);
	reaper(0);

	//allign and shoot middle flag
	moveTo(1500);
	reaper(1);
	while(getLimit() != 1);
	pros::c::delay(500);
	reaper(0);

	//allign and ram bottom flag
	rightTurn(20);
	moveTo(1000);
	moveTo(-1000);
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

	//turn on flywheel
	flywheel(true, 195); // flywheel first, flameo - josh
	intake(1);

	//move forward to ball
	moveTo(3000);

	//move back and allign top flag
	moveTo(-2800);
	leftTurn(91);
	moveTo(300);
	//shoot top flag
	reaper(1);
	pros::c::delay(500);
	reaper(0);

	//allign and shoot middle flag
	moveTo(1800);
	reaper(1);
	while(getLimit() != 1);
	pros::c::delay(500);
	reaper(0);

	//allign and ram bottom flag
	leftTurn(20);
	moveTo(1000);
	moveTo(-1000);


	//park
	/*moveTo(-1200);
	rightTurn(14);
	moveTo(-1700 - 600);
	rightTurn(90);
	moveTo(2500);*/

}

void backBlue(){
	pros::lcd::print(0, "INIT auton3");

	//turn on flywheel and intake first
	flywheel(true, 200);
	intake(1);
	pros::c::delay(1500);

	//move forward to ball
	moveTo(3000);//this is pretty close - 2900 is perfect to intake the ball
	pros::c::delay(750);

	//allign top flag
	moveTo(-2750);
	rightTurn(55);
	moveTo(-200, 25);


	//shoot top flag
	reaper(1);
	pros::c::delay(300);
	flywheel(true, 185);
	while(getLimit() != 1);
	reaper(0);

	//shoot middle flag
	pros::c::delay(300);
	reaper(1);
	pros::c::delay(500);

	//park
	if(getParkState()){
		moveTo(200, 25);
		rightTurn(35);
		moveTo(1200, 25);
		leftTurn(90);
		intake(-1);
		moveTo(1500, 127);
	}
}
void backRed(){
	pros::lcd::print(0, "INIT auton3");

	//turn on flywheel and intake first
	flywheel(true, 190);
	intake(1);
	pros::c::delay(1500);

	//move forward to ball
	moveTo(3000);
	pros::c::delay(750);

	//allign top flag
	moveTo(-250, 25);
	leftTurn(82);
	moveTo(-700, 30);

	//shoot top flag
	reaper(1);
	pros::c::delay(300);
	flywheel(true, 172);
	while(getLimit()!= 1);
	reaper(0);

	//shoot middle flag
	pros::c::delay(300);
	reaper(1);
	pros::c::delay(1000);

	//park
	if(getParkState()){
		leftTurn(10);
		intake(-1);
		moveTo(3150, 127);
	}
}

void autonskills(){
	pros::lcd::print(0, "INIT autonskills");

	pros::lcd::print(0, "INIT autonskills");



flywheel(true, 200); // flywheel first, flameo - josh
intake(1);
pros::c::delay(1500);
moveTo(2500, 60);//this is pretty close - 2900 is perfect to intake the ball
pros::c::delay(2000);
// intakes second ball
reaper(1);
while(getLimit() != 1);
reaper(0);
intake(-1);
pros::c::delay(1000);
// moves to flip first cap
moveTo(1000, 20);
pros::c::delay(1500);

moveTo(-3400,50);
leftTurn(92, 40);
moveTo(3700, 40);

// shoots first ball
reaper(1);
pros::c::delay(350);
// indexes second ball
while(getLimit() != 1);
reaper(0);
// scores second flag
moveTo(1500, 40);
reaper(1);
pros::c::delay(500);
leftTurn(15, 20);
// scores low flag
moveTo(1100, 40);
moveTo(-1100, 40);
rightTurn(15, 20);
// goes to cube
moveTo(-2000);
rightTurn(95, 40);
intake(1);
moveTo(2300, 40);
// intakes ball
	while(getLimit() != 1);
reaper(0);
intake(-1);
pros::c::delay(1000);
// flips second cap
moveTo(1000, 20);

leftTurn(96,40);
moveTo(1650, 40);
reaper(1);
pros::c::delay(1000);
leftTurn(15, 20);
moveTo(1000);
moveTo(-1400);
rightTurn(125, 20);
intake(-1);
moveTo(1500);
moveTo(1500, 40);
rightTurn(90, 20);
moveTo(1000);
leftTurn(90, 20);
moveTo(1000);
rightTurn(90, 20);
moveTo(1000);
rightTurn(90, 20);
moveTo(1000);
moveTo(-500);
moveTo(5000, 127);


}




void newBackBlue(){
	pros::lcd::print(0, "INIT auton3");
	//backred
	old_flywheel(true, 127); // flywheel first, flameo - josh
	intake(1);
	pros::c::delay(1500);
	moveTo(2700);//this is pretty close - 2900 is perfect to intake the ball
	if(getParkState()){
		pros::c::delay(1500);
		moveTo(-200);
		rightTurn(90);
		moveTo(2100);
	}
	else{
		moveTo(-2300);
	}
}

void newBackRed(){
	pros::lcd::print(0, "INIT auton3");
	//backred
	old_flywheel(true, 127); // flywheel first, flameo - josh
	intake(1);
	pros::c::delay(1500);
	moveTo(2700);//this is pretty close - 2900 is perfect to intake the ball
	if(getParkState()){
		pros::c::delay(1500);
		moveTo(-200);
		leftTurn(90);
		moveTo(2100);
	}
	else{
		moveTo(-2300);
	}
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
		newBackBlue(); // back blue
	}
	else if(aS == 4){
		newBackRed(); // back red
	}
	else if(aS == 5){
		autonskills();
	}
	//auton1();
	//test();
}
