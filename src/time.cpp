#include <time.hpp>
#include <GLFW/glfw3.h>

float Time::last_time = glfwGetTime();
float Time::delta;

void Time::update()
{
	float curr_time = glfwGetTime();
	delta = curr_time - last_time;
	last_time = curr_time;
}

float Time::get_delta()
{
	return delta;
}
