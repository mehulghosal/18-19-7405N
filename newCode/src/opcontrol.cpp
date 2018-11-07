#include "main.h"


/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */


//controler
pros::Controller master(pros::E_CONTROLLER_MASTER);

//drive motors
pros::Motor backLeftMtr(9);
pros::Motor frontLeftMtr(10);
pros::Motor frontRightMtr(2, pros::E_MOTOR_GEARSET_18, true);
pros::Motor backRightMtr(1, pros::E_MOTOR_GEARSET_18, true);

//reaper
pros::Motor reaperMotor(5, pros::E_MOTOR_GEARSET_18, true);

//flywheel
pros::Motor flyWheelMotor(6);

//intake
pros::Motor intakeMotor(7);

//arm (?)
pros::Motor armMotor(8);

// i honestly dont know why i have an array of motors - incase we need to iterate
pros::Motor motors [8] = {backLeftMtr, backRightMtr, frontLeftMtr, frontRightMtr, flyWheelMotor, intakeMotor, armMotor, reaperMotor};

//these are the current motor states - 1 for forwards, 0 for off, -1 for backwards
int flyWheelState = 0;
int reaperState = 0;
int intakeState = 0;

/* all of the buttons, in the order theyre in the arrayu
DIGITAL_L1		0
DIGITAL_L2		1
DIGITAL_R1		2
DIGITAL_R2		3
DIGITAL_UP		4
DIGITAL_DOWN	5
DIGITAL_LEFT	6
DIGITAL_RIGHT	7
DIGITAL_X		8
DIGITAL_B		9
DIGITAL_Y		10
DIGITAL_A		11 */
bool buttons [12] = {false, false, false, false, false, false, false, false, false, false, false, false};
bool keyPresses[12] = {false, false, false, false, false, false, false, false, false, false, false, false};
//controller_digital_e_t buttonTypes[12] = {DIGITAL_L1, DIGITAL_L2, DIGITAL_R1, DIGITAL_R2, DIGITAL_UP, DIGITAL_DOWN, DIGITAL_LEFT, DIGITAL_RIGHT, DIGITAL_X, DIGITAL_B, DIGITAL_Y, DIGITAL_A}
void buttonHandler(){
	if((master.get_digital(DIGITAL_L1)) == 1 && keyPresses[0] == false){
		buttons[0] = !buttons[0];
		keyPresses[0] = true;
	}
	else if(master.get_digital(DIGITAL_L1) == 0){
		keyPresses[0] = false;
	}

	if((master.get_digital(DIGITAL_L2)) == 1 && keyPresses[1] == false){
		buttons[1] = !buttons[1];
		keyPresses[1] = true;
	}
	else if(master.get_digital(DIGITAL_L2) == 0){
		keyPresses[1] = false;
	}
	if((master.get_digital(DIGITAL_R1)) == 1 && keyPresses[2] == false){
		buttons[2] = !buttons[2];
		keyPresses[2] = true;
	}
	else if(master.get_digital(DIGITAL_R1) == 0){
		keyPresses[2] = false;
	}
	if((master.get_digital(DIGITAL_R2)) == 1 && keyPresses[3] == false){
		buttons[3] = !buttons[3];
		keyPresses[3] = true;
	}
	else if(master.get_digital(DIGITAL_R2) == 0){
		keyPresses[3] = false;
	}
	if((master.get_digital(DIGITAL_UP)) == 1 && keyPresses[4] == false){
		buttons[4] = !buttons[4];
		keyPresses[4] = true;
	}
	else if(master.get_digital(DIGITAL_UP) == 0){
		keyPresses[4] = false;
	}
	if((master.get_digital(DIGITAL_DOWN)) == 1 && keyPresses[5] == false){
		buttons[5] = !buttons[5];
		keyPresses[5] = true;
	}
	else if(master.get_digital(DIGITAL_DOWN) == 0){
		keyPresses[5] = false;
	}
	if((master.get_digital(DIGITAL_LEFT)) == 1 && keyPresses[6] == false){
		buttons[6] = !buttons[6];
		keyPresses[6] = true;
	}
	else if(master.get_digital(DIGITAL_LEFT) == 0){
		keyPresses[6] = false;
	}
	if((master.get_digital(DIGITAL_RIGHT)) == 1 && keyPresses[7] == false){
		buttons[7] = !buttons[7];
		keyPresses[7] = true;
	}
	else if(master.get_digital(DIGITAL_RIGHT) == 0){
		keyPresses[7] = false;
	}
	if((master.get_digital(DIGITAL_X)) == 1 && keyPresses[8] == false){
		buttons[8] = !buttons[8];
		keyPresses[8] = true;
	}
	else if(master.get_digital(DIGITAL_X) == 0){
		keyPresses[8] = false;
	}
	if((master.get_digital(DIGITAL_B)) == 1 && keyPresses[9] == false){
		buttons[9] = !buttons[9];
		keyPresses[9] = true;
	}
	else if(master.get_digital(DIGITAL_B) == 0){
		keyPresses[9] = false;
	}
	if((master.get_digital(DIGITAL_Y)) == 1 && keyPresses[10] == false){
		buttons[10] = !buttons[10];
		keyPresses[10] = true;
	}
	else if(master.get_digital(DIGITAL_Y) == 0){
		keyPresses[10] = false;
	}
	if((master.get_digital(DIGITAL_A)) == 1 && keyPresses[11] == false){
		buttons[11] = !buttons[1];
		keyPresses[11] = true;
	}
	else if(master.get_digital(DIGITAL_A) == 0){
		keyPresses[11] = false;
	}
}

