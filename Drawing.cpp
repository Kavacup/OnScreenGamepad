#include "Drawing.h"
#include <GLFW/glfw3.h>
#include "Positioning constants.h"

float GLOBAL_ALPHA = 0.5f;
float GLOBAL_ALPHA_ELEMENTS = GLOBAL_ALPHA;
float GLOBAL_BRIGHTNESS_ELEMENTS = GLOBAL_ALPHA;
float BUTTON_COLOR[] = { 1 * GLOBAL_BRIGHTNESS_ELEMENTS, 0.32f * GLOBAL_BRIGHTNESS_ELEMENTS, 0.54f * GLOBAL_BRIGHTNESS_ELEMENTS };
float STICK_COLOR[] = { 0 * GLOBAL_BRIGHTNESS_ELEMENTS, 1 * GLOBAL_BRIGHTNESS_ELEMENTS, 0 * GLOBAL_BRIGHTNESS_ELEMENTS };
float THUMB_COLOR[] = { 1 * GLOBAL_BRIGHTNESS_ELEMENTS, 0.32f * GLOBAL_BRIGHTNESS_ELEMENTS, 0.54f * GLOBAL_BRIGHTNESS_ELEMENTS };
float TRIGGER_COLOR[] = { 0.8f * GLOBAL_BRIGHTNESS_ELEMENTS, 0 * GLOBAL_BRIGHTNESS_ELEMENTS, 0.8f * GLOBAL_BRIGHTNESS_ELEMENTS };

void updateColors() {
	BUTTON_COLOR[0] = 1 * GLOBAL_BRIGHTNESS_ELEMENTS;
	BUTTON_COLOR[1] = 0 * GLOBAL_BRIGHTNESS_ELEMENTS;
	BUTTON_COLOR[2] = 0 * GLOBAL_BRIGHTNESS_ELEMENTS;

	STICK_COLOR[0] = 0 * GLOBAL_BRIGHTNESS_ELEMENTS;
	STICK_COLOR[1] = 1 * GLOBAL_BRIGHTNESS_ELEMENTS;
	STICK_COLOR[2] = 0 * GLOBAL_BRIGHTNESS_ELEMENTS;

	THUMB_COLOR[0] = 1 * GLOBAL_BRIGHTNESS_ELEMENTS;
	THUMB_COLOR[1] = 0 * GLOBAL_BRIGHTNESS_ELEMENTS;
	THUMB_COLOR[2] = 0 * GLOBAL_BRIGHTNESS_ELEMENTS;

	TRIGGER_COLOR[0] = 0.8f * GLOBAL_BRIGHTNESS_ELEMENTS;
	TRIGGER_COLOR[1] = 0 * GLOBAL_BRIGHTNESS_ELEMENTS;
	TRIGGER_COLOR[2] = 0.8f * GLOBAL_BRIGHTNESS_ELEMENTS;
}

void drawCircle(float x, float y, float radius, int verts) {
	if (verts < 4) return;
	if (radius <= 0) return;
	GLfloat twicePi = 2.0f * M_PI;
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y); // center of circle
	for (int i = 0; i <= verts; i++) {
		glVertex2f(
			x + (radius * cos(i * twicePi / verts)),
			y + (radius * sin(i * twicePi / verts))
		);
	}
	glEnd();
}

void drawCircleSector(float x, float y, float radius, float a1, float a2, int verts) {
	if (verts < 3) return;
	if (radius <= 0) return;
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y); // center of circle
	for (int i = 0; i < verts - 1; i++) {
		glVertex2f(
			x + radius * cos((a1 + i * (a2 - a1) / (verts - 1)) / 180.f * M_PI),
			y + radius * sin((a1 + i * (a2 - a1) / (verts - 1)) / 180.f * M_PI)
		);
	}
	glVertex2f(
		x + radius * cos(a2/180.f * M_PI),
		y + radius * sin(a2/180.f * M_PI)
	);
	glEnd();
}

void drawCircleSegment(float x, float y, float radius, float a1, float a2, int verts) {
	if (verts < 3) return;
	if (radius <= 0) return;
	glBegin(GL_TRIANGLE_FAN);
	//glVertex2f(x, y); // center of circle
	for (int i = 0; i < verts - 1; i++) {
		glVertex2f(
			x + radius * cos((a1 + i * (a2 - a1) / (verts - 1)) / 180.f * M_PI),
			y + radius * sin((a1 + i * (a2 - a1) / (verts - 1)) / 180.f * M_PI)
		);
	}
	glVertex2f(
		x + radius * cos(a2 / 180.f * M_PI),
		y + radius * sin(a2 / 180.f * M_PI)
	);
	glEnd();
}



