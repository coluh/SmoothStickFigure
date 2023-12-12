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
enum PERIOD_HAND {
	HAND_STILL, HAND_PULL, HAND_HIT, HAND_BACK
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
	enum PERIOD_HAND armLeft;
	enum PERIOD_HAND armRight;
	enum PERIOD_HAND leftCut;
	enum PERIOD_HAND rightCut;
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
void InitStick();
void DrawStick(struct STICK);
void DetectEdge();
void CalculateStick();
void GetInput(double*);
void Punch(enum BODYPART);
void HandKnife();
void UpperCut();
void LowerHead();
void UpperHead();
void Squating();
void Standing();
void Walking(enum DIRECTION);
void RunningForward();
void Jumping();
void TouchGround(enum BODYPART);
bool IsOnGround(enum BODYPART part, int accuracy);
void DebugPrint();