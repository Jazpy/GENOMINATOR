#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

class Camera
{
	private:

	// OpenGL shader uniforms
	GLuint projection_u, modelview_u, normal_u;
	GLuint light_pos_u, ambient_mat_u, diffuse_mat_u;
	GLuint inner_tess_lvl_u, outer_tess_lvl_u;

	// Camera matrices
	glm::mat4 projection;
	glm::mat4 modelview;
	glm::mat4 normal;

	// Tesselation level values
	float inner_tess_lvl, outer_tess_lvl;

	public:

	Camera(GLuint program_id, float fov, float aspect_ratio,
		float min_distance, float max_distance, float inner, float outer);

	// Update camera
	void update(bool rotate);
	// Rotate around the origin
	void rotate_origin();

	// Update tesselation levels
	void set_tess_lvls(float inner, float outer);
};
