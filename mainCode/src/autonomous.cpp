#include "main.h"

//OPCONTROL//
pros::ADIDigitalIn limit ('A');
void testfunct();
void intake(int toggle);
void reaper(int toggle);
void flywheel(bool toggle);
void moveTo(double d);
void moveTo(double d, int speedCoef);
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
	leftTurn(94, 40); // needs to be tuned
	pros::c::delay(200);
	moveTo(3300); // needs to be tuned


}
void auton4(){
	pros::lcd::print(0,"INIT auton4");
	//backvlue
	flywheel(true); // flywheel first, flameo - josh
	intake(1);
	pros::c::delay(1600);
	moveTo(3000);//this is pretty close - 2900 is perfect to intake the ball
	pros::c::delay(1500);
	reaper(1);
	while(limit.get_value() != 1);
	reaper(0);
	intake(0);
	moveTo(400);

	leftTurn(90, 40);
intake(1);
	moveTo(1000);
	pros::c::delay(2000);
	moveTo(-500);

	rightTurn(94, 40);
	pros::c::delay(500);

	moveTo(-750);
	rightTurn(105, 40); // needs to be tuned
	pros::c::delay(200);
	intake(-1);
	moveTo(3900);
	leftTurn(94, 40);


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
// intakes second ball
reaper(1);
while(limit.get_value() != 1);
reaper(0);
intake(-1);
pros::c::delay(1000);
// moves to flip first cap
moveTo(1000, 20);
pros::c::delay(1500);
moveTo(-1100);
moveTo(-2730);
rightTurn(109, 40);
moveTo(2700);
// shoots first ball
reaper(1);
pros::c::delay(300);
// indexes second ball
while(limit.get_value() != 1);
reaper(0);
// scores second flag
moveTo(1800);
reaper(1);
pros::c::delay(300);
// scores low flag
moveTo(1700);
// goes to cube
moveTo(-2700);
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
