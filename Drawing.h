#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <GLFW/glfw3.h>

#define BUTTON_COLOR 1, 0, 0
#define STICK_COLOR 0, 1, 0
#define THUMB_COLOR 1, 0, 0
#define TRIGGER_COLOR
#define alpha 0.2

void drawCircle(float x, float y, float radius, int verts);
void drawTexturedRect(float x, float y, float w, float h, GLuint texture);
void drawRect(float x, float y, float w, float h);
void drawButtonPressed(float x, float y, float radius);

void drawLeftDPAD();
void drawRightDPAD();
void drawTopDPAD();
void drawBottomDPAD();

void drawStart();
void drawBack();

void drawLeftStick(GLFWgamepadstate& state);
void drawRightStick(GLFWgamepadstate& state);
void drawLeftThumb();
void drawRightThumb();