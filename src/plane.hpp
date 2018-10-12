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
	std::vector<glm::vec3> control_points;

	// Variables used for the VBO
	const GLsizei stride = 3 * sizeof(float);
	GLsizei total_size;

	// FUNCTIONS

	// Update mesh in VBO
	void update_VBO();

	public:

	Plane(float x_length, float z_length,
		size_t x_patches, size_t z_patches,
		const GLuint pos_index);
	~Plane();

	// Bind vertex and color data
	void bind_buffer_data();

	// Bind VAO and render
	void render();

	// Apply a function to all control points
	void sine_wave();
	void ripple();
};