void drawTexturedRect(float x, float y, float w, float h, GLuint texture) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_FALSE);
	glDisable(GL_DEPTH_TEST);
	glColor4f(1, 1, 1, GLOBAL_ALPHA);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex2f(x, y);
	glTexCoord2f(1, 0);
	glVertex2f(x + w, y);
	glTexCoord2f(1, 1);
	glVertex2f(x + w, y + h);
	glTexCoord2f(0, 1);
	glVertex2f(x, y + h);
	glTexCoord2f(0, 0);
	glVertex2f(x, y);
	glEnd();
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}

void drawRect(float x, float y, float w, float h) {
	glBegin(GL_QUADS);
	glVertex2f(x, y);
	glVertex2f(x + w, y);
	glVertex2f(x + w, y + h);
	glVertex2f(x, y + h);
	glVertex2f(x, y);
	glEnd();
}

void drawButtonPressed(float x, float y, float radius) {
	float currentColor[4];
	glGetFloatv(GL_CURRENT_COLOR, currentColor);
	glColor4f(BUTTON_COLOR[0], BUTTON_COLOR[1], BUTTON_COLOR[2], GLOBAL_ALPHA_ELEMENTS);
	drawCircle(x, y, radius, 60);
	glColor4f(currentColor[0], currentColor[1], currentColor[2], currentColor[3]);
}
#ifdef PS_PROFILE
void drawLeftDPAD() {
	float currentColor[4];
	glGetFloatv(GL_CURRENT_COLOR, currentColor);
	glColor4f(BUTTON_COLOR[0], BUTTON_COLOR[1], BUTTON_COLOR[2], GLOBAL_ALPHA_ELEMENTS);
	drawRect(DPAD_LEFT_LEFT_TOP_ANGLE_X, DPAD_LEFT_LEFT_TOP_ANGLE_Y, DPAD_LENGTH, DPAD_HEIGHT);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(DPAD_LEFT_LEFT_TOP_ANGLE_X + DPAD_LENGTH, DPAD_LEFT_LEFT_TOP_ANGLE_Y);
	glVertex2f(DPAD_LEFT_LEFT_TOP_ANGLE_X + DPAD_LENGTH + DPAD_TRIANGLE_DELTA_X, DPAD_LEFT_LEFT_TOP_ANGLE_Y + DPAD_TRIANGLE_DELTA_Y1);
	glVertex2f(DPAD_LEFT_LEFT_TOP_ANGLE_X + DPAD_LENGTH + DPAD_TRIANGLE_DELTA_X, DPAD_LEFT_LEFT_TOP_ANGLE_Y + DPAD_TRIANGLE_DELTA_Y2);
	glVertex2f(DPAD_LEFT_LEFT_TOP_ANGLE_X + DPAD_LENGTH, DPAD_LEFT_LEFT_TOP_ANGLE_Y + DPAD_HEIGHT);
	glVertex2f(DPAD_LEFT_LEFT_TOP_ANGLE_X + DPAD_LENGTH, DPAD_LEFT_LEFT_TOP_ANGLE_Y);
	glEnd();
	glColor4f(currentColor[0], currentColor[1], currentColor[2], currentColor[3]);
}
void drawRightDPAD() {
	float currentColor[4];
	glGetFloatv(GL_CURRENT_COLOR, currentColor);
	glColor4f(BUTTON_COLOR[0], BUTTON_COLOR[1], BUTTON_COLOR[2], GLOBAL_ALPHA_ELEMENTS);
	drawRect(DPAD_RIGHT_RIGHT_TOP_ANGLE_X, DPAD_RIGHT_RIGHT_TOP_ANGLE_Y, -DPAD_LENGTH, DPAD_HEIGHT);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(DPAD_RIGHT_RIGHT_TOP_ANGLE_X + -DPAD_LENGTH, DPAD_RIGHT_RIGHT_TOP_ANGLE_Y);
	glVertex2f(DPAD_RIGHT_RIGHT_TOP_ANGLE_X + -DPAD_LENGTH - DPAD_TRIANGLE_DELTA_X, DPAD_RIGHT_RIGHT_TOP_ANGLE_Y + DPAD_TRIANGLE_DELTA_Y1);
	glVertex2f(DPAD_RIGHT_RIGHT_TOP_ANGLE_X + -DPAD_LENGTH - DPAD_TRIANGLE_DELTA_X, DPAD_RIGHT_RIGHT_TOP_ANGLE_Y + DPAD_TRIANGLE_DELTA_Y2);
	glVertex2f(DPAD_RIGHT_RIGHT_TOP_ANGLE_X + -DPAD_LENGTH, DPAD_RIGHT_RIGHT_TOP_ANGLE_Y + DPAD_HEIGHT);
	glVertex2f(DPAD_RIGHT_RIGHT_TOP_ANGLE_X + -DPAD_LENGTH, DPAD_RIGHT_RIGHT_TOP_ANGLE_Y);
	glEnd();
	glColor4f(currentColor[0], currentColor[1], currentColor[2], currentColor[3]);
}
void drawTopDPAD() {
	float currentColor[4];
	glGetFloatv(GL_CURRENT_COLOR, currentColor);
	glColor4f(BUTTON_COLOR[0], BUTTON_COLOR[1], BUTTON_COLOR[2], GLOBAL_ALPHA_ELEMENTS);
	drawRect(DPAD_TOP_LEFT_TOP_ANGLE_X, DPAD_TOP_LEFT_TOP_ANGLE_Y, DPAD_HEIGHT, DPAD_LENGTH);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(DPAD_TOP_LEFT_TOP_ANGLE_X, DPAD_TOP_LEFT_TOP_ANGLE_Y + DPAD_LENGTH);
	glVertex2f(DPAD_TOP_LEFT_TOP_ANGLE_X + DPAD_TRIANGLE_DELTA_Y1, DPAD_TOP_LEFT_TOP_ANGLE_Y + DPAD_LENGTH + DPAD_TRIANGLE_DELTA_X);
	glVertex2f(DPAD_TOP_LEFT_TOP_ANGLE_X + DPAD_TRIANGLE_DELTA_Y2, DPAD_TOP_LEFT_TOP_ANGLE_Y + DPAD_LENGTH + DPAD_TRIANGLE_DELTA_X);
	glVertex2f(DPAD_TOP_LEFT_TOP_ANGLE_X + DPAD_HEIGHT, DPAD_TOP_LEFT_TOP_ANGLE_Y + DPAD_LENGTH);
	glVertex2f(DPAD_TOP_LEFT_TOP_ANGLE_X, DPAD_TOP_LEFT_TOP_ANGLE_Y + DPAD_LENGTH);
	glEnd();
	glColor4f(currentColor[0], currentColor[1], currentColor[2], currentColor[3]);
}
void drawBottomDPAD() {
	float currentColor[4];
	glGetFloatv(GL_CURRENT_COLOR, currentColor);
	glColor4f(BUTTON_COLOR[0], BUTTON_COLOR[1], BUTTON_COLOR[2], GLOBAL_ALPHA_ELEMENTS);
	drawRect(DPAD_BOTTOM_LEFT_BOTTOM_ANGLE_X, DPAD_BOTTOM_LEFT_BOTTOM_ANGLE_Y, DPAD_HEIGHT, -DPAD_LENGTH);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(DPAD_BOTTOM_LEFT_BOTTOM_ANGLE_X, DPAD_BOTTOM_LEFT_BOTTOM_ANGLE_Y + -DPAD_LENGTH);
	glVertex2f(DPAD_BOTTOM_LEFT_BOTTOM_ANGLE_X + DPAD_TRIANGLE_DELTA_Y1, DPAD_BOTTOM_LEFT_BOTTOM_ANGLE_Y + -DPAD_LENGTH + -DPAD_TRIANGLE_DELTA_X);
	glVertex2f(DPAD_BOTTOM_LEFT_BOTTOM_ANGLE_X + DPAD_TRIANGLE_DELTA_Y2, DPAD_BOTTOM_LEFT_BOTTOM_ANGLE_Y + -DPAD_LENGTH + -DPAD_TRIANGLE_DELTA_X);
	glVertex2f(DPAD_BOTTOM_LEFT_BOTTOM_ANGLE_X + DPAD_HEIGHT, DPAD_BOTTOM_LEFT_BOTTOM_ANGLE_Y + -DPAD_LENGTH);
	glVertex2f(DPAD_BOTTOM_LEFT_BOTTOM_ANGLE_X, DPAD_BOTTOM_LEFT_BOTTOM_ANGLE_Y + -DPAD_LENGTH);
	glEnd();;
	glColor4f(currentColor[0], currentColor[1], currentColor[2], currentColor[3]);
}
void drawStart() {
	float currentColor[4];
	glGetFloatv(GL_CURRENT_COLOR, currentColor);
	glColor4f(BUTTON_COLOR[0], BUTTON_COLOR[1], BUTTON_COLOR[2], GLOBAL_ALPHA_ELEMENTS);
	drawCircle(BUTTON_START_PIVOT_1_X, BUTTON_START_PIVOT_1_Y, BUTTON_START_BACK_RADIUS, 16);
	drawRect(BUTTON_START_PIVOT_1_X - BUTTON_START_BACK_RADIUS, BUTTON_START_PIVOT_1_Y,
		BUTTON_START_BACK_RADIUS * 2, BUTTON_START_PIVOT_2_Y - BUTTON_START_PIVOT_1_Y);
	drawCircle(BUTTON_START_PIVOT_2_X, BUTTON_START_PIVOT_2_Y, BUTTON_START_BACK_RADIUS, 16);
	glColor4f(currentColor[0], currentColor[1], currentColor[2], currentColor[3]);
}
void drawBack() {
	float currentColor[4];
	glGetFloatv(GL_CURRENT_COLOR, currentColor);
	glColor4f(BUTTON_COLOR[0], BUTTON_COLOR[1], BUTTON_COLOR[2], GLOBAL_ALPHA_ELEMENTS);
	drawCircle(BUTTON_BACK_PIVOT_1_X, BUTTON_BACK_PIVOT_1_Y, BUTTON_START_BACK_RADIUS, 16);
	drawRect(BUTTON_BACK_PIVOT_1_X - BUTTON_START_BACK_RADIUS, BUTTON_BACK_PIVOT_1_Y,
		BUTTON_START_BACK_RADIUS * 2, BUTTON_BACK_PIVOT_2_Y - BUTTON_BACK_PIVOT_1_Y);
	drawCircle(BUTTON_BACK_PIVOT_2_X, BUTTON_BACK_PIVOT_2_Y, BUTTON_START_BACK_RADIUS, 16);
	glColor4f(currentColor[0], currentColor[1], currentColor[2], currentColor[3]);
}

