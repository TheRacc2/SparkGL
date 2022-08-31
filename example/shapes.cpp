#include <Windows.h>
#include <iostream>
#include <exception>

#include <GLFW/glfw3.h>
#include <SparkGL/SparkGL.hpp>

/// @brief Testing example, draws a bunch of different shapes
int main() {
	auto hints = [&]() {
		//glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	};

	if (!SparkGL::init(Vec2(1600, 900), "SparkGL Shapes", hints)) {
		MessageBoxA(nullptr, "Failed to inititalize SparkGL!", "SparkGL | Error", MB_OK);
		exit(EXIT_FAILURE);
	}

	while (!glfwWindowShouldClose(SparkGL::window)) {
		SparkGL::begin();

		// normal rectangle
		SparkGL::rect(Vec2(500, 100), Vec2(300, 150), 0, 0xFF000080);

		// rectangle with rounded corners
		SparkGL::rect(Vec2(100, 100), Vec2(300, 150), 30, 0xFFFFFFFF);
		
		SparkGL::triangle(Vec2(300, 300), Vec2(500, 400), Vec2(300, 500), 0x0090FF90);

		// octogon
		SparkGL::circle(Vec2(150, 600), 60, 8, 0x7000FFFF);
		
		// circle
		SparkGL::circle(Vec2(600, 600), 60, 30, 0x00FF50FF);

		// thick line
		SparkGL::line(Vec2(1000, 400), Vec2(800, 600), 4, 0xFFFF00FF);

		SparkGL::end();
	}
}