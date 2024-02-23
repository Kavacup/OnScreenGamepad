#include <iostream>
#include <GLFW/glfw3.h>
#include <SOIL2.h>

#define PS_PROFILE
#include "Positioning constants.h"
#include "Drawing.h"

#define DEBUG_MODE 0

#define SIZE_KOEF 0.5

bool check_axes = true;
GLFWgamepadstate state;
int windowWidth;
int windowHeight;

void drawAll(GLuint &gamepad_texture) {
	glPushMatrix();
	drawTexturedRect(-1, -1, 2, 2, gamepad_texture); // full window
	glTranslatef(-1, 1, 0);
	glScalef(2.f / CONTROLLER_WIDTH, - 2.f / CONTROLLER_HEIGHT, 1);
	if (glfwJoystickIsGamepad(GLFW_JOYSTICK_1)) {
		if (glfwGetGamepadState(GLFW_JOYSTICK_1, &state)) {
			if (state.buttons[GLFW_GAMEPAD_BUTTON_A]) drawButtonPressed(BUTTON_A_X, BUTTON_A_Y, BUTTON_RADIUS);
			if (state.buttons[GLFW_GAMEPAD_BUTTON_B]) drawButtonPressed(BUTTON_B_X, BUTTON_B_Y, BUTTON_RADIUS);
			if (state.buttons[GLFW_GAMEPAD_BUTTON_X]) drawButtonPressed(BUTTON_X_X, BUTTON_X_Y, BUTTON_RADIUS);
			if (state.buttons[GLFW_GAMEPAD_BUTTON_Y]) drawButtonPressed(BUTTON_Y_X, BUTTON_Y_Y, BUTTON_RADIUS);
			if (state.buttons[GLFW_GAMEPAD_BUTTON_LEFT_BUMPER]) drawLeftBumper();
			if (state.buttons[GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER]) drawRightBumper();
			if (state.buttons[GLFW_GAMEPAD_BUTTON_BACK]) drawBack();
			if (state.buttons[GLFW_GAMEPAD_BUTTON_START]) drawStart();
			if (state.buttons[GLFW_GAMEPAD_BUTTON_DPAD_UP]) drawTopDPAD();
			if (state.buttons[GLFW_GAMEPAD_BUTTON_DPAD_RIGHT]) drawRightDPAD();
			if (state.buttons[GLFW_GAMEPAD_BUTTON_DPAD_DOWN]) drawBottomDPAD();
			if (state.buttons[GLFW_GAMEPAD_BUTTON_DPAD_LEFT]) drawLeftDPAD();
			drawLeftStick(state);
			drawRightStick(state);
			if (state.buttons[GLFW_GAMEPAD_BUTTON_LEFT_THUMB]) drawLeftThumb();
			if (state.buttons[GLFW_GAMEPAD_BUTTON_RIGHT_THUMB]) drawRightThumb();
			drawLeftTrigger(state);
			drawRightTrigger(state);

		}
	}
	glPopMatrix();
	
}

int dragging_cursor_x;
int dragging_cursor_y;
int offset_cpx;
int offset_cpy;
int window_pos_x;
int window_pos_y;
bool dragging_window;

void cursor_position_callback(GLFWwindow* window, double x, double y) {
	if (dragging_window == true) {
		offset_cpx = x - dragging_cursor_x;
		offset_cpy = y - dragging_cursor_y;
	}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		dragging_window = true;
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		dragging_cursor_x = floor(x);
		dragging_cursor_y = floor(y);
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		dragging_window = false;
		dragging_cursor_x = 0;
		dragging_cursor_y = 0;
	}
}

int main() {

	if (!glfwInit()) {
		return 1; // glfw load error
	}
	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
	glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);

	GLFWwindow* window = glfwCreateWindow((float)CONTROLLER_WIDTH * SIZE_KOEF, (float)CONTROLLER_HEIGHT * SIZE_KOEF,
		"why do you see it" , NULL, NULL);
	if (!window) {
		#if DEBUG_MODE
			std::cout << "PIZDEC\n";// Window or OpenGL context creation failed
		#endif
		glfwTerminate();
		return 2;
	}
	glfwMakeContextCurrent(window);

	GLuint texture = SOIL_load_OGL_texture // gamepad texture
	(
		"../pics/ps_gamepad_photoshoped2.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT

	);
	// init framebuf
	glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glViewport(0, 0, windowWidth, windowHeight);
	glfwSwapInterval(1);

	glClearColor(0, 0, 0, GLOBAL_ALPHA * 0.1); // transparent window

#if DEBUG_MODE
	const char* name = glfwGetGamepadName(GLFW_JOYSTICK_1);
	printf("%s", name); // XInput Gamepad (GLFW)
#endif

	//main window loop
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		if (dragging_window == true) {
			glfwGetWindowPos(window, &window_pos_x, &window_pos_y);
			glfwSetWindowPos(window, window_pos_x + offset_cpx, window_pos_y + offset_cpy);
			offset_cpx = 0;
			offset_cpy = 0;
			dragging_cursor_x += offset_cpx;
			dragging_cursor_y += offset_cpy;
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		drawAll(texture);
		glfwSwapBuffers(window);
	}
	glfwDestroyWindow(window); // close window and context
	glfwTerminate(); // unload glfw
	return 0;
}