void drawLeftBumper() {
	float currentColor[4];
	glGetFloatv(GL_CURRENT_COLOR, currentColor);
	glColor4f(BUTTON_COLOR[0], BUTTON_COLOR[1], BUTTON_COLOR[2], GLOBAL_ALPHA_ELEMENTS);
	drawCircleSegment(BUMPER_LEFT_SEGMENT_X, BUMPER_LEFT_SEGMENT_Y, BUMPER_LEFT_SEGMENT_RADIUS, -BUMPER_LEFT_SEGMENT_A1, -BUMPER_LEFT_SEGMENT_A2, 16);
	drawRect(BUTTON_LEFT_BUMPER_X, BUTTON_LEFT_BUMPER_Y, BUMPER_LENGTH, BUMPER_HEIGHT);
	glColor4f(currentColor[0], currentColor[1], currentColor[2], currentColor[3]);
}

void drawRightBumper() {
	float currentColor[4];
	glGetFloatv(GL_CURRENT_COLOR, currentColor);
	glColor4f(BUTTON_COLOR[0], BUTTON_COLOR[1], BUTTON_COLOR[2], GLOBAL_ALPHA_ELEMENTS);
	drawCircleSegment(BUMPER_RIGHT_SEGMENT_X, BUMPER_RIGHT_SEGMENT_Y, BUMPER_RIGHT_SEGMENT_RADIUS, -BUMPER_RIGHT_SEGMENT_A1, -BUMPER_RIGHT_SEGMENT_A2, 16);
	drawRect(BUTTON_RIGHT_BUMPER_X, BUTTON_RIGHT_BUMPER_Y, BUMPER_LENGTH, BUMPER_HEIGHT);
	glColor4f(currentColor[0], currentColor[1], currentColor[2], currentColor[3]);
}

