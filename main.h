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
//enum PERIOD {
//	STILL,
//	PUNCH_LEFT_PULL, PUNCH_LEFT_HIT, PUNCH_LEFT_BACK,
//	PUNCH_RIGHT_PULL, PUNCH_RIGHT_HIT, PUNCH_RIGHT_BACK,
//
//};
enum PERIOD_PUNCH {
	STILL, PUNCH_PULL, PUNCH_HIT, PUNCH_BACK
};
struct PERIOD {
	enum PERIOD_PUNCH armLeft;
	enum PERIOD_PUNCH armRight;
	//
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
void getInput();
void punch(bool);
void lowerHead();
void upperHead();