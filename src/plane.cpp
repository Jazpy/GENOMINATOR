#define GLM_ENABLE_EXPERIMENTAL

#include <plane.hpp>
#include <time.hpp>
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/geometric.hpp>
#include <iostream>

using glm::vec3;
using std::vector;

typedef vector<vec3>::iterator vec_iter;

// Planes consist of stitched-up patch primitives
Plane::Plane(float x_length, float z_length,
	size_t x_patches, size_t z_patches,
	const GLuint pos_index) :
	position_index(pos_index)
{
	// Each patch has 16 control points, reserve vector space
	control_points.reserve(16 * x_patches * z_patches);

	float x_patch_step = x_length / x_patches;
	float z_patch_step = z_length / z_patches;
	float x_step = x_patch_step / 3.0f;
	float z_step = z_patch_step / 3.0f;
	float x_lim = -x_length / 2.0f;
	float z_lim = -z_length / 2.0f;
	
	// First two loops walk over every patch, the innermost two
	// create control points for each patch. Innermost loops are
	// O(1) so this shouldn't be too bad.
	for(int p1 = 0; p1 != x_patches; ++p1)
	{
		for(int p2 = 0; p2 != z_patches; ++p2)
		{
			float x_corner = x_lim + (p1 * x_patch_step);
			float z_corner = z_lim + (p2 * z_patch_step);
			
			// Create control points for each patch
			for(int i = 0; i != 4; ++i)
			{
				for(int j = 0; j != 4; ++j)
				{
					vec3 new_point(
							x_corner + (i * x_step),
							0,
							z_corner + (j * z_step));
					control_points.push_back(new_point);
				}
			}
		}
	}

	// Total size in bytes for VBO
	total_size = stride * control_points.size();
}

Plane::~Plane()
{
	// Delete VAO
	glDeleteVertexArrays(1, &vao_id);

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
	glGenBuffers(1, &vertex_buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
	glBufferData(GL_ARRAY_BUFFER, total_size, &control_points[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(position_index);
	glVertexAttribPointer(position_index, 3, GL_FLOAT, GL_FALSE, stride, 0);

	// Render parameters	
	// glPatchParameteri(GL_PATCH_VERTICES, 16);
}

void Plane::update_VBO()
{
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
	glBufferSubData(GL_ARRAY_BUFFER, 0, total_size, &control_points[0]);
}

void Plane::render()
{
	// Bind VAO for this object and draw
	glBindVertexArray(vao_id);
	glDrawArrays(GL_POINTS, 0, control_points.size());
	//glDrawArrays(GL_PATCHES, 0, control_points.size());
}

void Plane::sine_wave()
{
	// Calculate delta time for smooth animation
	float delta_time = Time::get_delta();

	// Get displacement for this frame
	static float displacement;
	displacement += 1.5f * delta_time;

	for(vec_iter iter = control_points.begin(); iter != control_points.end(); ++iter)
	{
		iter->y = 3.5f * sin((iter->x + displacement) * 0.5f);
	}

	// Update mesh
	update_VBO();
}

void Plane::ripple()
{
	// Calculate delta time for smooth animation
	float delta_time = Time::get_delta();

	// Get displacement for this frame
	static float displacement;
	displacement += 1.5f * delta_time;

	for(vec_iter iter = control_points.begin(); iter != control_points.end(); ++iter)
	{
		float x_pow = pow((iter->x + 0), 2);
		float z_pow = pow((iter->z + 0), 2);

		iter->y = (4.0f * cos(sqrt((x_pow + z_pow) * 1.5f) + displacement)
			/ exp(((x_pow + z_pow) * 0.01f)));
	}

	// Update mesh
	update_VBO();
}
