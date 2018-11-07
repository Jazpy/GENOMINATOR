#define GLM_ENABLE_EXPERIMENTAL

#include <tower.hpp>
#include <time.hpp>
#include <math.h>
#include <stdlib.h>
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/geometric.hpp>
#include <iostream>

using glm::vec3;
using std::vector;
using std::shared_ptr;

// Inner class that handles color, rotation, and diameter of each ring
class Tower::Ring
{
	private:
	const int points;
	const int offset;
	const float radius;
	const float height;

	shared_ptr<vector<vec3>> ring_data;
	shared_ptr<vector<vec3>> color_data;

	public:

	// This constructor will actually fill in its share at shared_vec
	Ring(int points, int offset, float diameter,
		float height, const shared_ptr<vector<vec3>> shared_vec,
		const shared_ptr<vector<vec3>> shared_col) :
		points(points), offset(offset), radius(diameter / 2.0f),
		height(height), ring_data(shared_vec), color_data(shared_col)
	{
		// We'll step "points" times to complete the vertex data for one ring / circle
		float rad_step = 2 * M_PI / points;
		for(int i = 0; i != points; ++i)
		{
			float curr_rad = rad_step * i;
			vec3 new_point(
				radius * sin(curr_rad),
				height,
				radius * cos(curr_rad));

			ring_data->at(i + offset) = new_point;

			// Simple height-dependent gradient
			color_data->at(i + offset) = vec3(
				(float)(rand()) / (float)(RAND_MAX),
				(float)(rand()) / (float)(RAND_MAX),
				(float)(rand()) / (float)(RAND_MAX));
		}
	}

	void sine_wave(float displacement)
	{
		float period = 16.0f;
		float amplitude = 10.0f;
		float rad_step = 2 * M_PI / points * period;
		for(int i = 0; i != points; ++i)
		{
			float curr_rad = rad_step * i;
			ring_data->at(i + offset).y = height + 
				amplitude * sin(curr_rad + displacement);
		}
	}
};

// Towers consist of a series of rings made out of points
Tower::Tower(float base_diameter, float height, int total_rings,
	int points_per_ring, const GLuint pos_index) :
	position_index(pos_index)
{
	rings.reserve(total_rings);

	// Reserve enough space for all points that make up the tower
	vertex_data = std::make_shared<vector<vec3>>(total_rings * points_per_ring);
	color_data = std::make_shared<vector<vec3>>(total_rings * points_per_ring);

	// Create rings with their respective offsets and parameters
	// THIS WILL FILL vertex_data!
	for(int i = 0; i != total_rings; ++i)
	{
		rings.push_back(Ring(points_per_ring, i * points_per_ring,
			base_diameter, i * (height / total_rings), 
			vertex_data, color_data));
	}

	// Total size in bytes for VBO
	total_vertex_size = stride * vertex_data->size();
	total_color_size = stride * color_data->size();
}

Tower::~Tower()
{
	// Delete VAO
	glDeleteVertexArrays(1, &vao_id);

	// Cleanup VBO
	glDeleteBuffers(1, &vertex_buffer_id);
	glDeleteBuffers(1, &color_buffer_id);

	// Cleanup attributes
	glDisableVertexAttribArray(position_index);
	glDisableVertexAttribArray(position_index + 1);
}

void Tower::bind_buffer_data()
{
	glGenVertexArrays(1, &vao_id);
	glBindVertexArray(vao_id);

	// Bind vertex buffer data
	glGenBuffers(1, &vertex_buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
	glBufferData(GL_ARRAY_BUFFER, total_vertex_size, &(*vertex_data)[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(position_index);
	glVertexAttribPointer(position_index, 3, GL_FLOAT, GL_FALSE, stride, 0);

	// Bind color buffer data
	glGenBuffers(1, &color_buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, color_buffer_id);
	glBufferData(GL_ARRAY_BUFFER, total_color_size, &(*color_data)[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(position_index + 1);
	glVertexAttribPointer(position_index + 1, 3, GL_FLOAT, GL_FALSE, stride, 0);
}

void Tower::update_VBO() const
{
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
	glBufferSubData(GL_ARRAY_BUFFER, 0, total_vertex_size, &(*vertex_data)[0]);
}

void Tower::render() const
{
	// Bind VAO for this object and draw
	glBindVertexArray(vao_id);
	glDrawArrays(GL_POINTS, 0, vertex_data->size());
}

void Tower::sine_wave()
{
	// Calculate delta time for smooth animation
	float delta_time = Time::get_delta();

	// Get displacement for this frame
	static float displacement;
	displacement += 1.5f * delta_time;

	typedef vector<Ring>::iterator ring_iter;
	for(ring_iter iter = rings.begin(); iter != rings.end(); ++iter)
		iter->sine_wave(displacement);

	// Update mesh
	update_VBO();
}

