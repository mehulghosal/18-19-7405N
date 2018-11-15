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

void leftTurn();
void rightTurn();

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

void flywheel(bool toggle){
	if(toggle){
		flyWheelMotor = 127;
	}
	else {
		flyWheelMotor = 0;
	}

}

void intake(int toggle){
	if(toggle == 1){
		intakeMotor = 127;
	}
	if(toggle == -1){
		intakeMotor = -127;
	}
	if(toggle == 0){
		intakeMotor = 0;
	}

}

void reaper(int toggle){
	if(toggle == 1){
		reaperMotor = 80;
	}
	else if(toggle == 0){
		reaperMotor = 0;
	}
	else {
		reaperMotor = -80;
	}

}

void arm(bool toggle){
	if(toggle == true){
		armMotor.move_absolute(100, 100);
	}
	else{
		armMotor.move_absolute(-100, 100);
	}
}

void chassisSet(int m1, int m2){
	backLeftMtr = m1;
	frontLeftMtr = m1;
	backRightMtr = m2;
	frontRightMtr = m2;
}

void drive(int driveL, int driveR) {

	if(abs(driveL) >= 15 || abs(driveR) >= 15) {
		chassisSet(std::min(std::max(driveL + driveR, -127),127), std::min(std::max(driveL - driveR, -127),127));
	} else {
		chassisSet(0,0);
	}

	/*
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
	}*/

	pros::lcd::print(3, "BL: %d FL: %d", (backLeftMtr.get_actual_velocity()),(frontLeftMtr.get_actual_velocity()));
	pros::lcd::print(4, "BR: %d FR: %d", (backRightMtr.get_actual_velocity()),(frontRightMtr.get_actual_velocity()));

}

void motorStop() {
	for (int i = 0; i < 8; i++) {
		motors[i] = 0;
	}
}

void opcontrol() {
	//pros::lcd::print(0, "INIT pumped up kicks is a fucking fire song (even if its about columbine)");
	bool flyWheelToggle = false;
	int intakeToggle = 0;
	int reaperToggle = 0;
	bool xPressed = false;
	bool yPressed = false;
	bool left = false;
	bool right = false;
	bool bPressed = false;
	bool lPressed = false;
	bool rPressed = false;

	while (true) {
		// pros::lcd::print(0, "hello this is initialized %d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		//                  (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		//                  (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);



		int driveLeft = master.get_analog(ANALOG_LEFT_Y); //controls left motors
		int driveRight = master.get_analog(ANALOG_RIGHT_X);  //controls right motors

		//reaper toggling
		if (master.get_digital(DIGITAL_X) == 1 && xPressed == false){
			if (reaperToggle == 1){
				reaperToggle = 0;
			}
			else if (reaperToggle == 0 || reaperToggle == -1){
				reaperToggle = 1;
			}
			xPressed = true;


		}
		else if(master.get_digital(DIGITAL_X) == 0) {
			xPressed = false;
		}
		if (master.get_digital(DIGITAL_B) == 1 && bPressed == false) {
			if (reaperToggle == -1){
				reaperToggle = 0;
			}
			else if (reaperToggle == 0 || reaperToggle == 1){
				reaperToggle = -1;
			}
			bPressed = true;


		}
		else if (master.get_digital(DIGITAL_B) == 0) {
			bPressed = false;
		}


		//intake toggling
		if (master.get_digital(DIGITAL_LEFT) == 1 && lPressed == false ){

			if (intakeToggle == 1){
				intakeToggle = 0;
			}
			else if (intakeToggle == 0 || intakeToggle == -1){
				intakeToggle = 1;
			}
			lPressed = true;

		}
		else if (master.get_digital(DIGITAL_LEFT) == 0){
			lPressed = false;
		}
		if (master.get_digital(DIGITAL_RIGHT) == 1 && rPressed == false) {

			if (intakeToggle == -1){
				intakeToggle = 0;
			}
			else if (intakeToggle == 0 || intakeToggle == 1){
				intakeToggle = -1;
			}
			rPressed = true;

		}
		else if (master.get_digital(DIGITAL_RIGHT) == 0){
			rPressed = false;
		}

		//flywheel toggling
		if (master.get_digital(DIGITAL_Y) == 1 && yPressed == false){
			flyWheelToggle = !flyWheelToggle;
			yPressed = true;
			pros::Task::delay(20);
		}
		else if (master.get_digital(DIGITAL_Y) == 0){
			yPressed = false;
		}
//		pros::lcd::print(2, "ARM: %d",(int)armMotor.get_position()) ;
		//lmao forgive me for this
		if(master.get_digital(DIGITAL_R2) == 1){
				armMotor = 100;
		}
		else if(master.get_digital(DIGITAL_L2) == 1){
				armMotor = -100;
		}
		else if(armMotor.get_position() >= 400){
			armMotor = -15;
		}

		else if(armMotor.get_position() < 400){
			armMotor = 15;
		}
		/*
enum class brakeMode {
  coast = 0, // Motor coasts when stopped, traditional behavior
  brake = 1, // Motor brakes when stopped
  hold = 2,  // Motor actively holds position when stopped
  invalid = INT32_MAX
};

		*/


		//stops all motors
		if (master.get_digital(DIGITAL_UP) == 1) {
			motorStop();
		}
		pros::lcd::print(1, "Reaper: %f Intake: %d", (reaperMotor.get_actual_velocity()),(int)intakeToggle);
		pros::lcd::print(2, "Flywheel: %f", (flyWheelMotor.get_actual_velocity()));

		intake(intakeToggle);
		flywheel(flyWheelToggle);
		drive(driveLeft, driveRight);
		reaper(reaperToggle);
		pros::Task::delay(20);

	}
}


void testfunct(){
//	pros::lcd::print(0, "test function");
	pros::c::delay(2000);
}

//for autons
//this for moving straight
void moveTo(double d){ // REWRITE THIS TO WAIT UNTIL ITS DONE THEN STOP THE MOTORS
	//not turning
  backRightMtr.tare_position();

	frontLeftMtr.move_absolute(d, 200);
	frontRightMtr.move_absolute(d, 200);
	backLeftMtr.move_absolute(d, 200);
	backRightMtr.move_absolute(d, 200);

	// while((200 - backRightMtr.get_position()) > 5){ // NOT SURE IF CORRECT - TEST THIS
	// 	pros::c::delay(10);
	// }
}

//lets just make this in 15 degree intervals degrees bc who cares
void leftTurn(int mult){
	int turn = mult * 50;//turn the 10 to be for about 15 degrees
	frontRightMtr.move_absolute(turn, 200);
	backRightMtr.move_absolute(turn, 200);
	frontLeftMtr.move_absolute(turn, -200);
	backLeftMtr.move_absolute(turn, -200);
}

void rightTurn(int mult){
	int turn = mult * 50;
	frontRightMtr.move_absolute(turn, -200);
	backRightMtr.move_absolute(turn, -200);
	backLeftMtr.move_absolute(turn, 200);
	frontLeftMtr.move_absolute(turn, 200);
}
