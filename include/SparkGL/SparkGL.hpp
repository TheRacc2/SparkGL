#ifndef SPARKGL_HEADER
#define SPARKGL_HEADER

#define _USE_MATH_DEFINES
#include <cmath>

#include <optional>
#include <functional>

#ifndef SPARKGL_NO_INCLUDE // flag to prevent GLFW from being included
	#include <GLFW/glfw3.h>
#endif

struct Vec2 {
	int x, y;

	Vec2() {
		x = 0;
		y = 0;
	}

	Vec2(int _x, int _y) {
		x = _x;
		y = _y;
	}

	/// <returns>The distance of this vector from the origin</returns>
	float len() {
		return sqrtf(static_cast<float>((x * x) + (y * y)));
	}

	/// <param name="other">Vector B, where this vector is A</param>
	/// <returns>The dot product of 'other' and this vector</returns>
	int dot(const Vec2 other) noexcept {
		return (x * other.x) + (y * other.y);
	}

	/// <param name="other">The endpoint vector</param>
	/// <returns>A directional vector from this to 'other'</returns>
	Vec2 vecTo(const Vec2 other) noexcept {
		return Vec2(other.x - x, other.y - y);
	}

#pragma region operators

	Vec2 operator -(const Vec2 other) { return Vec2(x - other.x, y - other.y); }
	Vec2 operator -(void) { return Vec2(-x, -y); }

	Vec2 operator +(const Vec2 other) { return Vec2(x + other.x, y + other.y); }

	Vec2 operator *(const Vec2 other) { return Vec2(x * other.x, y * other.x); }
	Vec2 operator *(const int value) { return Vec2(x * value, y * value); }

	Vec2 operator /(const Vec2 other) { return Vec2(x / other.x, y / other.y); }
	Vec2 operator /(const int value) { return Vec2(x / value, y / value); }

#pragma endregion
};

namespace SparkGL {
	inline GLFWwindow* window;

	#pragma region utility

	/// <summary>
	/// Attempts to initialize the SparkGL library
	/// </summary>
	/// <param name="size">The size of the window to be created</param>
	/// <param name="title">The window title</param>
	/// <param name="hintWindow">A lambda containing additional window hints</param>
	/// <returns>`true` on success or `false` on failure</returns>
	bool init(const Vec2 size, const char* title, std::function<void()> hintWindow = [&]{ });

	/// <summary>
	/// Call before drawing a frame
	/// </summary>
	void begin();

	/// <summary>
	/// Call after drawing a frame
	/// </summary>
	void end();

	#pragma endregion

	#pragma region wrapping

	/// <summary>
	/// Draws a simple rectangle
	/// </summary>
	/// <param name="pos">The top-left corner of the rectangle, in pixels</param>
	/// <param name="size">The width and height of the rectangle, in pixels</param>
	/// <param name="rounding">The rounding value, in pixels</param>
	/// <param name="color">Hexadecimal RGBA value (0xRRGGBBAA)</param>
	void rect(const Vec2 pos, const Vec2 size, const int rounding, const unsigned int color, const bool outline = false, const int thickness = 1);

	/// <summary>
	/// Draws a simple triangle
	/// </summary>
	/// <param name="a">The first point of the triangle, in pixels</param>
	/// <param name="b">The second point of the triangle, in pixels</param>
	/// <param name="c">The third point of the triangle, in pixels</param>
	/// <param name="color">Hexadecimal RGBA value (0xRRGGBBAA)</param>
	void triangle(const Vec2 a, const Vec2 b, const Vec2 c, const unsigned int color, const bool outline = false, const int thickness = 1);

	/// <summary>
	/// Draws a simple circular polygon
	/// </summary>
	/// <param name="center">The center/origin of the circle</param>
	/// <param name="radius">The radius of the circle, in pixels</param>
	/// <param name="points">How many points to use for the polygon</param>
	/// <param name="color">Hexadecimal RGBA value (0xRRGGBBAA)</param>
	void circle(const Vec2 center, const int radius, const int points, const unsigned int color, const bool outline = false, const int thickness = 1);

	/// <summary>
	/// Draws a simple line
	/// </summary>
	/// <param name="start">The beginning point of the line</param>
	/// <param name="end">The end point of the line</param>
	/// <param name="thickness">How thick the line is, in pixels</param>
	/// <param name="color">Hexadecimal RGBA value (0xRRGGBBAA)</param>
	void line(const Vec2 start, const Vec2 end, const int thickness, const unsigned int color);

	/// <summary>
	/// Draws a polygon from a list of vertices
	/// </summary>
	/// <param name="color">Hexadecimal RGBA value (0xRRGGBBAA)</param>
	/// <param name="args">A varags-style list of Vec2 points</param>
	void polygon(const unsigned int color, const Vec2 args...);

	#pragma endregion
}

#endif
