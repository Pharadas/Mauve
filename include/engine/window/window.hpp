#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>



#pragma once

#include <string>

class Window {
public:
	GLFWwindow* _window;
	VkSurfaceKHR _surface;

	void init_window(const char* window_name, int window_width, int window_height);
	void create_surface(VkInstance instance);
	void cleanup();

private:
	const char* _windowName;
	int _windowHeight;
	int _windowWidth;

};