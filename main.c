#include "main.h"
struct PERIOD period = { 0 };
struct STICK player;
struct STICK status = { 0 };	//每帧的变化量
int main() {
	InitWindow(SCREENWIDTH, SCREENHEIGHT, "StickFigure");
	SetTraceLogLevel(LOG_WARNING);
	SetTargetFPS(90);
	InitStick();
	struct STICK friend = { 0 };
	//临时加上:
	do{
		friend.center = (Vector2){ 1700, 250 };
		friend.neck = (Vector2){ 1690, 350 };
		friend.headV = 0.6 * PI;
		friend.elbowLeftV = 1.4 * PI;
		friend.handLeftV = 0.6 * PI;
		friend.elbowRightV = 1 * PI;//Right Hit
		friend.handRightV = 1 * PI;//Right Hit
		friend.kneeLeftV = 1.55 * PI;
		friend.footLeftV = 1.6 * PI;
		friend.kneeRightV = 1.4 * PI;
		friend.footRightV = 1.45 * PI;
		friend.color = RED;
		//speed
	} while (0);
	double lastClickTime = 0;
	while (!WindowShouldClose()) {
		GetInput(&lastClickTime);
		CalculateStick();
		CalculateHit(NULL);
		CorrectPosture();
		BeginDrawing();
		ClearBackground(WHITE);
		DrawStick(player);
		DrawStick(friend);
		//Ground
		DrawLine(0, SCREENHEIGHT - GROUNDHEIGHT, SCREENWIDTH, SCREENHEIGHT - GROUNDHEIGHT, RED);
		DrawText(TextFormat("%d", GetFPS()), 50, 20, 50, RED);
		if (status.color.r == 0)DrawText("Double Jump: On", 200, 20, 60, GREEN);
		EndDrawing();
	}
	CloseWindow();
	return 0;
}

void GetInput(double* lastClickTime) {
	if (IsKeyPressed(KEY_H)) {
		Punch(LEFTPART);
	}
	if (IsKeyPressed(KEY_J) && (period.leftCut == HAND_STILL && (period.armLeft == HAND_STILL && (period.armRight == HAND_STILL || period.armRight == HAND_BACK)))) {
		HandKnife();
	}
	if (IsKeyPressed(KEY_K) && (period.rightCut == HAND_STILL && (period.armRight == HAND_STILL && (period.armLeft == HAND_STILL || period.armLeft == HAND_BACK)))) {
		UpperCut();
	}
	if (IsKeyPressed(KEY_L)) {
		Punch(RIGHTPART);
	}
	if (IsKeyPressed(KEY_W)) {
		LowerHead();
	}
	if (IsKeyReleased(KEY_W)) {
		UpperHead();
	}
	if (IsKeyPressed(KEY_Q)) {
		player.center.x -= 500;
		player.neck.x -= 500;
	}
	if (IsKeyPressed(KEY_R)) {
		InitStick();
	}
	if (IsKeyDown(KEY_D)) {
		if (period.body == SQUATING)
			WalkingSquating(FORWARD);
		else
			Walking(FORWARD);
	}
	else {
		if (IsKeyDown(KEY_A)) {
			if (period.body != SQUATING) {
				Walking(BACKWARD);
				Walking(BACKWARD);
			}
			else {
				WalkingSquating(BACKWARD);
				WalkingSquating(BACKWARD);
			}
		}
	}
	if (IsKeyPressed(KEY_D)) {
		double currentTime = GetTime();
		if (currentTime - *lastClickTime <= 0.4) {
			period.legs = RUNNING;
			player.neck.x += 20;
			player.neck.y -= 10;
			*lastClickTime = 0;
		}
		else {
			*lastClickTime = currentTime;
		}
	}
	if (IsKeyReleased(KEY_D)) {
		if (period.legs == RUNNING) {
			period.legs = MOVE;
			player.neck.x -= 20;
			player.neck.y += 10;
		}
		if (period.legs == FLYING) {
			period.legs = FALLING;
		}
	}
	if (IsKeyUp(KEY_A) && IsKeyUp(KEY_D)) {
		if (IsKeyDown(KEY_LEFT_SHIFT)) {
			Squating();
		}
		if (IsKeyUp(KEY_LEFT_SHIFT)) {
			Standing();
		}
	}
	if (IsKeyPressed(KEY_SPACE) && period.bodyj == NOTJUMP) {
		period.bodyj = ACCUMULATE;
	}
	if (IsKeyPressed(KEY_SPACE) && (status.color.r == 0 && period.bodyj == JUMPING)) {
		status.center.y = 30;
		status.neck.y = 30;

	}
	if (IsKeyPressed(KEY_B)) {
		SetDoubleJump();
	}

}
void InitStick() {
	player.headV = 0.4 * PI;
	player.neck = (Vector2){ 210,350 };
	player.elbowLeftV = 1.6 * PI;
	player.handLeftV = 0.4 * PI;
	player.elbowRightV = 1.4 * PI;
	player.handRightV = 0.3 * PI;
	player.center = (Vector2){ 200, 250 };
	player.kneeLeftV = 1.45 * PI;
	player.footLeftV = 1.4 * PI;
	player.kneeRightV = 1.6 * PI;
	player.footRightV = 1.55 * PI;
	player.color = SKYBLUE;
	status.color = WHITE;
	TouchGround(RIGHTPART);
	/*period.armLeft = STILL;
	period.armRight = STILL;*/
}
void DrawStick(struct STICK player) {
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
void CalculateStick() {
	//Step 1: Detect edge conditions
	DetectEdge();
	//Step 2: Weaken Speed
	status.headV *= 0.9;
	status.elbowLeftV *= 0.9;
	status.handLeftV *= 0.9;
	status.elbowRightV *= 0.9;
	status.handRightV *= 0.9;
	//Step 3: Time past 1 frame
	player.headV += status.headV;
	player.elbowLeftV += status.elbowLeftV;
	player.handLeftV += status.handLeftV;
	player.elbowRightV += status.elbowRightV;
	player.handRightV += status.handRightV;
	player.center.y += status.center.y;
	player.neck.y += status.neck.y;
}
void CalculateHit(struct PERIOD* p) {
	//
}