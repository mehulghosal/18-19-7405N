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

	flywheel(true); // flywheel first, flameo - josh
	moveTo(3000);

	intake(1);

	pros::c::delay(3000);

	pros::c::delay(500);

	moveTo(-2950);
	pros::c::delay(1500);
	rightTurn(6);
	pros::c::delay(700);
	moveTo(150);

	pros::c::delay(1000);
	reaper(1);
	pros::c::delay(1500);
	reaper(0);
	moveTo(2000);
	pros::c::delay(1800);
	reaper(1);
	pros::c::delay(3000);
}
void auton2(){
	pros::lcd::print(0, "INIT auton2");
	flywheel(true); // flywheel first, flameo - josh
	moveTo(3000);

	intake(1);

	pros::c::delay(3000);

	pros::c::delay(500);

	moveTo(-2950);
	pros::c::delay(1500);
	leftTurn(6);
	pros::c::delay(700);
	moveTo(150);

	pros::c::delay(1000);
	reaper(1);
	pros::c::delay(1500);
	reaper(0);
	moveTo(2000);
	pros::c::delay(1800);
	reaper(1);
	pros::c::delay(3000);
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


	pros::c::delay(500);

	//turn right 135 degrees
	moveTo(-3200);
	pros::c::delay(1000);
	rightTurn(9.1);
	pros::c::delay(500);

	//reaper and flywheel shoot
	//delay for flywheel to accelerate
	pros::c::delay(1000);
	reaper(1);
	pros::c::delay(1500);
	reaper(0);
	moveTo(3000);
	pros::c::delay(1800);
	reaper(1);
	pros::c::delay(2000);
	pros::c::delay(3000);
	reaper(0);

}
void auton4(){
	pros::lcd::print(0,"INIT Auton4");
	//move forward to ball in front
	flywheel(true); // flywheel first, flameo - josh
	moveTo(3000);//this is pretty close - 2900 is perfect to intake the ball
	//pros::c::delay(1000);
	//turn on intake
	intake(1);

	pros::c::delay(3000);


	pros::c::delay(500);

	//turn right 135 degrees
	moveTo(-3200);
	pros::c::delay(1000);
	leftTurn(9.1);
	pros::c::delay(500);

	//reaper and flywheel shoot
	//delay for flywheel to accelerate
	pros::c::delay(1000);
	reaper(1);
	pros::c::delay(1500);
	reaper(0);
	moveTo(3000);
	pros::c::delay(1800);
	reaper(1);
	pros::c::delay(2000);
	pros::c::delay(3000);
	reaper(0);
}
void testAuton(){
	//TESTING AUTON CODE//
	otherMoveTo(3000);
	intake(1);
}

void skills(){
	flywheel(true);
	moveTo(3000);
	pros::c::delay(2000);
	intake(1);
	pros::c::delay(3000);
	intake(0);
	pros::c::delay(2000);
	reaper(1);
	pros::c::delay(500);
	reaper(0);
	intake(-1);
	moveTo(2000);
	pros::c::delay(3000);
	moveTo(-4150);
	pros::c::delay(3000);
	leftTurn(8);
	pros::c::delay(3000);
	moveTo(800);
	reaper(1);
	pros::c::delay(1250);
	reaper(0);
	moveTo(-800);
	pros::c::delay(1000);
	rightTurn(3);
	pros::c::delay(2000);
	moveTo(4000);
	intake(-1);
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
	else if(getAutonState() == 5){
		skills();
	}
	//testAuton();
}
