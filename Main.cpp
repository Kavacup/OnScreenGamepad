#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <windows.h>
#include <GLFW/glfw3.h>
#include <SOIL2.h>

#define PS_PROFILE
#include "Positioning constants.h"
#include "Drawing.h"

void glfwSetWindowCenter(GLFWwindow* window) {
	// Get window position and size
	int window_x, window_y;
	glfwGetWindowPos(window, &window_x, &window_y);

	int window_width, window_height;
	glfwGetWindowSize(window, &window_width, &window_height);

	// Halve the window size and use it to adjust the window position to the center of the window
	window_width *= 0.5;
	window_height *= 0.5;

	window_x += window_width;
	window_y += window_height;

	// Get the list of monitors
	int monitors_length;
	GLFWmonitor** monitors = glfwGetMonitors(&monitors_length);

	if (monitors == NULL) {
		// Got no monitors back
		return;
	}

	// Figure out which monitor the window is in
	GLFWmonitor* owner = NULL;
	int owner_x, owner_y, owner_width, owner_height;

	for (int i = 0; i < monitors_length; i++) {
		// Get the monitor position
		int monitor_x, monitor_y;
		glfwGetMonitorPos(monitors[i], &monitor_x, &monitor_y);

		// Get the monitor size from its video mode
		int monitor_width, monitor_height;
		GLFWvidmode* monitor_vidmode = (GLFWvidmode*)glfwGetVideoMode(monitors[i]);

		if (monitor_vidmode == NULL) {
			// Video mode is required for width and height, so skip this monitor
			continue;

		}
		else {
			monitor_width = monitor_vidmode->width;
			monitor_height = monitor_vidmode->height;
		}

		// Set the owner to this monitor if the center of the window is within its bounding box
		if ((window_x > monitor_x && window_x < (monitor_x + monitor_width)) && (window_y > monitor_y && window_y < (monitor_y + monitor_height))) {
			owner = monitors[i];

			owner_x = monitor_x;
			owner_y = monitor_y;

			owner_width = monitor_width;
			owner_height = monitor_height;
		}
	}

	if (owner != NULL) {
		// Set the window position to the center of the owner monitor
		glfwSetWindowPos(window, owner_x + (owner_width * 0.5) - window_width, owner_y + (owner_height * 0.5) - window_height);
	}
}

float SIZE_KOEF = 0.5f;

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

bool showSettings = false;
double settingsX = 0;
double settingsY = 0;

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
	if (!showSettings) {
		glfwGetCursorPos(window, &settingsX, &settingsY);
	}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && showSettings) { // ignore dragging
		return;
	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS && !showSettings) {
		showSettings = true;
		return;
	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS && showSettings) {
		showSettings = false;
		return;
	}
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

void showSettingsWindow(GLFWwindow* window) {
	ImGui::Begin("Settings", &showSettings, ImGuiWindowFlags_MenuBar);
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Close", "RMB")) { showSettings = false; }
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}
	ImGui::PushItemWidth(0.5f * ImGui::GetWindowWidth());
	ImGui::SliderFloat("Size", &SIZE_KOEF, 0.3f, 1.0f);
	if (ImGui::Button("Apply size")) {
		glfwSetWindowSize(window, (float)CONTROLLER_WIDTH * SIZE_KOEF, (float)CONTROLLER_HEIGHT * SIZE_KOEF);
		//ImGui::SetWindowSize(ImVec2((float)CONTROLLER_WIDTH * 0.3f * 0.5f, (float)CONTROLLER_HEIGHT * 0.3f * 0.5f));
	}
	ImGui::SliderFloat("Controller opacity", &GLOBAL_ALPHA, 0.4f, 0.9f);
	if(ImGui::SliderFloat("Elements opacity", &GLOBAL_BRIGHTNESS_ELEMENTS, 0.4f, 0.9f))
		updateColors();
	ImGui::PopItemWidth();
	if (ImGui::Button("Exit app")) glfwSetWindowShouldClose(window, GL_TRUE);
	ImGui::End();
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow) {
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
	glfwSetWindowCenter(window);

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
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;// Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;// Enable Gamepad Controls
	ImGui::StyleColorsDark();
	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);// Second param install_callback=true will install GLFW callbacks and chain to existing ones.
	ImGui_ImplOpenGL3_Init();

#if DEBUG_MODE
	const char* name = glfwGetGamepadName(GLFW_JOYSTICK_1);
	printf("%s", name); // XInput Gamepad (GLFW)
#endif
	 
	//main window loop
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		
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
		if (showSettings) {
			ImGui::SetNextWindowPos(ImVec2(0, 0));
			ImGui::SetNextWindowSize(ImVec2((float)CONTROLLER_WIDTH * SIZE_KOEF * 0.5f, (float)CONTROLLER_HEIGHT * SIZE_KOEF * 0.5f), ImGuiCond_Appearing);
			showSettingsWindow(window);
		}
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
		glViewport(0, 0, windowWidth, windowHeight);
		glfwSwapBuffers(window);
	}
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(window); // close window and context
	glfwTerminate(); // unload glfw
	return 0;
}