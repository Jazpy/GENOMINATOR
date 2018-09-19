#pragma once

#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <vector>

class Plane
{
	private:
	const GLuint position_index;

	// OpenGL VAO
	GLuint vao_id;

	// OpenGL buffer ids
	GLuint vertex_buffer_id;

	// Bezier plane's control points
	int control_count;
	int control_per_patch;
	std::vector<glm::vec3> control_points;

	public:

	Plane(float x_length, float z_length, const GLuint pos_index);
	~Plane();

	// Bind vertex and color data
	void bind_buffer_data();

	// Apply a function to all control points
	void sine_wave();

	// Return number of control points
	int get_control_count() { return control_count; }
	int get_control_per_patch() { return control_per_patch; }
};