void drawLeftTrigger(GLFWgamepadstate& state) {
	float perc = (state.axes[GLFW_GAMEPAD_AXIS_LEFT_TRIGGER] + 1) / 2;
	float currentColor[4];
	glGetFloatv(GL_CURRENT_COLOR, currentColor);
	glColor4f(TRIGGER_COLOR[0], TRIGGER_COLOR[1], TRIGGER_COLOR[2], GLOBAL_ALPHA_ELEMENTS);
	drawRect(TRIGGER_LEFT_FRAME_X, TRIGGER_LEFT_FRAME_Y, TRIGGER_FRAME_LENGTH, TRIGGER_FRAME_HEIGHT * perc);
	glColor4f(currentColor[0], currentColor[1], currentColor[2], currentColor[3]);
}

void drawRightTrigger(GLFWgamepadstate& state) {
	float perc = (state.axes[GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER] + 1) / 2;
	float currentColor[4];
	glGetFloatv(GL_CURRENT_COLOR, currentColor);
	glColor4f(TRIGGER_COLOR[0], TRIGGER_COLOR[1], TRIGGER_COLOR[2], GLOBAL_ALPHA_ELEMENTS);
	drawRect(TRIGGER_RIGHT_FRAME_X, TRIGGER_RIGHT_FRAME_Y, TRIGGER_FRAME_LENGTH, TRIGGER_FRAME_HEIGHT * perc);
	glColor4f(currentColor[0], currentColor[1], currentColor[2], currentColor[3]);
}

