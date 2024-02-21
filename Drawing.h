#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

void drawCircle(float x, float y, float radius, int verts);
void drawTexturedRect(float x, float y, float w, float h, GLuint texture);
void drawButtonPressed(float x, float y, float radius);