#include "Drawing.h"
#include <GLFW/glfw3.h>
#define PS_PROFILE
#include "Positioning constants.h"
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

void drawTexturedRect(float x, float y, float w, float h, GLuint texture) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_FALSE);
	glDisable(GL_DEPTH_TEST);
	glBegin(GL_QUADS);
	glColor3f(255, 255, 255);
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
	glColor4f(BUTTON_COLOR, alpha);
	drawCircle(x, y, radius, 60);
	glColor4f(currentColor[0], currentColor[1], currentColor[2], currentColor[3]);
}
#ifdef PS_PROFILE
void drawLeftDPAD() {
	float currentColor[4];
	glGetFloatv(GL_CURRENT_COLOR, currentColor);
	glColor4f(BUTTON_COLOR, alpha);
	drawRect(DPAD_LEFT_LEFT_TOP_ANGLE_X, DPAD_LEFT_LEFT_TOP_ANGLE_Y, DPAD_LENGTH, DPAD_HEIGHT);
	glColor4f(currentColor[0], currentColor[1], currentColor[2], currentColor[3]);
}
void drawRightDPAD() {
	float currentColor[4];
	glGetFloatv(GL_CURRENT_COLOR, currentColor);
	glColor4f(BUTTON_COLOR, alpha);
	drawRect(DPAD_RIGHT_RIGHT_TOP_ANGLE_X, DPAD_RIGHT_RIGHT_TOP_ANGLE_Y, -DPAD_LENGTH, DPAD_HEIGHT);
	glColor4f(currentColor[0], currentColor[1], currentColor[2], currentColor[3]);
}
void drawTopDPAD() {
	float currentColor[4];
	glGetFloatv(GL_CURRENT_COLOR, currentColor);
	glColor4f(BUTTON_COLOR, alpha);
	drawRect(DPAD_TOP_LEFT_TOP_ANGLE_X, DPAD_TOP_LEFT_TOP_ANGLE_Y, DPAD_HEIGHT, DPAD_LENGTH);
	glColor4f(currentColor[0], currentColor[1], currentColor[2], currentColor[3]);
}
void drawBottomDPAD() {
	float currentColor[4];
	glGetFloatv(GL_CURRENT_COLOR, currentColor);
	glColor4f(BUTTON_COLOR, alpha);
	drawRect(DPAD_BOTTOM_LEFT_BOTTOM_ANGLE_X, DPAD_BOTTOM_LEFT_BOTTOM_ANGLE_Y, DPAD_HEIGHT, -DPAD_LENGTH);
	glColor4f(currentColor[0], currentColor[1], currentColor[2], currentColor[3]);
}
void drawStart() {

}
void drawBack() {

}

void drawLeftStick(GLFWgamepadstate& state) {
	float currentColor[4];
	glGetFloatv(GL_CURRENT_COLOR, currentColor);
	glColor4f(STICK_COLOR, alpha);
	drawCircle(LEFT_STICK_X + state.axes[GLFW_GAMEPAD_AXIS_LEFT_X] * STICK_RADIUS,
		LEFT_STICK_Y + state.axes[GLFW_GAMEPAD_AXIS_LEFT_Y] * STICK_RADIUS, STICK_POINT_RADIUS, 36);
	glColor4f(currentColor[0], currentColor[1], currentColor[2], currentColor[3]);
}
void drawRightStick(GLFWgamepadstate& state) {
	float currentColor[4];
	glGetFloatv(GL_CURRENT_COLOR, currentColor);
	glColor4f(STICK_COLOR, alpha);
	drawCircle(RIGHT_STICK_X + state.axes[GLFW_GAMEPAD_AXIS_RIGHT_X] * STICK_RADIUS,
		RIGHT_STICK_Y + state.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y] * STICK_RADIUS, STICK_POINT_RADIUS, 36);
	glColor4f(currentColor[0], currentColor[1], currentColor[2], currentColor[3]);
}
void drawLeftThumb() {
	float currentColor[4];
	glGetFloatv(GL_CURRENT_COLOR, currentColor);
	glColor4f(THUMB_COLOR, alpha);
	drawCircle(LEFT_STICK_X, LEFT_STICK_Y, STICK_RADIUS, 36);
	glColor4f(currentColor[0], currentColor[1], currentColor[2], currentColor[3]);
}
void drawRightThumb() {
	float currentColor[4];
	glGetFloatv(GL_CURRENT_COLOR, currentColor);
	glColor4f(THUMB_COLOR, alpha * 0.5f);
	drawCircle(RIGHT_STICK_X, RIGHT_STICK_Y, STICK_RADIUS, 36);
	glColor4f(currentColor[0], currentColor[1], currentColor[2], currentColor[3]);
}
#endif