#define GLM_ENABLE_EXPERIMENTAL

#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/geometric.hpp>
#include <plane.hpp>
#include <iostream>

using glm::vec3;
using std::vector;

typedef vector<vec3>::iterator vec_iter;

// Construct plane with given characteristics
Plane::Plane(float x_length, float z_length, const GLuint pos_index) : position_index(pos_index)
{
	control_per_patch = 16;

	float x_step = x_length / 3.0f;
	float z_step = z_length / 3.0f;
	float x_lim = -x_length / 2.0f;
	float z_lim = -z_length / 2.0f;

	for(int i = 0; i != 4; ++i)
	{
		for(int j = 0; j != 4; ++j)
		{
			vec3 new_point(x_lim + (i * x_step), 0, z_lim + (j * z_step));
			control_points.push_back(new_point);
		}
	}

	control_count = control_points.size();
}

Plane::~Plane()
{
	// Cleanup VBO
	glDeleteBuffers(1, &vertex_buffer_id);

	// Cleanup attributes
	glDisableVertexAttribArray(position_index);
}

void Plane::bind_buffer_data()
{
	glGenVertexArrays(1, &vao_id);
	glBindVertexArray(vao_id);

	// Bind vertex buffer data
	GLsizei stride = 3 * sizeof(float);
	GLsizei total_size = stride * control_count;

	glGenBuffers(1, &vertex_buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
	glBufferData(GL_ARRAY_BUFFER, total_size, &control_points[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(position_index);
	glVertexAttribPointer(position_index, 3, GL_FLOAT, GL_FALSE, stride, 0);
}

void Plane::sine_wave()
{
	for(vec_iter iter = control_points.begin(); iter != control_points.end(); ++iter)
	{
		iter->y = abs(8.0f * sin(iter->x));
	}
}
