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
	pros::lcd::print(0, "INIT auton1");
	flywheel(true); // flywheel first, flameo - josh
	intake(1);
	moveTo(2650);
	pros::c::delay(800);
	moveTo(-2625);
	pros::c::delay(800);
	
	turn(90, 0);
	pros::c::delay(2000);

	//first shot
	reaper(1);
	pros::c::delay(1500);
	reaper(0);

	//second shot
	moveTo(1200);
	reaper(1);
	pros::c::delay(1500);

	//bottom flag
	moveTo(600);
	turn(30, 1);
	pros::c::delay(1500);

	//come back
	turn(30, 0);
	moveTo(-1800);

	
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
