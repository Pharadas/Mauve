#include <engine/window/window.hpp>

#include <stdexcept>

void Window::init_window(const char* window_name, int window_width, int window_height) {
	const char* _windowName;
	int _windowHeight;
	int _windowWidth;

	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	_window = glfwCreateWindow(window_width, window_height, window_name, nullptr, nullptr);
}

void Window::create_surface(VkInstance instance) {
	if (glfwCreateWindowSurface(instance, _window, nullptr, &_surface) != VK_SUCCESS) {
        throw std::runtime_error("failed to create window surface!");
    }
}

void Window::cleanup() {
	glfwDestroyWindow(_window);

	glfwTerminate();
}
