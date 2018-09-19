#pragma once

#include <GL/glew.h>
#include <vector>

class Plane
{
	private:
	const GLuint position_index;

	// OpenGL buffer ids
	GLuint vertex_buffer_id;
	GLuint vbo_index_id;

	// NURB plane's control points, hardcoded for now
	const int face_buffer[60] = {
		2, 1, 0,
		3, 2, 0,
		4, 3, 0,
		5, 4, 0,
		1, 5, 0,

		11, 6,  7,
		11, 7,  8,
		11, 8,  9,
		11, 9,  10,
		11, 10, 6,

		1, 2, 6,
		2, 3, 7,
		3, 4, 8,
		4, 5, 9,
		5, 1, 10,

		2,  7, 6,
		3,  8, 7,
		4,  9, 8,
		5, 10, 9,
		1, 6, 10 };
	const float vertex_buffer[36] = {
		0.000f,  0.000f,  1.000f,
		0.894f,  0.000f,  0.447f,
		0.276f,  0.851f,  0.447f,
		-0.724f,  0.526f,  0.447f,
		-0.724f, -0.526f,  0.447f,
		0.276f, -0.851f,  0.447f,
		0.724f,  0.526f, -0.447f,
		-0.276f,  0.851f, -0.447f,
		-0.894f,  0.000f, -0.447f,
		-0.276f, -0.851f, -0.447f,
		0.724f, -0.526f, -0.447f,
		0.000f,  0.000f, -1.000f };

	// OpenGL VAO
	GLuint vao_id;

	// Count of all line segments in the tree
	int lines = 0;

	// Used for VBO indexing
	int index_count;

	public:

	Plane(const GLuint pos_index);
	~Plane();

	// Bind vertex and color data
	void bind_buffer_data();
	// Bind to the current VAO
	void bind_to_vao();

	GLuint get_index_count() { return this->index_count; }
	int get_lines() { return this->lines; }
};
