#define GLM_ENABLE_EXPERIMENTAL

#include <camera.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

using glm::vec3;	using glm::vec4;
using glm::mat4;	using glm::mat3;
using glm::quat;

using glm::degrees;	using glm::radians;
using glm::lookAt;	using glm::transpose;
using glm::angleAxis;	using glm::toMat4;
using glm::perspective;

Camera::Camera(GLuint program_id, float fov, float aspect_ratio,
	float min_distance, float max_distance, float inner, float outer)
{
	// Set tesselation levels
	inner_tess_lvl = inner;
	outer_tess_lvl = outer;

	// Get shader uniforms
	projection_u = glGetUniformLocation(program_id, "Projection");
	modelview_u = glGetUniformLocation(program_id, "Modelview");
	normal_u = glGetUniformLocation(program_id, "NormalMatrix");
	light_pos_u = glGetUniformLocation(program_id, "LightPosition");
	ambient_mat_u = glGetUniformLocation(program_id, "AmbientMaterial");
	diffuse_mat_u = glGetUniformLocation(program_id, "DiffuseMaterial");
	inner_tess_lvl_u = glGetUniformLocation(program_id, "TessLevelInner");
	outer_tess_lvl_u = glGetUniformLocation(program_id, "TessLevelOuter");
	patch_u = glGetUniformLocation(program_id, "B");
	patch_transpose_u = glGetUniformLocation(program_id, "BT");

	// Initialize patch matrices
	mat4 bezier(
		vec4(-1, 3, -3, 1),
		vec4(3, -6, 3, 0),
		vec4(-3, 3, 0, 0),
		vec4(1, 0, 0, 0)
		);
	glUniformMatrix4fv(patch_u, 1, GL_FALSE, &bezier[0][0]);
	glUniformMatrix4fv(patch_transpose_u, 1, GL_TRUE, &bezier[0][0]);
	
	// Initialize projection matrix
	projection = perspective(radians(fov),
		aspect_ratio, min_distance, max_distance);

	// Update camera view matrix
	vec3 camera_pos(15, 15, 15);
	vec3 target_pos(0, 0, 0);
	vec3 up_vector(0, 1, 0);
	modelview = lookAt(camera_pos, target_pos, up_vector);
}

void Camera::update(bool rotate)
{
	if(rotate)
		rotate_origin();

	// Update normal matrix
	normal = mat3(modelview);
	// Pack and transpose normal matrix
	float packed[9] =
	{
		normal[0][0], normal[1][0], normal[2][0],
		normal[0][1], normal[1][1], normal[2][1],
		normal[0][2], normal[1][2], normal[2][2]
	};

	// Update uniforms
	glUniform1f(inner_tess_lvl_u, inner_tess_lvl);
	glUniform1f(outer_tess_lvl_u, outer_tess_lvl);

	vec4 light_pos(0.0f, 15.0f, 0.0f, 0.0f);
	glUniform3fv(light_pos_u, 1, &light_pos.x);

	glUniform3f(ambient_mat_u, 0.0f, 0.0f, 0.0f);
	glUniform3f(diffuse_mat_u, 0.0f, 0.0f, 0.0f);

	// Send MVP to shaders
	glUniformMatrix4fv(projection_u, 1, 0, &projection[0][0]);
	glUniformMatrix4fv(modelview_u, 1, 0, &modelview[0][0]);
	glUniformMatrix3fv(normal_u, 1, 0, &packed[0]);
}

void Camera::rotate_origin()
{
	// Calculate delta time for smooth rotation
	static double last_time = glfwGetTime();
	double curr_time = glfwGetTime();
	float delta_time = float(curr_time - last_time);

	// Get rotation for this frame
	float speed = 0.005f * delta_time;

	// Create rotation matrix
	vec3 axis(0.0f, 1.0f, 0.0f);
	quat rot_quat = angleAxis(degrees(speed), axis);
	mat4 rotation_matrix = toMat4(rot_quat);

	// Rotate
	modelview *= rotation_matrix;

	last_time = curr_time;
}

void Camera::set_tess_lvls(float inner, float outer)
{
	inner_tess_lvl = inner;
	outer_tess_lvl = outer;
}
