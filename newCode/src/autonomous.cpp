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

	pros::c::delay(500);

	//turn right 135 degrees
	moveTo(-3000);
	pros::c::delay(1000);
	rightTurn(7);
	pros::c::delay(500);
	moveTo(-100);	

	//reaper and flywheel shoot
	//delay for flywheel to accelerate
	pros::c::delay(1000);
	reaper(1);
	pros::c::delay(2200);
	reaper(0);
	moveTo(2000);
	pros::c::delay(2000);
	reaper(1);
	pros::c::delay(2000);
	reaper(0);
}
void auton2(){
	pros::lcd::print(0, "INIT auton2");
	//move forward to ball in front
	flywheel(true); // flywheel first, flameo - josh
	moveTo(3000);//this is pretty close - 2900 is perfect to intake the ball
	//pros::c::delay(1000);
	//turn on intake
	intake(1);

	pros::c::delay(3000);
	intake(0);

	pros::c::delay(500);

	//turn right 135 degrees
	moveTo(-3000);
	pros::c::delay(1000);
	leftTurn(7);
	pros::c::delay(500);
	moveTo(-100);

	//reaper and flywheel shoot
	//delay for flywheel to accelerate
	pros::c::delay(1000);
	reaper(1);
	pros::c::delay(2200);
	reaper(0);
	moveTo(2000);
	pros::c::delay(2000);
	reaper(1);
	pros::c::delay(2000);
	reaper(0);
}
void auton3(){
	pros::lcd::print(0, "INIT auton3");
	//move forward to ball in front
	flywheel(true); // flywheel first, flameo - josh
	moveTo(3000);//this is pretty close - 2900 is perfect to intake the ball
	//pros::c::delay(1000);
	//turn on intake
	intake(1);

	pros::c::delay(3000);
	intake(0);

	pros::c::delay(500);

	//turn right 135 degrees
	moveTo(-3000);
	pros::c::delay(1000);
	rightTurn(7);
	pros::c::delay(500);
	moveTo(2600);

	//reaper and flywheel shoot
	//delay for flywheel to accelerate
	pros::c::delay(1000);
	reaper(1);
	pros::c::delay(2200);
	reaper(0);
	moveTo(2000);
	pros::c::delay(2000);
	reaper(1);
	pros::c::delay(2000);
	reaper(0);

}
void auton4(){
	pros::lcd::print(0, "INIT auton4");
	//move forward to ball in front
	flywheel(true); // flywheel first, flameo - josh
	moveTo(3000);//this is pretty close - 2900 is perfect to intake the ball
	//pros::c::delay(1000);
	//turn on intake
	intake(1);

	pros::c::delay(3000);
	intake(0);

	pros::c::delay(500);

	//turn right 135 degrees
	moveTo(-3000);
	pros::c::delay(1000);
	leftTurn(7);
	pros::c::delay(500);
	moveTo(2600);

	//reaper and flywheel shoot
	//delay for flywheel to accelerate
	pros::c::delay(1000);
	reaper(1);
	pros::c::delay(2200);
	reaper(0);
	moveTo(2000);
	pros::c::delay(2000);
	reaper(1);
	pros::c::delay(2000);
	reaper(0);
}
void testAuton(){
	pros::lcd::print(1, "test");
	intake(1);
	moveTo(3000);
	pros::c::delay(2000);
	leftTurn(6);
	pros::c::delay(1000);
	reaper(1);
	pros::c::delay(3000);
	rightTurn(6);
	moveTo(-3000);
}

void autonomous() {
	if(getAutonState() == 1){
		auton1();
	}
	else if(getAutonState() == 2){
		auton2();
	}
	else if(getAutonState() == 3){
		auton3();
	}
	else if(getAutonState() == 4){
		auton4();
	}
	//testAuton();	
}
