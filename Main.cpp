#include <iostream>
#include <GLFW/glfw3.h>
#include <SOIL2.h>
#define PS_PROFILE
#include "Positioning constants.h"
#include "Drawing.h"

#define DEBUG_MODE 0

#define SIZE_KOEF 0.5

void drawAll(GLuint &gamepad_texture) {
	drawTexturedRect(-1, -1, 2, 2, gamepad_texture); // full window
	glPushMatrix();
	glScalef(1.f / CONTROLLER_WIDTH, 1.f / CONTROLLER_HEIGHT, 1);
	glColor3f(1, 0, 0);
	drawCircle(0, 0, 100, 100);
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
		"../pics/ps_gamepad_photoshoped.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT

	);
	// init framebuf
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glViewport(0, 0, width, height);
	glfwSwapInterval(1);

	glClearColor(0, 0, 0, 0); // transparent window

#if DEBUG_MODE
	const char* name = glfwGetGamepadName(GLFW_JOYSTICK_1);
	printf("%s", name); // XInput Gamepad (GLFW)
#endif

	bool check_axes = false;
	GLFWgamepadstate state;

	//main window loop
	while (!glfwWindowShouldClose(window)) {
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
		glfwPollEvents();
		if (glfwJoystickIsGamepad(GLFW_JOYSTICK_1)) {
			if (glfwGetGamepadState(GLFW_JOYSTICK_1, &state)) {
				if (state.buttons[GLFW_GAMEPAD_BUTTON_A]) std::cout << "a ";
				if (state.buttons[GLFW_GAMEPAD_BUTTON_B]) std::cout << "b ";
				if (state.buttons[GLFW_GAMEPAD_BUTTON_X]) std::cout << "x ";
				if (state.buttons[GLFW_GAMEPAD_BUTTON_Y]) std::cout << "y ";
				if (state.buttons[GLFW_GAMEPAD_BUTTON_LEFT_BUMPER]) std::cout << "lb ";
				if (state.buttons[GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER]) std::cout << "rb ";
				if (state.buttons[GLFW_GAMEPAD_BUTTON_BACK]) std::cout << "back ";
				if (state.buttons[GLFW_GAMEPAD_BUTTON_START]) std::cout << "start ";
				//if (state.buttons[GLFW_GAMEPAD_BUTTON_GUIDE]) std::cout << "guide "; // th?
				if (state.buttons[GLFW_GAMEPAD_BUTTON_LEFT_THUMB]) std::cout << "lt ";
				if (state.buttons[GLFW_GAMEPAD_BUTTON_RIGHT_THUMB]) std::cout << "rt ";
				if (state.buttons[GLFW_GAMEPAD_BUTTON_DPAD_UP]) std::cout << "dpu ";
				if (state.buttons[GLFW_GAMEPAD_BUTTON_DPAD_RIGHT]) std::cout << "dpr ";
				if (state.buttons[GLFW_GAMEPAD_BUTTON_DPAD_DOWN]) std::cout << "dpd ";
				if (state.buttons[GLFW_GAMEPAD_BUTTON_DPAD_LEFT]) std::cout << "dpl ";
				if (check_axes) {
					if (state.axes[GLFW_GAMEPAD_AXIS_LEFT_X]) std::cout << "lx ";
					if (state.axes[GLFW_GAMEPAD_AXIS_LEFT_Y]) std::cout << "ly ";
					if (state.axes[GLFW_GAMEPAD_AXIS_RIGHT_X]) std::cout << "rx ";
					if (state.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y]) std::cout << "ry ";
					if (state.axes[GLFW_GAMEPAD_AXIS_LEFT_TRIGGER]) std::cout << "ltr ";
					if (state.axes[GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER]) std::cout << "rtr ";
				}

			}
		}
		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window); // close window and context
	glfwTerminate(); // unload glfw
	return 0;
}