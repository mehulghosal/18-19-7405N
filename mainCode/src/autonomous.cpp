#include "main.h"

//OPCONTROL//
pros::ADIDigitalIn limit ('A');
void testfunct();
void intake(int toggle);
void reaper(int toggle);
void flywheel(bool toggle, int speed = 200);

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

	flywheel(true, 195); // flywheel first, flameo - josh
	intake(1);

	moveTo(3000);//this is pretty close - 2900 is perfect to intake the ball
	//pros::c::delay(1000);


	moveTo(-2730);
	rightTurn(90);


moveTo(300);
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


	flywheel(true, 195); // flywheel first, flameo - josh
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
	//backblue
	flywheel(true, 187); // flywheel first, flameo - josh
	intake(1);
	pros::c::delay(1500);
	moveTo(3000);//this is pretty close - 2900 is perfect to intake the ball
	pros::c::delay(1500);

	moveTo(-150, 25);
	rightTurn(88);
	moveTo(-700, 30);
	reaper(1);
	pros::c::delay(300);
	flywheel(true, 170);
	while(limit.get_value() != 1);
	reaper(0);
	// intake(0);
	pros::c::delay(300);
	reaper(1);
	pros::c::delay(1000);
	if(getParkState()){
		rightTurn(10);
		intake(-1);
		moveTo(3250, 127);
	}
}
void backRed(){ // back blue
	pros::lcd::print(0, "INIT auton3");
	//backred
	flywheel(true, 185); // flywheel first, flameo - josh
	intake(1);
	pros::c::delay(1500);
	moveTo(3000);//this is pretty close - 2900 is perfect to intake the ball
	pros::c::delay(1500);

	moveTo(-150, 25);
	leftTurn(82);
	moveTo(-700, 30);
	reaper(1);
	pros::c::delay(300);
	flywheel(true, 175);
	while(limit.get_value() != 1);
	reaper(0);
	// intake(0);
	pros::c::delay(300);
	reaper(1);
	pros::c::delay(1000);
	if(getParkState()){
		leftTurn(10);
		intake(-1);
		moveTo(3050, 127);
	}
}

void autonskills(){
	pros::lcd::print(0, "INIT autonskills");

flywheel(true, 187); // flywheel first, flameo - josh
	intake(1);
	pros::c::delay(1500);
	moveTo(3000);//this is pretty close - 2900 is perfect to intake the ball
	pros::c::delay(1500);
	moveTo(-150, 25);
	rightTurn(88);
	moveTo(-700, 30);
	reaper(1);
	pros::c::delay(300);

	while(limit.get_value() != 1);
	reaper(0);
	// intake(0);
	flywheel(true, 170);
	pros::c::delay(300);
	reaper(1);
	pros::c::delay(500);


	moveTo(700 + 150);
	rightTurn(-88);
	intake(-1);//flip capf
	moveTo(700);


	moveTo(-(700 + 3000));
	rightTurn(90);

	moveTo(3000);
	leftTurn(90);


	intake(1);
	moveTo(3000);
	moveTo(-2730);
	rightTurn(95);
	reaper(1);
	pros::c::delay(500);
	reaper(0);
	moveTo(1800);
	reaper(1);
	pros::c::delay(1500);
	reaper(0);
	rightTurn(20);
	moveTo(1800);
	moveTo(-1500);
	leftTurn(90);

	leftTurn(-90);
	moveTo(-1000);
	intake(-1);
	leftTurn(90);
	moveTo(3300);

	moveTo(-300);
	rightTurn(90);
	moveTo(1500);

	rightTurn(180);
	moveTo(3500);

	moveTo(-500);
	leftTurn(90);
	moveTo(500);
	leftTurn(-90);
	moveTo(1300);
	rightTurn(90);
	moveTo(1300);


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