void drawLeftStick(GLFWgamepadstate& state) {
	float currentColor[4];
	glGetFloatv(GL_CURRENT_COLOR, currentColor);
	glColor4f(STICK_COLOR[0], STICK_COLOR[1], STICK_COLOR[2], GLOBAL_ALPHA_ELEMENTS);
	float xCircle = state.axes[GLFW_GAMEPAD_AXIS_LEFT_X]
		* sqrt(1 - 0.5 * state.axes[GLFW_GAMEPAD_AXIS_LEFT_Y] * state.axes[GLFW_GAMEPAD_AXIS_LEFT_Y]);
	float yCircle = state.axes[GLFW_GAMEPAD_AXIS_LEFT_Y]
		* sqrt(1 - 0.5 * state.axes[GLFW_GAMEPAD_AXIS_LEFT_X] * state.axes[GLFW_GAMEPAD_AXIS_LEFT_X]);
	drawCircle(LEFT_STICK_X + xCircle * STICK_RADIUS,
		LEFT_STICK_Y + yCircle * STICK_RADIUS, STICK_POINT_RADIUS, 36);
	/*drawCircle(LEFT_STICK_X + state.axes[GLFW_GAMEPAD_AXIS_LEFT_X] * STICK_RADIUS,
		LEFT_STICK_Y + state.axes[GLFW_GAMEPAD_AXIS_LEFT_Y] * STICK_RADIUS, STICK_POINT_RADIUS, 36);*/
	glColor4f(currentColor[0], currentColor[1], currentColor[2], currentColor[3]);
}
void drawRightStick(GLFWgamepadstate& state) {
	float currentColor[4];
	glGetFloatv(GL_CURRENT_COLOR, currentColor);
	glColor4f(STICK_COLOR[0], STICK_COLOR[1], STICK_COLOR[2], GLOBAL_ALPHA_ELEMENTS);
	float xCircle = state.axes[GLFW_GAMEPAD_AXIS_RIGHT_X]
		* sqrt(1 - 0.5 * state.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y] * state.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y]);
	float yCircle = state.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y]
		* sqrt(1 - 0.5 * state.axes[GLFW_GAMEPAD_AXIS_RIGHT_X] * state.axes[GLFW_GAMEPAD_AXIS_RIGHT_X]);
	drawCircle(RIGHT_STICK_X + xCircle * STICK_RADIUS,
		RIGHT_STICK_Y + yCircle * STICK_RADIUS, STICK_POINT_RADIUS, 36);
	/*drawCircle(RIGHT_STICK_X + state.axes[GLFW_GAMEPAD_AXIS_RIGHT_X] * STICK_RADIUS,
		RIGHT_STICK_Y + state.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y] * STICK_RADIUS, STICK_POINT_RADIUS, 36);*/
	glColor4f(currentColor[0], currentColor[1], currentColor[2], currentColor[3]);
}
void drawLeftThumb() {
	float currentColor[4];
	glGetFloatv(GL_CURRENT_COLOR, currentColor);
	glColor4f(THUMB_COLOR[0], THUMB_COLOR[1], THUMB_COLOR[2], GLOBAL_ALPHA_ELEMENTS);
	drawCircle(LEFT_STICK_X, LEFT_STICK_Y, STICK_RADIUS, 36);
	glColor4f(currentColor[0], currentColor[1], currentColor[2], currentColor[3]);
}
void drawRightThumb() {
	float currentColor[4];
	glGetFloatv(GL_CURRENT_COLOR, currentColor);
	glColor4f(THUMB_COLOR[0], THUMB_COLOR[1], THUMB_COLOR[2], GLOBAL_ALPHA_ELEMENTS * 0.5f);
	drawCircle(RIGHT_STICK_X, RIGHT_STICK_Y, STICK_RADIUS, 36);
	glColor4f(currentColor[0], currentColor[1], currentColor[2], currentColor[3]);
}
#endif