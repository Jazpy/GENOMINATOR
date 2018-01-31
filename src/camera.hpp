#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

class Camera
{
	private:

	// Handle for "MVP" uniform
	GLuint matrix_id;

	// Camera matrices
	glm::mat4 projection;
	glm::mat4 view;
	glm::mat4 model;

	// Model View Projection
	glm::mat4 MVP;

	public:

	Camera(GLuint program_id, float fov, float aspect_ratio,
		float min_distance, float max_distance);

	// Get MVP transformation
	GLfloat *get_transformation();

	// Get handle
	GLint get_handle();
};