// void buttonReset(){
// 	for(int i = 0; i<12; i++){
// 		buttons[i] = false;
// 	}
// }

void flywheel(){
	if(flyWheelState != 0){
		flyWheelMotor = 127;
		flyWheelState = 1;
	}
	else {
		flyWheelMotor = 0;
		flyWheelState = 0;

	}
	pros::lcd::print(1, "Flywheel Speed: %f", (flyWheelMotor.get_actual_velocity()));
}

void reaper(int button){
	//forward/off
	if(button == 10){
		if(reaperState != 0){
			reaperMotor = 0;
			reaperState = 0;
		}
		else{
			reaperMotor = 127;
			reaperState = 1;
		}
	}
	//back/off
	else {
		if(reaperState != 0){
			reaperMotor = 0;
			reaperState = 0;
		}
		else{
			reaperMotor = -127;
			reaperState = -1;
		}
	}
	pros::lcd::print(3, "Reaper Motor Speed: %f", (reaperMotor.get_actual_velocity()));
}

void intake(int button){
	//forward
	if(button == 6){
		if(intakeState != 0){
			intakeMotor = 0;
		}
		else{
			intakeMotor = 127;
		}
	}
	//backward
	else{
		if(intakeState != 0){
			intakeMotor = 0;
		}
		else{
			intakeMotor = -127;
		}
	}
	pros::lcd::print(2, "Intake Motor Speed: %f", (intakeMotor.get_actual_velocity()));
}

void lift(){
	//we need to tune the motor so we know how long its supposed to be on
}

void drive(int driveL, int driveR) {

	if(driveL > 15 || driveL < -15){
		backLeftMtr = driveL; frontLeftMtr = driveL;
	}
	else{
		backLeftMtr = 0; frontLeftMtr = 0;
	}
	if(driveR > 15 || driveR < -15){
		backRightMtr = driveR; frontRightMtr = driveR;
	}
	else{
		backRightMtr = 0; frontRightMtr = 0;
	}

	pros::lcd::print(4, "BL : %d", (backLeftMtr.get_actual_velocity()));
	pros::lcd::print(5, "FL : %d", (frontLeftMtr.get_actual_velocity()));
	pros::lcd::print(6, "BR : %d", (backRightMtr.get_actual_velocity()));
	pros::lcd::print(7, "FR : %d", (frontRightMtr.get_actual_velocity()));

}

void motorStop() {
	for (int i = 0; i < 8; i++) {
		motors[i] = 0;
	}
}

void opcontrol() {
	pros::lcd::print(0, "INIT pumped up kicks is a fucking fire song (even if its about columbine)");

	while (true) {
		// pros::lcd::print(0, "hello this is initialized %d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		//                  (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		//                  (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);


		int driveLeft = master.get_analog(ANALOG_LEFT_Y); //controls left motors
		int driveRight = master.get_analog(ANALOG_RIGHT_Y);  //controls right motors
		buttonHandler();

		//reaper toggling
		if (buttons[8]){
			reaper(8);
		}
		else if(buttons[9]){
			reaper(9);
		}
		//flywheel toggling
		if(buttons[10]){
			flywheel();
		}

		//intake will have to be be 0 for off, 1 for forward, -1 for back
		//stop
		//intake toggling
		if(buttons[6]){
			intake(6);
		}
		else if(buttons[7]){
			intake(7);
		}

		//stops all motors
		if (buttons[4]) {
			motorStop();
		}

		// intake(intakeToggle);
		// flywheel(flyWheelToggle);
		// reaper(reaperToggle);
		drive(driveLeft, driveRight);
		pros::Task::delay(10);

	}
}

void auton1(){
	pros::lcd::print(0, "INIT auton1");
}

void leftTurn(){
	//90 degree left turn: right side 100, left side -100
	//we have to do PID so we know how long the motors should stay on
}

void rightTurn(){
	//same as the other method ig
}
