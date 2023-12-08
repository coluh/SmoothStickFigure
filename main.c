#include "main.h"
static bool b1 = true, b2 = false, b3 = false;
struct STICK player;
struct STICK status = { 0 };	//每帧的变化量
int main() {
	InitWindow(SCREENWIDTH, SCREENHEIGHT, "StickFigure");
	SetTraceLogLevel(LOG_WARNING);
	SetTargetFPS(60);
	initStick();
	while (!WindowShouldClose()) {
		getInput();
		calculateStick();
		BeginDrawing();
		ClearBackground(WHITE);
		drawStick();
		EndDrawing();
	}
	CloseWindow();
	return 0;
}

void getInput() {
	if (IsKeyPressed(KEY_H)) {
		punch(LEFTPART);
	}
	if (IsKeyPressed(KEY_L)) {
		punch(RIGHTPART);
	}
	if (IsKeyPressed(KEY_W)) {
		lowerHead();
	}
	if (IsKeyReleased(KEY_W)) {
		upperHead();
	}
}
void initStick() {
	player.headV = 0.4 * PI;
	player.neck = (Vector2){ 200,300 };
	player.elbowLeftV = 1.6 * PI;
	player.handLeftV = 0.4 * PI;
	player.elbowRightV = 1.4 * PI;
	player.handRightV = 0.3 * PI;
	player.center = (Vector2){ 200, 200 };
	player.kneeLeftV = 1.4 * PI;
	player.footLeftV = 1.45 * PI;
	player.kneeRightV = 1.6 * PI;
	player.footRightV = 1.55 * PI;
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
	control.y = neck.y + ARMLEN / 2;
	DrawSplineSegmentBezierQuadratic(center, control, neck, THICKNESS, player.color);
	DrawCircle(neck.x, neck.y, THICKNESS / 2, player.color);
	DrawCircle(center.x, center.y, THICKNESS / 2, player.color);
}
void detectEdge() {
	if (player.headV < 0.25 * PI || player.headV > 0.4 * PI) {
		status.headV = 0;
	}
	if (b1) {
		if (player.elbowLeftV <= 1.4 * PI/* && player.handLeftV < 0.1 * PI*/) {
			player.elbowLeftV = 1.4 * PI;
			player.handLeftV = 0.1 * PI;
			status.elbowLeftV = 0.56 * PI;
			status.handLeftV = -0.16 * PI;
			b1 = false;
			b2 = true;
			b3 = false;
		}
		if (player.elbowRightV <= 1.3 * PI/* && player.handRightV < 0.1 * PI*/) {
			player.elbowRightV = 1.3 * PI;
			player.handRightV = 0.1 * PI;
			status.elbowRightV = 0.66 * PI;
			status.handRightV = -0.16 * PI;
			b1 = false;
			b2 = true;
			b3 = false;
		}
	}
	if (b2) {
		if (player.elbowLeftV >= 1.95 * PI) {
			player.elbowLeftV = 1.95 * PI;
			player.handLeftV = 1.95 * PI;
			status.elbowLeftV = -0.36 * PI;
			status.handLeftV = 0.46 * PI;
			b1 = false;
			b2 = false;
			b3 = true;
		}
		if (player.elbowRightV >= 1.95 * PI) {
			player.elbowRightV = 1.95 * PI;
			player.handRightV = 1.95 * PI;
			status.elbowRightV = -0.56 * PI;
			status.handRightV = 0.36 * PI;
			b1 = false;
			b2 = false;
			b3 = true;
		}
	}
	if (b3) {
		if (player.elbowLeftV < 1.6 * PI) {
			player.elbowLeftV = 1.6 * PI;
			player.handLeftV = 0.4 * PI;
			status.elbowLeftV = 0;
			status.handLeftV = 0;
			b1 = true;
			b2 = false;
			b3 = false;
		}
		if (player.elbowRightV < 1.4 * PI) {
			player.elbowRightV = 1.4 * PI;
			player.handRightV = 0.3 * PI;
			status.elbowRightV = 0;
			status.handRightV = 0;
			b1 = true;
			b2 = false;
			b3 = false;
		}
	}
	if (player.handLeftV >= 2 * PI) {
		player.handLeftV -= 2 * PI;
	}
	if (player.handRightV >= 2 * PI) {
		player.handRightV -= 2 * PI;
	}
}
void calculateStick() {
	//Step 1: Detect edge conditions
	detectEdge();
	//Step 2: Weaken Speed
	status.headV *= 0.5;
	status.elbowLeftV *= 0.5;
	status.handLeftV *= 0.5;
	status.elbowRightV *= 0.5;
	status.handRightV *= 0.5;
	//Step 3: Time past 1 frame
	player.headV += status.headV;
	player.elbowLeftV += status.elbowLeftV;
	player.handLeftV += status.handLeftV;
	player.elbowRightV += status.elbowRightV;
	player.handRightV += status.handRightV;
}