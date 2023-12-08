#include <stdio.h>
#include <raylib.h>
#include <raymath.h>
#define ARMLEN 80
#define LEGLEN 100
#define THICKNESS 20
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
} player;
void initStick();
void drawStick();
void detectFalling() {
	//
};
int main() {
	InitWindow(SCREENWIDTH, SCREENHEIGHT, "StickFigure");
	SetTraceLogLevel(LOG_WARNING);
	SetTargetFPS(60);
	initStick();
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(WHITE);
		drawStick();
		EndDrawing();
	}
	CloseWindow();
	return 0;
}

void initStick() {
	player.neck = (Vector2){ 200,300 };
	player.center = (Vector2){ 200, 200 };
	player.headV = 0.5 * PI;
	player.elbowLeftV = 1.4 * PI;
	player.handLeftV = 1.45 * PI;
	player.elbowRightV = 1.6 * PI;
	player.handRightV = 1.55 * PI;
	player.kneeLeftV = 1.4 * PI;
	player.footLeftV = 1.5 * PI;
	player.kneeRightV = 1.6 * PI;
	player.footRightV = 1.5 * PI;
	player.color = BLACK;
}
void drawStick() {
	/* 只在绘图的时候将y坐标反过来, 程序其它部分按正常坐标习惯 */
	double headPosX = player.neck.x + ARMLEN / 2 * cos(player.headV);
	double headPosY = SCREENHEIGHT - (player.neck.y + ARMLEN / 2 * sin(player.headV));
	DrawCircle((int)headPosX, (int)headPosY, (float)ARMLEN / 2, player.color);
	Vector2 neck, elbowL, elbowR, handL, handR;
	neck.x = player.neck.x;
	neck.y = SCREENHEIGHT - player.neck.y;
	elbowL.x = (float)ARMLEN * cos(player.elbowLeftV);
	elbowL.y = (float)ARMLEN * sin(player.elbowLeftV);
	handL.x = (float)ARMLEN * cos(player.handLeftV);
	handL.y = (float)ARMLEN * sin(player.handLeftV);
	elbowL = Vector2Add(player.neck, elbowL);
	handL = Vector2Add(elbowL, handL);
	elbowL.y = SCREENHEIGHT - elbowL.y;
	handL.y = SCREENHEIGHT - handL.y;
	elbowR.x = (float)ARMLEN * cos(player.elbowRightV);
	elbowR.y = (float)ARMLEN * sin(player.elbowRightV);
	handR.x = (float)ARMLEN * cos(player.handRightV);
	handR.y = (float)ARMLEN * sin(player.handRightV);
	elbowR = Vector2Add(player.neck, elbowR);
	handR = Vector2Add(elbowR, handR);
	elbowR.y = SCREENHEIGHT - elbowR.y;
	handR.y = SCREENHEIGHT - handR.y;
	DrawLineEx(neck, elbowL, THICKNESS, player.color);
	DrawCircle((int)elbowL.x, (int)elbowL.y, THICKNESS / 2, player.color);
	DrawLineEx(elbowL, handL, THICKNESS, player.color);
	DrawCircle((int)handL.x, (int)handL.y, THICKNESS / 2, player.color);
	DrawLineEx(neck, elbowR, THICKNESS, player.color);
	DrawCircle((int)elbowR.x, (int)elbowR.y, THICKNESS / 2, player.color);
	DrawLineEx(elbowR, handR, THICKNESS, player.color);
	DrawCircle((int)handR.x, (int)handR.y, THICKNESS / 2, player.color);
	Vector2 center, kneeL, kneeR, footL, footR;
	center.x = player.center.x;
	center.y = SCREENHEIGHT - player.center.y;
	kneeL.x = (float)LEGLEN * cos(player.kneeLeftV);
	kneeL.y = (float)LEGLEN * sin(player.kneeLeftV);
	footL.x = (float)LEGLEN * cos(player.footLeftV);
	footL.y = (float)LEGLEN * sin(player.footLeftV);
	kneeL = Vector2Add(player.center, kneeL);
	footL = Vector2Add(kneeL, footL);
	kneeL.y = SCREENHEIGHT - kneeL.y;
	footL.y = SCREENHEIGHT - footL.y;
	kneeR.x = (float)LEGLEN * cos(player.kneeRightV);
	kneeR.y = (float)LEGLEN * sin(player.kneeRightV);
	footR.x = (float)LEGLEN * cos(player.footRightV);
	footR.y = (float)LEGLEN * sin(player.footRightV);
	kneeR = Vector2Add(player.center, kneeR);
	footR = Vector2Add(kneeR, footR);
	kneeR.y = SCREENHEIGHT - kneeR.y;
	footR.y = SCREENHEIGHT - footR.y;
	DrawLineEx(center, kneeL, THICKNESS, player.color);
	DrawCircle((int)kneeL.x, (int)kneeL.y, THICKNESS / 2, player.color);
	DrawLineEx(kneeL, footL, THICKNESS, player.color);
	DrawCircle((int)footL.x, (int)footL.y, THICKNESS / 2, player.color);
	DrawLineEx(center, kneeR, THICKNESS, player.color);
	DrawCircle((int)kneeR.x, (int)kneeR.y, THICKNESS / 2, player.color);
	DrawLineEx(kneeR, footR, THICKNESS, player.color);
	DrawCircle((int)footR.x, (int)footR.y, THICKNESS / 2, player.color);
	Vector2 control;
	control.x = neck.x;
	control.y = neck.y + ARMLEN/2;
	DrawSplineSegmentBezierQuadratic(center, control, neck, THICKNESS, player.color);
	DrawCircle(neck.x, neck.y, THICKNESS / 2, player.color);
	DrawCircle(center.x, center.y, THICKNESS / 2, player.color);
}