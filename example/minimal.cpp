#include <GLFW/glfw3.h>
#include <SparkGL/SparkGL.hpp>

int main() {
	auto hints = [&] {
		// your hints here
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	};

	if (!SparkGL::init(Vec2(800, 800), "SparkGL Example", hints))
		return EXIT_FAILURE;

	while (!glfwWindowShouldClose(SparkGL::window)) {
		SparkGL::begin();

		SparkGL::circle(Vec2(400, 400), 100, 80, 0xFFFFFFFF);

		SparkGL::end();
	}

	return EXIT_SUCCESS;
}