#include "main.h"

//OPCONTROL//
void testfunct();
void intake(int toggle);
void reaper(int toggle);
void flywheel(bool toggle);
void moveTo(double d);
void turn(double d, int i); //1 FOR LEFT; 0 FOR RIGHT
int getAutonState();
void arm(bool toggle);
//AUTONS//
void auton1(){
	pros::lcd::print(0,"INIT Auton4");
	//move forward to ball in front
	flywheel(true); // flywheel first, flameo - josh
	moveTo(3000);//this is pretty close - 2900 is perfect to intake the ball
	//pros::c::delay(1000);
	//turn on intake
	intake(1);

//	pros::c::delay(3000);


//	pros::c::delay(500);

	//turn right 135 degrees
	moveTo(-3000);
	rightTurn(87);
}


void auton2(){
	pros::lcd::print(0, "INIT auton2");
	flywheel(true); // flywheel first, flameo - josh

}
void auton3(){
	pros::lcd::print(0, "INIT auton3");
	flywheel(true); // flywheel first, flameo - josh


}
void auton4(){
	pros::lcd::print(0,"INIT auton4");
	flywheel(true); // flywheel first, flameo - josh

}

void test(){
	moveTo(2600);
	//right turn by 90 degrees
	turn(90, 0);
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
	auton1();
	//test();
}
