#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <GLFW/glfw3.h>

#define GLOBAL_ALPHA 0.5
#define GLOBAL_ALPHA_ELEMENTS GLOBAL_ALPHA
#define GLOBAL_BRIGHTNESS_ELEMENTS GLOBAL_ALPHA
#define BUTTON_COLOR 1 * GLOBAL_BRIGHTNESS_ELEMENTS, 0 * GLOBAL_BRIGHTNESS_ELEMENTS, 0 * GLOBAL_BRIGHTNESS_ELEMENTS
#define STICK_COLOR 0 * GLOBAL_BRIGHTNESS_ELEMENTS, 1 * GLOBAL_BRIGHTNESS_ELEMENTS, 0 * GLOBAL_BRIGHTNESS_ELEMENTS
#define THUMB_COLOR 1 * GLOBAL_BRIGHTNESS_ELEMENTS, 0 * GLOBAL_BRIGHTNESS_ELEMENTS, 0 * GLOBAL_BRIGHTNESS_ELEMENTS
#define TRIGGER_COLOR 0.8f * GLOBAL_BRIGHTNESS_ELEMENTS, 0 * GLOBAL_BRIGHTNESS_ELEMENTS, 0.8f * GLOBAL_BRIGHTNESS_ELEMENTS

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