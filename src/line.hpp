#pragma once

#include <GL/glew.h>
#include <vector>

class Line
{
	private:

	// OpenGL buffer ids
	GLuint vertex_buffer;
	GLuint color_buffer;

	// Vertex data
	std::vector<float> vertex_buffer_data;
	std::vector<float> color_buffer_data;

	// OpenGL VAO
	GLuint vao_id;

	public:

	Line();
	~Line();

	// Bind to the current VAO
	void BindToVAO();
};
