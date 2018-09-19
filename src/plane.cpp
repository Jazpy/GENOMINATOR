#define GLM_ENABLE_EXPERIMENTAL

#include <stdlib.h>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/geometric.hpp>
#include <plane.hpp>

using glm::vec3;
using std::vector;

typedef vector<float>::iterator vec_iter;

// Construct plane with given characteristics
Plane::Plane(const GLuint pos_index) : position_index(pos_index)
{
	index_count = sizeof(face_buffer) / sizeof(face_buffer[0]);
}

Plane::~Plane()
{
	// Cleanup VBO
	glDeleteBuffers(1, &vertex_buffer_id);

	// Cleanup attributes
	glDisableVertexAttribArray(0);
}

void Plane::bind_buffer_data()
{
	glGenVertexArrays(1, &vao_id);
	glBindVertexArray(vao_id);

	// Bind vertex buffer data
	GLsizei stride = 3 * sizeof(float);
	glGenBuffers(1, &vertex_buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer), vertex_buffer, GL_STATIC_DRAW);
	glEnableVertexAttribArray(position_index);
	glVertexAttribPointer(position_index, 3, GL_FLOAT, GL_FALSE, stride, 0);

	// Create the VBO for indices:
	glGenBuffers(1, &vbo_index_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_index_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(face_buffer), face_buffer, GL_STATIC_DRAW);
}

void Plane::bind_to_vao()
{
	// Bind our VBOs
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
}
