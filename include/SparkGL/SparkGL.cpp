#include "SparkGL.hpp"



void glColorui(unsigned int col) {
	int r, g, b, a;
	r = col >> 24 & 0xFF;
	g = col >> 16 & 0xFF;
	b = col >> 8 & 0xFF;
	a = col & 0xFF;

	glColor4ub(r, g, b, a);
}

namespace SparkGL {
	#pragma region utility

	bool init(const Vec2 size, const char* title, std::function<void()> hintWindow) {
		if (glfwInit() != GL_TRUE)
			return false;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

		hintWindow();

		window = glfwCreateWindow(size.x, size.y, title, nullptr, nullptr);

		if (!window)
			return false;

		glfwMakeContextCurrent(window);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0.f, size.x, size.y, 0.f, 0.f, 1.f);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		return true;
	}

	void begin() {
		Vec2 size;
		glfwGetFramebufferSize(window, &size.x, &size.y);
		glViewport(0, 0, size.x, size.y);

		glClearColor(0.f, 0.f, 0.f, 0.f); // Set background color to black and opaque
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void end() {
		glFlush();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	#pragma endregion

	#pragma region wrapping

	void rect(const Vec2 pos, const Vec2 size, int rounding, const unsigned int color, const bool outline, const int thickness) {
		if (rounding == 0) {
			auto begin = [&]() {
				if (outline)
					glLineWidth(static_cast<GLfloat>(thickness)), glBegin(GL_LINE_LOOP);
				else
					glBegin(GL_QUADS);
			};

			begin();
			{
				glColorui(color);

				glVertex2i(pos.x, pos.y); // TL
				glVertex2i(pos.x + size.x, pos.y); // TR
				glVertex2i(pos.x + size.x, pos.y + size.y); // BR
				glVertex2i(pos.x, pos.y + size.y); // BL
			}
			glEnd();
		}
		else {
			const int doubleRounding = rounding * 2;
			if (outline) {

				glLineWidth(static_cast<GLfloat>(thickness));

				glBegin(GL_LINE);
				{
					
				}
				glEnd();
			}
			else {
				rect(Vec2(pos.x, pos.y + rounding), Vec2(size.x, size.y - doubleRounding), 0, color); // middle
				rect(Vec2(pos.x + rounding, pos.y), Vec2(size.x - doubleRounding, rounding), 0, color); // top
				rect(Vec2(pos.x + rounding, pos.y + size.y - rounding), Vec2(size.x - doubleRounding, rounding), 0, color); // bottom
			}

			constexpr float TO_RAD = static_cast<float>(M_PI) / 180.f;
				
			Vec2 corners[4] = {
				Vec2(pos.x + rounding, pos.y + rounding), // top left
				Vec2(pos.x + size.x - rounding, pos.y + rounding), // top right
				Vec2(pos.x + size.x - rounding, pos.y + size.y - rounding), // bottom right
				Vec2(pos.x + rounding, pos.y + size.y - rounding) // bottom left
			};

			for (int i = 0; i < 4; i++) {
				auto begin = [&]() {
					if (outline)
						glLineWidth(static_cast<GLfloat>(thickness)), glBegin(GL_LINE_STRIP);
					else
						glBegin(GL_TRIANGLE_FAN);
				};

				begin();
				{
					glColorui(color);

					if (!outline)
						glVertex2i(corners[i].x, corners[i].y); // add the corner

					for (float j = 0; j <= 90.f; j += (90.f / rounding)) {
						float angle = j + (90.f * i);

						float cos = cosf(angle * TO_RAD) * rounding;
						float sin = sinf(angle * TO_RAD) * rounding;
						
						// we have to use glVertex2f instead of glVertex2i due to floating-point imprecision 
						glVertex2f(corners[i].x - cos, corners[i].y - sin);
					}
				}
				glEnd();
			}

			// debug
			/*glBegin(GL_QUADS);
				glColor4f(1.f, 0.f, 0.f, 0.5f);
				glVertex2i(corners[0].x, corners[0].y);
				glVertex2i(corners[1].x, corners[1].y);
				glVertex2i(corners[2].x, corners[2].y);
				glVertex2i(corners[3].x, corners[3].y);
			glEnd();*/
		}
	}

	void triangle(const Vec2 a, const Vec2 b, const Vec2 c, const unsigned int color, const bool outline, const int thickness) {
		auto begin = [&]() {
			if (outline)
				glLineWidth(static_cast<GLfloat>(thickness)), glBegin(GL_LINES);
			else
				glBegin(GL_TRIANGLES);
		};

		begin();
		{
			glColorui(color);

			glVertex2i(a.x, a.y);
			glVertex2i(b.x, b.y);
			glVertex2i(c.x, c.y);
		}
		glEnd();
	}

	void circle(const Vec2 center, const int radius, const int points, const unsigned int color, const bool outline, const int thickness) {
		auto begin = [&]() {
			if (outline)
				glBegin(GL_LINE_STRIP), glLineWidth(static_cast<GLfloat>(thickness));
			else
				glBegin(GL_TRIANGLE_FAN);
		};

		begin();
		{
			glColorui(color);

			constexpr float TO_RAD = static_cast<float>(M_PI) / 180.f;

			for (float i = 0; i <= 360.f; i += (360.f / points)) {
				float cos = cosf(i * TO_RAD) * radius;
				float sin = sinf(i * TO_RAD) * radius;

				glVertex2f(center.x - cos, center.y - sin);
			}
		}
		glEnd();
	}

	void line(const Vec2 start, const Vec2 end, const int thickness, const unsigned int color) {
		glLineWidth(static_cast<GLfloat>(thickness));

		glBegin(GL_LINES);
		{
			glColorui(color);

			glVertex2i(start.x, start.y);
			glVertex2i(end.x, end.y);
		}
		glEnd();
	}

	#pragma endregion
}