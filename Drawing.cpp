#include "Drawing.h"
#include <GLFW/glfw3.h>
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