#include <camera.hpp>
#include <glm/gtc/matrix_transform.hpp>

using glm::vec3;	using glm::mat4;

Camera::Camera(GLuint program_id, float fov, float aspect_ratio,
	float min_distance, float max_distance)
{
	// Get our handle
	matrix_id = glGetUniformLocation(program_id, "MVP");

	// Initialize matrices
	
	// Projection matrix
	mat4 projection = glm::perspective(glm::radians(fov),
		aspect_ratio, min_distance, max_distance);

	// Camera matrix
	mat4 view = glm::lookAt
		(
			vec3(4, 3, -3),	// Camera is at (4, 3, -3)
			vec3(0, 0, 0),	// looking at the origin
			vec3(0, 1, 0)	// (0, -1, 0) is upside-down
		);

	// model matrix: an identity matrix (model will be at the origin)
	mat4 model = mat4(1.0f);

	// Our ModelViewProjection: multiplication of our 3 matrices
	MVP  = projection * view * model; 
}

GLfloat *Camera::get_transformation()
{
	return &MVP[0][0];
}

GLint Camera::get_handle()
{
	return matrix_id;
}
