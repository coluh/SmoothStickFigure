#include "main.h"
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
void punch(bool part) {
	//part: LEFTPART or RIGHTPART
	//printf("\n%lf\n%lf\n%lf\n%lf\n", player.elbowLeftV, player.handLeftV, player.elbowRightV, player.handRightV);
	if (!(player.elbowLeftV == 1.6 * PI && player.handLeftV == 0.4 * PI)) {
		return;
	}
	if (!(player.elbowRightV == 1.4 * PI && player.handRightV == 0.3 * PI)) {
		return;
	}
	/*
	* 暂不支持双手交换打
	* 
	*/
	switch (part) {
	case LEFTPART:
		status.elbowLeftV = -0.21 * PI;
		status.handLeftV = -0.31 * PI;
		break;
	case RIGHTPART:
		status.elbowRightV = -0.11 * PI;
		status.handRightV = -0.21 * PI;
		break;
	}
}
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