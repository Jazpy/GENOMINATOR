#pragma once

#include <GL/glew.h>
#include <vector>

class Tree
{
	private:

	// OpenGL buffer ids
	GLuint vertex_buffer;
	GLuint color_buffer;

	// Vertex data
	std::vector<float> vertex_buffer_data;

	// Color data
	std::vector<float> color_buffer_data;

	// OpenGL VAO
	GLuint vao_id;

	// Count of all line segments in the tree
	int lines = 0;

	public:

	Tree(unsigned int iterations);
	~Tree();

	// Bind to the current VAO
	void BindToVAO();

	int get_lines() { return this->lines; }
};
