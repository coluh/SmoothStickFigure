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