#include "main.h"

//OPCONTROL//
void testfunct();
void intake(int toggle);
void reaper(int toggle);
void flywheel(bool toggle);
void moveTo(double d);
void rightTurn(int mult);
void leftTurn(int mult);
int getAutonState();
//AUTONS//
void auton1(){
	pros::lcd::print(0, "INIT auton1");
	//move forward to ball in front
	flywheel(true); // flywheel first, flameo - josh
	moveTo(3000);//this is pretty close - 2900 is perfect to intake the ball
	//pros::c::delay(1000);
	//turn on intake
	intake(1);
	pros::c::delay(3000);
	intake(0);

	pros::c::delay(3000);
	//turn right 135 degrees
	rightTurn(9);
	//reaper and flywheel shoot
	//delay for flywheel to accelerate
	pros::c::delay(1000);
	reaper(1);
	pros::c::delay(1000);
}
void auton2(){
	pros::lcd::print(0, "INIT auton2");
	//move forward to ball in front
	moveTo(3000);//this is pretty close - 2900 is perfect to intake the ball
	//pros::c::delay(1000);
	//turn on intake
	intake(1);
	pros::c::delay(3000);
	intake(0);
	//turn right 135 degrees
	leftTurn(9);
	//reaper and flywheel shoot
	flywheel(true);
	pros::c::delay(1000);
	reaper(1);
	pros::c::delay(1000);
}
void auton3(){
	pros::lcd::print(0, "INIT auton3");
}
void auton4(){
	pros::lcd::print(0, "INIT auton4");
}
void testAuton(){
	moveTo(3000);//this is pretty close - 2900 is perfect to intake the ball
	rightTurn(1);
}

void autonomous() {
	// if(getAutonState() == 1){
	// 	auton1();
	// }
	// else if(getAutonState() == 2){
	// 	auton2();
	// }
	// else if(getAutonState() == 3){
	// 	auton3();
	// }
	// else if(getAutonState() == 4){
	// 	auton4();
	// }
	testAuton();
}
