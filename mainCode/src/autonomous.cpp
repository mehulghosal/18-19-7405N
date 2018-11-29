#include "main.h"

//OPCONTROL//
void testfunct();
void intake(int toggle);
void reaper(int toggle);
void flywheel(bool toggle);
void moveTo(double d);
void rightTurn(double mult);
void leftTurn(double mult);
int getAutonState();
void arm(bool toggle);

//AUTONS//
void auton1(){
	pros::lcd::print(0, "INIT auton1");
	flywheel(true); // flywheel first, flameo - josh
	
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
}
