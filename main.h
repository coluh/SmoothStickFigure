#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <raylib.h>
#include <raymath.h>
#define ARMLEN 80
#define LEGLEN 100
#define THICKNESS 12		//maybe 20 is like Alan's
#define SCREENWIDTH 2100
#define SCREENHEIGHT 900
#define GROUNDHEIGHT 40
enum BODYPART {
	LEFTPART, RIGHTPART
};
enum DIRECTION {
	BACKWARD, FORWARD
};
enum PERIOD_PUNCH {
	PUNCH_STILL, PUNCH_PULL, PUNCH_HIT, PUNCH_BACK
};
enum PERIOD_WALK {
	MOVE, END, RUNNING, FLYING, FALLING
};
enum PERIOD_SQUAT {
	STANDING, SQUATDOWN, SQUATING
};
enum PERIOD_JUMP {
	NOTJUMP, ACCUMULATE, JUMPING
};
struct PERIOD {
	enum PERIOD_PUNCH armLeft;
	enum PERIOD_PUNCH armRight;
	enum PERIOD_PUNCH leftCut;
	enum PERIOD_PUNCH rightCut;
	enum PERIOD_WALK legs;
	enum PERIOD_SQUAT body;
	enum PERIOD_JUMP bodyj;
};
struct STICK {
	double headV;			/*    (_)  80	*/
	Vector2 neck;			/*	   |   *5	*/
	double elbowLeftV;		/*   / |		*/
	double handLeftV;		/*  |  |		*/
	double elbowRightV;		/*     | \		*/
	double handRightV;		/*     |  |		*/
	Vector2 center;			/*     |  100	*/
	double kneeLeftV;		/*    /	   *5	*/
	double footLeftV;		/*   |			*/
	double kneeRightV;		/*       \	    */
	double footRightV;		/*        |	    */
	Color color;
};
void initStick();
void drawStick();
void calculateStick();
void getInput(double*);
void punch(enum BODYPART);
void handKnife();
void upperCut();
void lowerHead();
void upperHead();
void squating();
void standing();
void walking(enum DIRECTION);
void runningForward();
void jumping();
void touchGround(enum BODYPART);
bool onGround(enum BODYPART, int);