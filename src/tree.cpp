#define GLM_ENABLE_EXPERIMENTAL

#include <stdlib.h>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/geometric.hpp>
#include <tree.hpp>

using glm::vec3;
using std::vector;

typedef vector<float>::iterator vec_iter;

// Fractal construction takes place in the constructor
Tree::Tree(unsigned int iterations)
{
	// Create initial iteration data, this represents the
	// tree's "trunk"
	vector<float> trunk;
	
	// First point
	trunk.push_back(0.0f);
	trunk.push_back(0.0f);
	trunk.push_back(0.0f);
	// Second point
	trunk.push_back(0.0f);
	trunk.push_back(10.0f);
	trunk.push_back(0.0f);

	// Iterate, building more of the tree in each iteration
	vector<float> curr = trunk;
	for(int i = 0; i != iterations; ++i)
	{
		// Create new vector for this iteration's data
		vector<float> new_vec;

		// Modify past iteration's data, adding to final buffer
		for(vec_iter it = curr.begin(); it !=
			curr.end(); it += 6)
		{
			// Create glm vectors for easier processing
			vec3 p1(*it, *(it + 1), *(it + 2));
			vec3 p2(*(it + 3), *(it + 4), *(it + 5));

			// Split in half, midpoint formula
			vec3 midpoint = p1 + p2;
			midpoint = midpoint / 2.0f;

			// Add the split line to the final buffer
			vertex_buffer_data.push_back(p1.x);
			vertex_buffer_data.push_back(p1.y);
			vertex_buffer_data.push_back(p1.z);

			vertex_buffer_data.push_back(midpoint.x);
			vertex_buffer_data.push_back(midpoint.y);
			vertex_buffer_data.push_back(midpoint.z);

			++this->lines;

			// Random color values
			for(int j = 0; j != 6; ++j)
				color_buffer_data.push_back((float)(rand()) / (float)(RAND_MAX));

			// We'll create 3 branches
			for(int j = 0; j != 3; ++j)
			{
				// Calculate perpendicular vector
				vec3 original = midpoint - p1;
				vec3 perp = glm::cross(original, vec3(0.0f, 0.0f, 1.0f));

				// Rotate our new branch
				vec3 endpoint = rotate(p2 - midpoint, 45.0f, perp);
				endpoint = rotate(endpoint, 400.0f * j, original);

				// Add to this iteration's vector
				new_vec.push_back(midpoint.x);
				new_vec.push_back(midpoint.y);
				new_vec.push_back(midpoint.z);

				new_vec.push_back(midpoint.x + endpoint.x);
				new_vec.push_back(midpoint.y + endpoint.y);
				new_vec.push_back(midpoint.z + endpoint.z);
			}
		}

		curr = new_vec;
	}

	// Bind vertex buffer data
	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER,
		vertex_buffer_data.size() * sizeof(float),
		&vertex_buffer_data[0], GL_STATIC_DRAW);

	// Bind color buffer data
	glGenBuffers(1, &color_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
	glBufferData(GL_ARRAY_BUFFER,
		color_buffer_data.size() * sizeof(float),
		&color_buffer_data[0], GL_STATIC_DRAW);
}

Tree::~Tree()
{
	// Cleanup VBO
	glDeleteBuffers(1, &vertex_buffer);
	glDeleteBuffers(1, &color_buffer);

	// Cleanup attributes
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void Tree::BindToVAO()
{
	// Bind our VBOs
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
}
