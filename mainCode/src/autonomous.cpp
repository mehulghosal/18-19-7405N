#include "main.h"

//OPCONTROL//
pros::ADIDigitalIn limit ('A');
void testfunct();
void intake(int toggle);
void reaper(int toggle);
void flywheel(bool toggle);
void moveTo(double d);
void turn(double d, int i); //1 FOR LEFT; 0 FOR RIGHT
void rightTurn(double d, int speed = 100);
void leftTurn(double d, int speed = 100);
int getAutonState();
void moveReaper(int dist, bool delay);
void arm(bool toggle);


//AUTONS//
void auton1(){
	pros::lcd::print(0,"INIT Auton1");
	//move forward to ball in front
	flywheel(true); // flywheel first, flameo - josh
	intake(1);
	pros::c::delay(1500);
	moveTo(3000);//this is pretty close - 2900 is perfect to intake the ball
	//pros::c::delay(1000);

	pros::c::delay(500);
	moveTo(-2850);
	rightTurn(101);
	//moveReaper(2000, true);
	reaper(1);
	pros::c::delay(1000);
	reaper(0);
	//pros::c::delay(1000);
	moveTo(1700);
	reaper(1);
	pros::c::delay(3000);
	reaper(0);
	rightTurn(14);
	moveTo(1200);


	//park
	/*moveTo(-1200);
	leftTurn(14);
	moveTo(-1700 - 600);
	leftTurn(90);
	moveTo(2500);*/

}


void auton2(){
	pros::lcd::print(0, "INIT auton2");
	flywheel(true); // flywheel first, flameo - josh
	intake(1);
	pros::c::delay(1500);
	moveTo(3000);//this is pretty close - 2900 is perfect to intake the ball
	//pros::c::delay(1000);
	pros::c::delay(500);
	moveTo(-2730);
	leftTurn(89);
	//moveReaper(2000, true);
	reaper(1);
	pros::c::delay(1000);
	reaper(0);

	//pros::c::delay(1000);
	moveTo(1800);
	reaper(1);
	pros::c::delay(2000);
	reaper(0);
	pros::c::delay(50);
	leftTurn(8);
	//leftTurn(14);
	moveTo(1400);


	//park
	/*moveTo(-1200);
	rightTurn(14);
	moveTo(-1700 - 600);
	rightTurn(90);
	moveTo(2500);*/

}
void auton3(){
	pros::lcd::print(0, "INIT auton3");
	//backred
	flywheel(true); // flywheel first, flameo - josh
	intake(1);
	pros::c::delay(1500);
	moveTo(3000);//this is pretty close - 2900 is perfect to intake the ball
	pros::c::delay(1500);
	reaper(1);
	while(limit.get_value() != 1);
	reaper(0);
	pros::c::delay(200);
	moveTo(-230);
	leftTurn(90, 40); // needs to be tuned
	pros::c::delay(200);
	moveTo(3040); // needs to be tuned


}
void auton4(){
	pros::lcd::print(0,"INIT auton4");
	//backvlue
	flywheel(true); // flywheel first, flameo - josh
	intake(1);
	pros::c::delay(1500);
	moveTo(3000);//this is pretty close - 2900 is perfect to intake the ball
	pros::c::delay(1500);
	reaper(1);
	while(limit.get_value() != 1);
	reaper(0);
	pros::c::delay(200);
	moveTo(-250);
//	slowrightTurn(97); // needs to be tuned
	pros::c::delay(200);
	intake(-1);
	moveTo(3150);


	/*moveTo(3000);
	intake(1);
	pros::c::delay(2000);
	turn(83, 0);

	reaper(1);
	pros::c::delay(700);*/
	// reaper(0);
	// moveTo(1000);
	// reaper(1);
	// //rightTurn(90);
	// pros::c::delay(100);
	// leftTurn(90);

}

void autonskills()
{
		pros::lcd::print(0, "INIT autonskills");
	flywheel(true); // flywheel first, flameo - josh
	intake(1);
	pros::c::delay(1500);
	moveTo(3000);//this is pretty close - 2900 is perfect to intake the ball
	pros::c::delay(1500);
	reaper(1);
	while(limit.get_value() != 1);
	reaper(0);
	moveTo(-2730);
//	slowrightTurn(90);
	moveTo(3000);
	reaper(1);
	while(limit.get_value() != 1);
	reaper(0);
	moveTo(1800);
	reaper(1);

}

void test(){
	moveTo(2600);
	//right turn by 90 degrees
	turn(90, 0);
}

void autonomous() {
	if(getAutonState() == 1){
		auton1();
	}
	else if(getAutonState() == 2){
		auton2();
	}
	else if(getAutonState() == 3){
		auton4();
	}
	else if(getAutonState() == 4){
		auton3();
	}
	else if(getAutonState() == 5){
			autonskills();
	}
	//auton1();
	//test();
}
