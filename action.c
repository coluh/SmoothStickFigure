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
void runningForward() {
	if (period.legs == MOVE || period.legs == END) {
		return;
	}
	if (period.legs == RUNNING) {
		/*player.kneeLeftV += 0.035 * PI;
		  player.footLeftV += 0.03 * PI;
		  player.kneeRightV -= 0.03 * PI;
		  player.footRightV -= 0.05 * PI;*/
		
		player.center.x += 9.3;
		player.center.x += 9.3;
		player.neck.x += 9.3;
		player.neck.x += 9.3;
		/*if (onGround(RIGHTPART)) {
			touchGround(RIGHTPART);
		}*/
		if (player.kneeLeftV > 1.8 * PI) {
			player.kneeLeftV = 1.8 * PI;
			player.footLeftV = 1.7 * PI;
			player.kneeRightV = 1.3 * PI;
			player.footRightV = 1.05 * PI;
			status.kneeLeftV = -0.21 * PI;
			status.footLeftV = -0.151 * PI;
			status.kneeRightV = 0.151 * PI;
			status.footRightV = 0.351 * PI;
			period.legs = FLYING;
		}
	}
	else {
		
		player.center.x += 9.3;
		player.center.x += 9.3;
		player.neck.x += 9.3;
		player.neck.x += 9.3;
		/*if (onGround(LEFTPART)) {
			touchGround(LEFTPART);
		}*/
		if (player.kneeLeftV < 1.6 * PI) {
			player.kneeLeftV = 1.45 * PI;
			player.footLeftV = 1.4 * PI;
			player.kneeRightV = 1.6 * PI;
			player.footRightV = 1.55 * PI;
			status.kneeLeftV = 0;
			status.footLeftV = 0;
			status.kneeRightV = 0;
			status.footRightV = 0;
			if (period.legs == FLYING) {
				period.legs = RUNNING;
				status.kneeLeftV = 0.351 * PI;
				status.footLeftV = 0.31 * PI;
				status.kneeRightV = -0.31 * PI;
				status.footRightV = -0.51 * PI;
			}
			else {
				player.neck.x -= 20;
				player.neck.y += 10;
				period.legs = MOVE;
			}
		}

	}
}
void walking(enum DIRECTION direction) {
	switch (period.legs) {
	case MOVE:
		player.kneeLeftV += 0.005 * PI;
		player.footLeftV += 0.005 * PI;
		player.kneeRightV -= 0.005 * PI;
		player.footRightV -= 0.005 * PI;
		if (direction == FORWARD) {
			player.center.x += 3.103f;
			player.neck.x += 3.103f;
			if (player.kneeLeftV > 1.6 * PI) {
				period.legs = END;
			}
		}
		else {
			player.center.x -= 3.103f;
			player.neck.x -= 3.103f;
			if (player.kneeLeftV > 1.6 * PI) {
				period.legs = END;
			}
		}
		touchGround(RIGHTPART);
		break;
	case END:
		player.kneeLeftV = 1.45 * PI;
		player.footLeftV = 1.4 * PI;
		player.kneeRightV = 1.6 * PI;
		player.footRightV = 1.55 * PI;
		period.legs = MOVE;
		break;
	}
}
void detectEdge() {
	if (player.headV < 0.25 * PI || player.headV > 0.4 * PI) {
		status.headV = 0;
	}
	runningForward();
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
void touchGround(bool part) {
	double offsetY = player.center.y - GROUNDHEIGHT - THICKNESS / 2;
	if (part == RIGHTPART) {
		offsetY += LEGLEN * sin(player.kneeRightV) + LEGLEN * sin(player.footRightV);
	}
	else {
		offsetY += LEGLEN * sin(player.kneeLeftV) + LEGLEN * sin(player.footLeftV);
	}
	player.center.y -= offsetY;
	player.neck.y -= offsetY;
}
bool onGround(bool part) {
	double offsetY = player.center.y - GROUNDHEIGHT - THICKNESS / 2;
	if (part == RIGHTPART) {
		offsetY += LEGLEN * sin(player.kneeRightV) + LEGLEN * sin(player.footRightV);
	}
	else {
		offsetY += LEGLEN * sin(player.kneeLeftV) + LEGLEN * sin(player.footLeftV);
	}
	if (offsetY <= 1 && offsetY >= -1) {
		return true;
	}
}