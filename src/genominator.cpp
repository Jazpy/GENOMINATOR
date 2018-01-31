#include <iostream>

using std::cout;	using std::cerr;
using std::endl;

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

GLFWwindow* window;
using glm::mat4;	using glm::vec3;

#include <shader.hpp>
#include <line.hpp>

int main( void )
{
	// Initialize GLFW
	if(!glfwInit())
	{
		cerr << "Failed to initialize GLFW" << endl;

		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow( 1024, 768, "GENOMINATOR", NULL, NULL);

	if(window == NULL)
	{
		cerr << "Failed to open GLFW window. "
			"If you have an Intel GPU, "
			"they are not 3.3 compatible" << endl;
		glfwTerminate();

		return -1;
	}

	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile

	if(glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();

		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Black background
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Enable depth test and culling
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 

	GLuint vertex_array_id;
	glGenVertexArrays(1, &vertex_array_id);
	glBindVertexArray(vertex_array_id);

	// Create and compile our GLSL program from the shaders
	GLuint program_id = load_shaders("../assets/shaders/transform.vshader",
		"../assets/shaders/color.fshader");

	// Get a handle for our "MVP" uniform
	GLuint matrix_id = glGetUniformLocation(program_id, "MVP");

	// projection matrix : 45° Field of view, 4:3 ratio,
	// display range : 0.1 unit <-> 100 units
	mat4 projection = glm::perspective(glm::radians(45.0f),
		4.0f / 3.0f, 0.1f, 1000.0f);
	// Camera matrix
	mat4 view = glm::lookAt(
		vec3(4,3,-3), // Camera is at (4,3,-3), in World Space
		vec3(0,0,0), // and looks at the origin
		vec3(0,1,0)  // Head is up (set to 0,-1,0 for upside-down)
		);
	// model matrix : an identity matrix (model will be at the origin)
	mat4 model = mat4(1.0f);
	// Our modelviewprojection : multiplication of our 3 matrices
	mat4 MVP  = projection * view * model; 

	// Simple line for testing, create and bind
	Line line;
	line.bind_to_vao();

	do {
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(program_id);

		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(matrix_id, 1, GL_FALSE, &MVP[0][0]);

		// Draw our current batch
		glDrawArrays(GL_LINE_LOOP, 0, 1 * 3);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	// Check if the ESC key was pressed or the window was closed
	} while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	// Cleanup VBO and shader
	glDeleteProgram(program_id);
	glDeleteVertexArrays(1, &vertex_array_id);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

