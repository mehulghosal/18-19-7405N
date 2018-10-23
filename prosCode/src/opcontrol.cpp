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


//declaring global vars, controler
pros::Controller master(pros::E_CONTROLLER_MASTER);

//drive motors
pros::Motor backLeftMtr(1);
pros::Motor backRightMtr(2);
pros::Motor frontLeftMtr(3);
pros::Motor frontRightMrt(4);



//until we get more motor wires, we wont be able to declare all of the motors - upload error
//flywheel
pros::Motor flyWheelMotor(6);

//intake
pros::Motor intakeMotor(7);

//lift (?)
pros::Motor liftMotor(8);


void opcontrol() {
	while (true) {
		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);
		int driveX = master.get_analog(ANALOG_RIGHT_X); //controls right and left
		int driveY = master.get_analog(ANALOG_LEFT_Y);  //controls forward/back

		int flyIntake = master.get_digital(DIGITAL_X);	//flywheel and intake same time
		int flyOn = master.get_digital(DIGITAL_Y);		//only flywheel
		int intakeOn = master.get_digital(DIGITAL_A);	//only intake
		int powerOff = master.get_digital(DIGITAL_B);	//turn intake and flywheel off

		if (flyIntake == 1){
			backLeftMtr = 127;
			backRightMtr = -127;
		}

		if (powerOff == 1){
			backRightMtr = 0;
			backLeftMtr = 0;
		}

		//backRightMtr, frontRightMrt = right;
		//backLeftMtr, frontLeftMtr = left;
		//backLeftMtr = left;
		//backRightMtr = right;

	}
}

void drive(){


}

void flywheel(){


}

void lift(){


}