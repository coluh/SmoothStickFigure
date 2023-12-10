#include "main.h"
extern struct PERIOD period;
extern struct STICK player;
extern struct STICK status;
/* actions:
* w
* a
* d
* h
* j
* k
* l
* shift
* space
*/
void lowerHead() {
	status.headV = -0.15 * PI;
	if (player.headV >= 0.4 * PI) {
		player.headV = 0.4 * PI;
	}
}
void upperHead() {
	status.headV = 0.15 * PI;
	if (player.headV <= 0.25 * PI) {
		player.headV = 0.25 * PI;
	}
}
void punch(bool part) {
	//part: LEFTPART or RIGHTPART
	//printf("\n%lf\n%lf\n%lf\n%lf\n", player.elbowLeftV, player.handLeftV, player.elbowRightV, player.handRightV);
	if (period.armLeft == PUNCH_PULL || period.armRight == PUNCH_PULL) {
		return;
	}
	switch (part) {
	case LEFTPART:
		if (period.armLeft == PUNCH_HIT || period.armLeft == PUNCH_BACK) {
			break;
		}
		status.elbowLeftV = -0.21 * PI;
		status.handLeftV = -0.31 * PI;
		period.armLeft = PUNCH_PULL;
		break;
	case RIGHTPART:
		if (period.armRight == PUNCH_HIT || period.armRight == PUNCH_BACK) {
			break;
		}
		status.elbowRightV = -0.11 * PI;
		status.handRightV = -0.21 * PI;
		period.armRight = PUNCH_PULL;
		break;
	}
}
void detectEdge() {
	if (player.headV < 0.25 * PI || player.headV > 0.4 * PI) {
		status.headV = 0;
	}
	switch (period.armLeft) {
	case STILL:
		//do nothing
		break;
	case PUNCH_PULL:
		if (player.elbowLeftV <= 1.4 * PI/* && player.handLeftV < 0.1 * PI*/) {
			player.elbowLeftV = 1.4 * PI;
			player.handLeftV = 0.1 * PI;
			status.elbowLeftV = 0.56 * PI;
			status.handLeftV = -0.16 * PI;
			period.armLeft = PUNCH_HIT;
		}
		break;
	case PUNCH_HIT:
		if (player.elbowLeftV >= 1.95 * PI) {
			player.elbowLeftV = 1.95 * PI;
			player.handLeftV = 1.95 * PI;
			status.elbowLeftV = -0.36 * PI;
			status.handLeftV = 0.46 * PI;
			period.armLeft = PUNCH_BACK;
		}
		break;
	case PUNCH_BACK:
		if (player.elbowLeftV < 1.6 * PI) {
			player.elbowLeftV = 1.6 * PI;
			player.handLeftV = 0.4 * PI;
			status.elbowLeftV = 0;
			status.handLeftV = 0;
			period.armLeft = STILL;
		}
		break;
	}
	switch (period.armRight) {
	case STILL:
		//do nothing
		break;
	case PUNCH_PULL:
		if (player.elbowRightV <= 1.3 * PI/* && player.handRightV < 0.1 * PI*/) {
			player.elbowRightV = 1.3 * PI;
			player.handRightV = 0.1 * PI;
			status.elbowRightV = 0.66 * PI;
			status.handRightV = -0.16 * PI;
			period.armRight = PUNCH_HIT;
		}
		break;
	case PUNCH_HIT:
		if (player.elbowRightV >= 1.95 * PI) {
			player.elbowRightV = 1.95 * PI;
			player.handRightV = 1.95 * PI;
			status.elbowRightV = -0.56 * PI;
			status.handRightV = 0.36 * PI;
			period.armRight = PUNCH_BACK;
		}
		break;
	case PUNCH_BACK:
		if (player.elbowRightV < 1.4 * PI) {
			player.elbowRightV = 1.4 * PI;
			player.handRightV = 0.3 * PI;
			status.elbowRightV = 0;
			status.handRightV = 0;
			period.armRight = STILL;
		}
		break;
	}
	if (player.handLeftV >= 2 * PI) {
		player.handLeftV -= 2 * PI;
	}
	if (player.handRightV >= 2 * PI) {
		player.handRightV -= 2 * PI;
	}
	//printf("\n \x1B[1;37;41mUndefined Motion \x1B[m");
}