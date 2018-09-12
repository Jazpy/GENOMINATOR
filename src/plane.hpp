#pragma once

#include <GL/glew.h>
#include <vector>

class Plane
{
	private:

	// OpenGL buffer ids
	GLuint vertex_buffer;
	GLuint color_buffer;

	// NURB plane's control points, hardcoded for now
	GLfloat control_points[4][4][3] =
	{
		{{-1.5, 1.0, -1.5}, {-0.5, 1.0, -1.5}, {0.5, 1.0, -1.5}, {1.5, 1.0, -1.5}}, 
		{{-1.5, 1.0, -0.5}, {-0.5, 2.0, -0.5}, {0.5, 2.0, -0.5}, {1.5, 1.0, -0.5}}, 
		{{-1.5, 1.0,  0.5}, {-0.5, 2.0,  0.5}, {0.5, 2.0,  0.5}, {1.5, 1.0,  0.5}}, 
		{{-1.5, 1.0,  1.5}, {-0.5, 1.0,  1.5}, {0.5, 1.0,  1.5}, {1.5, 1.0,  1.5}}
	};

	// Vertex and color data
	std::vector<float> vertex_buffer_data;
	std::vector<float> color_buffer_data;

	// OpenGL VAO
	GLuint vao_id;

	// Count of all line segments in the tree
	int lines = 0;

	public:

	Plane(unsigned int iterations);
	~Plane();

	// Bind vertex and color data
	void bind_buffer_data();
	// Bind to the current VAO
	void bind_to_vao();

	int get_lines() { return this->lines; }
};
