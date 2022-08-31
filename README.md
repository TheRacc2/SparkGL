# SparkGL
 A simple OpenGL/GLFW wrapper for your projects.
 
 The **Spark** to get things rolling!

# Including
SparkGL was intended to be used as a submodule. It can be added as `git submodule add https://github.com/TheRacc2/SparkGL`

From there, simply add `SparkGL/include` as an include directory in your project configuration

You should now be able to write `#include <SparkGL/SparkGL.hpp>`

# Configuration
SparkGL uses GLFW and OpenGL. On windows, link against both `OpenGL32.lib` and `glfw3.lib`

The static GLFW library can be used. Read more about this [here.](https://www.glfw.org/docs/3.3/build_guide.html#build_link)

# Examples
SparkGL was designed with ease-of-use and code readability in mind. the [example projects](https://github.com/TheRacc2/SparkGL/tree/main/example)
showcase how easy it is to setup SparkGL out-of-the-box.

The most minimal example can be found [here.](https://github.com/TheRacc2/SparkGL/tree/main/example/minimal.cpp)

# Issues / Contributions
The code is written by myself and myself alone.
I have not taken a trigonometry or geometry class, so the algorithm used to draw circles and other polygons is more than likely very outdated.
If you have a better solution that works, please feel free to make a [Pull Request.](https://github.com/TheRacc2/SparkGL/pulls)

Issues can be reported on the [Issues page.](https://github.com/TheRacc2/SparkGL/issues)