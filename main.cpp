#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


const int WIDTH = 800;
const int HEIGHT = 800;

int main() {

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "game engine", NULL, NULL);
	
	if (window == NULL) {

		std::cout << "Failed to create window" << "/n";
		glfwTerminate();
		return -1;

	}

	glfwMakeContextCurrent(window);

	gladLoadGL();


	glViewport(0, 0, WIDTH, HEIGHT);

	while (!glfwWindowShouldClose(window)) {

		glfwPollEvents();

	}


	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;

}