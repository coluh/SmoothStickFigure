#include "main.h"
extern struct PERIOD period;
extern struct STICK player;
extern struct STICK status;
/*
 * actions:
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
void DetectEdge() {
	if (player.headV < 0.25 * PI || player.headV > 0.4 * PI) {
		status.headV = 0;
	}
	if (player.elbowLeftV >= 2 * PI) {
		player.elbowLeftV -= 2 * PI;
	}
	if (player.elbowRightV >= 2 * PI) {
		player.elbowRightV -= 2 * PI;
	}
	if (player.handLeftV >= 2 * PI) {
		player.handLeftV -= 2 * PI;
	}
	if (player.handRightV >= 2 * PI) {
		player.handRightV -= 2 * PI;
	}
	RunningForward();
	Jumping();
	switch (period.armLeft) {
	case HAND_STILL:
		//do nothing
		break;
	case HAND_PULL:
		if (player.elbowLeftV <= 1.4 * PI/* && player.handLeftV < 0.1 * PI*/) {
			player.elbowLeftV = 1.4 * PI;
			player.handLeftV = 0.1 * PI;
			status.elbowLeftV = 0.55 * PI / 3;
			status.handLeftV = -0.15 * PI / 3;
			period.armLeft = HAND_HIT;
		}
		break;
	case HAND_HIT:
		if (player.elbowLeftV >= 1.95 * PI) {
			player.elbowLeftV = 1.95 * PI;
			player.handLeftV = 1.95 * PI;
			status.elbowLeftV = -0.35 * PI / 3;
			status.handLeftV = 0.45 * PI / 3;
			period.armLeft = HAND_BACK;
		}
		break;
	case HAND_BACK:
		if (player.elbowLeftV < 1.6 * PI) {
			player.elbowLeftV = 1.6 * PI;
			player.handLeftV = 0.4 * PI;
			status.elbowLeftV = 0;
			status.handLeftV = 0;
			period.armLeft = HAND_STILL;
		}
		break;
	}
	switch (period.armRight) {
	case HAND_STILL:
		//do nothing
		break;
	case HAND_PULL:
		if (player.elbowRightV <= 1.3 * PI/* && player.handRightV < 0.1 * PI*/) {
			player.elbowRightV = 1.3 * PI;
			player.handRightV = 0.1 * PI;
			status.elbowRightV = 0.65 * PI / 3;
			status.handRightV = -0.15 * PI / 3;
			period.armRight = HAND_HIT;
		}
		break;
	case HAND_HIT:
		if (player.elbowRightV >= 1.95 * PI) {
			player.elbowRightV = 1.95 * PI;
			player.handRightV = 1.95 * PI;
			status.elbowRightV = -0.55 * PI / 3;
			status.handRightV = 0.35 * PI / 3;
			period.armRight = HAND_BACK;
		}
		break;
	case HAND_BACK:
		if (player.elbowRightV < 1.4 * PI) {
			player.elbowRightV = 1.4 * PI;
			player.handRightV = 0.3 * PI;
			status.elbowRightV = 0;
			status.handRightV = 0;
			period.armRight = HAND_STILL;
		}
		break;
	}
	switch (period.leftCut) {
	case HAND_PULL:
		if (player.elbowLeftV > 0.4 * PI && player.elbowLeftV < 0.5 * PI) {
			player.elbowLeftV = 0.4 * PI;
			player.handLeftV = 0.4 * PI;
			period.leftCut = HAND_HIT;
			status.elbowLeftV = -0.4 * PI / 3;
			status.handLeftV = -0.4 * PI / 3;
		}
		break;
	case HAND_HIT:
		if (player.elbowLeftV < 0 && player.handLeftV < 0) {
			player.elbowLeftV = 1.99 * PI;
			player.handLeftV = 0;
			period.leftCut = HAND_BACK;
			status.elbowLeftV = -0.4 * PI / 8;
			status.handLeftV = 0.4 * PI / 8;
		}
		break;
	case HAND_BACK:
		if (player.elbowLeftV < 1.6 * PI && player.handLeftV > 0.4 * PI) {
			player.elbowLeftV = 1.6 * PI;
			player.handLeftV = 0.4 * PI;
			period.leftCut = HAND_STILL;
			status.elbowLeftV = 0;
			status.handLeftV = 0;
		}
		break;
	}
	switch (period.rightCut) {
	case HAND_PULL:
		if (player.handRightV < 0) {
			player.handRightV += 2 * PI;
		}
		if (player.elbowRightV < 1.1 * PI && player.handRightV < 1.8 * PI) {
			player.elbowRightV = 1.1 * PI;
			player.handRightV = 1.8 * PI;
			period.rightCut = HAND_HIT;
			status.elbowRightV = 1.0 * PI / 3;
			status.handRightV = 0.7 * PI / 3;
		}
		break;
	case HAND_HIT:
		if (player.elbowRightV > 0.1 * PI && player.handRightV > 0.5 * PI) {
			player.elbowRightV = 0.1 * PI;
			player.handRightV = 0.5 * PI;
			period.rightCut = HAND_BACK;
			status.elbowRightV = -0.7 * PI/6;
			status.handRightV = -0.2 * PI/6;
		}
		break;
	case HAND_BACK:
		if (player.elbowRightV < 0) {
			player.elbowRightV += 2 * PI;
		}
		if (player.elbowRightV < 1.4 * PI && player.handRightV < 0.3 * PI) {
			player.elbowRightV = 1.4 * PI;
			player.handRightV = 0.3 * PI;
			period.rightCut = HAND_STILL;
			status.elbowRightV = 0;
			status.handRightV = 0;
		}
		break;
	}
	//printf("\n \x1B[1;37;41mUndefined Motion \x1B[m");
	if (player.neck.y < 100) {
		player.neck.y += SCREENHEIGHT * 1.5;
		player.center.y += SCREENHEIGHT * 1.5;
	}
	if (player.center.x > SCREENWIDTH + 200) {
		player.center.x -= SCREENWIDTH + 400;
		player.neck.x -= SCREENWIDTH + 400;
	}
	if (player.center.x < -200) {
		player.center.x += SCREENWIDTH + 400;
		player.neck.x += SCREENWIDTH + 400;
	}
}
void LowerHead() {
	status.headV = -0.15 * PI / 4;
	if (player.headV >= 0.4 * PI) {
		player.headV = 0.4 * PI;
	}
}
void UpperHead() {
	status.headV = 0.15 * PI / 4;
	if (player.headV <= 0.25 * PI) {
		player.headV = 0.25 * PI;
	}
}
void Punch(enum BODYPART part) {
	//part: LEFTPART or RIGHTPART
	if (period.armLeft == HAND_PULL || period.armRight == HAND_PULL) {
		return;
	}
	switch (part) {
	case LEFTPART:
		if (period.armLeft == HAND_HIT || period.armLeft == HAND_BACK) {
			break;
		}
		if (period.leftCut != HAND_STILL) {
			break;
		}
		status.elbowLeftV = -0.2 * PI / 3;
		status.handLeftV = -0.3 * PI / 3;
		period.armLeft = HAND_PULL;
		break;
	case RIGHTPART:
		if (period.armRight == HAND_HIT || period.armRight == HAND_BACK) {
			break;
		}
		if (period.rightCut != HAND_STILL) {
			break;
		}
		status.elbowRightV = -0.1 * PI / 3;
		status.handRightV = -0.2 * PI / 3;
		period.armRight = HAND_PULL;
		break;
	}
}
void HandKnife() {
	status.elbowLeftV = 0.8 * PI / 4;
	period.leftCut = HAND_PULL;
}
void UpperCut() {
	status.elbowRightV = -0.3 * PI / 4;
	status.handRightV = -0.5 * PI / 4;
	period.rightCut = HAND_PULL;
}
void RunningForward() {
	if (period.legs == MOVE || period.legs == END) {
		return;
	}
	if (period.legs == RUNNING) {
		player.kneeLeftV += 0.035 * PI;
		player.footLeftV += 0.03 * PI;
		player.kneeRightV -= 0.03 * PI;
		player.footRightV -= 0.05 * PI;
		player.center.x += 9.3f;
		player.center.x += 9.3f;
		player.neck.x += 9.3f;
		player.neck.x += 9.3f;
		/*if (IsOnGround(RIGHTPART)) {
			TouchGround(RIGHTPART);
		}*/
		if (player.kneeLeftV > 1.8 * PI) {
			player.kneeLeftV = 1.8 * PI;
			player.footLeftV = 1.7 * PI;
			player.kneeRightV = 1.3 * PI;
			player.footRightV = 1.05 * PI;
			period.legs = FLYING;
		}
	}
	else {
		player.kneeLeftV -= 0.02 * PI;
		player.footLeftV -= 0.015 * PI;
		player.kneeRightV += 0.015 * PI;
		player.footRightV += 0.035 * PI;
		player.center.x += 9.3f;
		player.center.x += 9.3f;
		player.neck.x += 9.3f;
		player.neck.x += 9.3f;
		/*if (IsOnGround(LEFTPART)) {
			TouchGround(LEFTPART);
		}*/
		if (player.kneeLeftV < 1.6 * PI) {
			player.kneeLeftV = 1.45 * PI;
			player.footLeftV = 1.4 * PI;
			player.kneeRightV = 1.6 * PI;
			player.footRightV = 1.55 * PI;
			if (period.legs == FLYING) {
				period.legs = RUNNING;
			}
			else {
				player.neck.x -= 20;
				player.neck.y += 10;
				period.legs = MOVE;
			}
		}

	}
}
void Walking(enum DIRECTION direction) {
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
		if(period.bodyj!=ACCUMULATE){
			TouchGround(RIGHTPART);
		}
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
void TouchGround(enum BODYPART part) {
	double offsetY = player.center.y - GROUNDHEIGHT - THICKNESS / 2;
	if (part == RIGHTPART) {
		offsetY += LEGLEN * sin(player.kneeRightV) + LEGLEN * sin(player.footRightV);
	}
	else {
		offsetY += LEGLEN * sin(player.kneeLeftV) + LEGLEN * sin(player.footLeftV);
	}
	if (period.bodyj != JUMPING) {
		player.center.y -= offsetY;
		player.neck.y -= offsetY;
	}
}
bool IsOnGround(enum BODYPART part, int accuracy) {
	double offsetY = player.center.y - GROUNDHEIGHT - THICKNESS / 2;
	if (part == RIGHTPART) {
		offsetY += LEGLEN * sin(player.kneeRightV) + LEGLEN * sin(player.footRightV);
	}
	else {
		offsetY += LEGLEN * sin(player.kneeLeftV) + LEGLEN * sin(player.footLeftV);
	}
	if (offsetY <= accuracy && offsetY >= -accuracy) {
		return true;
	}
	return false;
}
void Squating() {
	switch (period.body) {
	case STANDING:
		period.body = SQUATDOWN;
		break;
	case SQUATDOWN:
		player.neck.x += 1;
		player.neck.y -= 1;
		player.kneeLeftV += 0.02 * PI;
		player.footLeftV -= 0.013 * PI;
		player.kneeRightV += 0.021 * PI;
		player.footRightV -= 0.005 * PI;
		if (player.kneeLeftV > 1.85 * PI) {
			player.kneeLeftV = 1.85 * PI;
			player.footLeftV = 1.14 * PI;
			player.kneeRightV = 0.02 * PI;
			player.footRightV = 1.45 * PI;
			player.neck.x = player.center.x + 30;
			player.neck.y = player.center.y + 80;
			period.body = SQUATING;
		}
		TouchGround(RIGHTPART);
		break;
	}
}
void Standing() {
	switch (period.body) {
	case SQUATING:
		period.body = SQUATDOWN;
		break;
	case SQUATDOWN:
		player.neck.x -= 1;
		player.neck.y += 1;
		player.kneeLeftV -= 0.02 * PI;
		player.footLeftV += 0.013 * PI;
		player.kneeRightV -= 0.021 * PI;
		player.footRightV += 0.005 * PI;
		if (player.kneeLeftV <= 1.45 * PI) {
			player.kneeLeftV = 1.45 * PI;
			player.footLeftV = 1.4 * PI;
			player.kneeRightV = 1.6 * PI;
			player.footRightV = 1.55 * PI;
			period.body = STANDING;
			player.neck.x = player.center.x + 10;
			player.neck.y = player.center.y + 100;
		}
		TouchGround(RIGHTPART);
		break;
	}
}
void Jumping() {
	switch (period.bodyj) {
	case ACCUMULATE:
		if (period.legs == MOVE || period.legs == END) {
			player.kneeLeftV += 0.01 * PI;
			player.kneeRightV += 0.01 * PI;
			player.footLeftV -= 0.01 * PI;
			player.footRightV -= 0.01 * PI;
			TouchGround(RIGHTPART);
		}
		status.center.x -= 1;//used for counting
		if (status.center.x <= -10) {
			period.bodyj = JUMPING;
			status.center.y = 30;
			status.neck.y = 30;
		}
		break;
	case JUMPING:
		status.center.y -= 1;
		status.neck.y -= 1;
		if (status.center.x == 0 && IsOnGround(RIGHTPART, 30)) {
			status.center.y = 0;
			status.neck.y = 0;
			period.bodyj = NOTJUMP;
			TouchGround(RIGHTPART);
			status.center.x = 0;
		}
		if (status.center.x < 0) {
			status.center.x += 1;
			if (period.legs == MOVE || period.legs == END) {
				player.kneeLeftV -= 0.01 * PI;
				player.kneeRightV -= 0.01 * PI;
				player.footLeftV += 0.01 * PI;
				player.footRightV += 0.01 * PI;
			}
		}
		break;
	}
}
void DebugPrint() {
	printf("\nperiod.armLeft: ");
	switch (period.armLeft) {
	case HAND_STILL:
		printf("HAND_STILL");
		break;
	case HAND_PULL:
		printf("HAND_PULL");
		break;
	case HAND_HIT:
		printf("HAND_HIT");
		break;
	case HAND_BACK:
		printf("HAND_BACK");
		break;
	}
	printf("\nperiod.armRight: ");
	switch (period.armRight) {
	case HAND_STILL:
		printf("HAND_STILL");
		break;
	case HAND_PULL:
		printf("HAND_PULL");
		break;
	case HAND_HIT:
		printf("HAND_HIT");
		break;
	case HAND_BACK:
		printf("HAND_BACK");
		break;
	}
	printf("\nperiod.leftCut: ");
	switch (period.leftCut) {
	case HAND_STILL:
		printf("HAND_STILL");
		break;
	case HAND_PULL:
		printf("HAND_PULL");
		break;
	case HAND_HIT:
		printf("HAND_HIT");
		break;
	case HAND_BACK:
		printf("HAND_BACK");
		break;
	}
	printf("\nperiod.rightCut: ");
	switch (period.rightCut) {
	case HAND_STILL:
		printf("HAND_STILL");
		break;
	case HAND_PULL:
		printf("HAND_PULL");
		break;
	case HAND_HIT:
		printf("HAND_HIT");
		break;
	case HAND_BACK:
		printf("HAND_BACK");
		break;
	}
	printf("\nelbowLeftV:%lf\nhandLeftV:%lf\nelbowRightV:%lf\nhandRightV:%lf\n",
		player.elbowLeftV, player.handLeftV, player.elbowRightV, player.handRightV);
}