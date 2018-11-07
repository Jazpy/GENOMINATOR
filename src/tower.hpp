#pragma once

#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <vector>
#include <memory>

class Tower
{
	private:

	const GLuint position_index;

	// OpenGL VAO
	GLuint vao_id;

	// OpenGL buffer ids
	GLuint vertex_buffer_id;
	GLuint color_buffer_id;

	// Classes that control each individual ring
	class Ring;
	std::vector<Ring> rings;
	// Actual ring vertex and color data
	std::shared_ptr<std::vector<glm::vec3>> vertex_data;
	std::shared_ptr<std::vector<glm::vec3>> color_data;

	// Variables used for the VBO
	const GLsizei stride = 3 * sizeof(float);
	GLsizei total_vertex_size;
	GLsizei total_color_size;

	// FUNCTIONS

	// Update mesh in VBO
	void update_VBO() const;

	public:

	Tower(float base_diameter, float height, int total_rings,
		int points_per_ring, const GLuint pos_index);
	~Tower();

	// Bind vertex and color data
	void bind_buffer_data();

	// Bind VAO and render
	void render() const;

	// Apply a function to all control points
	void spin();
	void sine_wave();
};
