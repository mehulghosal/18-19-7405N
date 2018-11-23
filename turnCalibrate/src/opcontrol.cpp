#include "main.h"

pros::Controller master(pros::E_CONTROLLER_MASTER);

//MOTOR INITS//
pros::Motor backLeftMtr(9);
pros::Motor frontLeftMtr(10);
pros::Motor frontRightMtr(2, pros::E_MOTOR_GEARSET_18, true);
pros::Motor backRightMtr(1, pros::E_MOTOR_GEARSET_18, true);

int left = 127;
int right = -127;


void chassisSet(int m1, int m2){
	backLeftMtr = m1;
	frontLeftMtr = m1;
	backRightMtr = m2;
	frontRightMtr = m2;
}

void opcontrol() {
	while (true) {
		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);

		if (master.get_digital(DIGITAL_UP) == 1 && upPressed == false){
			left = std::min(left + 1, 127);
			upPressed = true;
			pros::Task::delay(20);
		}
		else if (master.get_digital(DIGITAL_UP) == 0){
			upPressed = false;
		}

		if (master.get_digital(DIGITAL_DOWN) == 1 && downPressed == false){
			left = std::min(left - 1, 127);
			downPressed = true;
			pros::Task::delay(20);
		}
		else if (master.get_digital(DIGITAL_DOWN) == 0){
			downPressed = false;
		}



		chassisSet(left,right);
		pros::delay(20);

	}
}
