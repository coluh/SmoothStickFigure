#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <raylib.h>
#include <raymath.h>
#define LEFTPART false
#define RIGHTPART true
#define ARMLEN 80
#define LEGLEN 100
#define THICKNESS 12		//maybe 20 is like Alan's
#define SCREENWIDTH 2100
#define SCREENHEIGHT 900
#define GROUNDHEIGHT 40
enum DIRECTION {
	BACKWARD, FORWARD
};
enum PERIOD_PUNCH {
	STILL, PUNCH_PULL, PUNCH_HIT, PUNCH_BACK
};
enum PERIOD_WALK {
	MOVE, END, RUNNING, FLYING, FALLING
};
struct PERIOD {
	enum PERIOD_PUNCH armLeft;
	enum PERIOD_PUNCH armRight;
	enum PERIOD_WALK legs;
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
void punch(bool);
void lowerHead();
void upperHead();
void walking(enum DIRECTION);
void runningForward();
void touchGround(bool);
bool onGround(bool);