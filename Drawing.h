#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <GLFW/glfw3.h>

extern float GLOBAL_ALPHA;
extern float GLOBAL_ALPHA_ELEMENTS;
extern float GLOBAL_BRIGHTNESS_ELEMENTS;
extern float BUTTON_COLOR[4];
extern float STICK_COLOR[4];
extern float THUMB_COLOR[4];
extern float TRIGGER_COLOR[4];

void updateColors();

void drawCircle(float x, float y, float radius, int verts);
void drawCircleSector(float x, float y, float radius, float a1, float a2,int verts);
void drawCircleSegment(float x, float y, float radius, float a1, float a2, int verts);
void drawTexturedRect(float x, float y, float w, float h, GLuint texture);
void drawRect(float x, float y, float w, float h);
void drawButtonPressed(float x, float y, float radius);

void drawLeftDPAD();
void drawRightDPAD();
void drawTopDPAD();
void drawBottomDPAD();

void drawStart();
void drawBack();

void drawLeftBumper();
void drawRightBumper();

void drawLeftTrigger(GLFWgamepadstate& state);
void drawRightTrigger(GLFWgamepadstate& state);

void drawLeftStick(GLFWgamepadstate& state);
void drawRightStick(GLFWgamepadstate& state);
void drawLeftThumb();
void drawRightThumb();