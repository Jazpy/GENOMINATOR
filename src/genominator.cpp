#include <iostream>

using std::cout;	using std::cerr;
using std::cin;		using std::endl;

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <shader.hpp>
#include <plane.hpp>
#include <camera.hpp>

static const GLuint position_index = 0;

// Auxiliary setup functions
void GLFWSetup(GLFWwindow **window);
void GLEWSetup();
void GLSetup(GLuint &program_id);

// Auxiliary cleanup function
void cleanup(GLuint &program_id);

int main()
{
	// Initialize GLFW and GLEW
	GLFWwindow *window;

	try
	{
		GLFWSetup(&window);
		GLEWSetup();
	} catch(int e) {
		return e;
	}

	// Setup OpenGL, load shaders
	GLuint program_id;
	GLSetup(program_id);

	// Setup our camera
	Camera camera(program_id, 90.0f, 16.0f / 9.0f, 5.0f, 150.0f, 3, 2);

	// Simple plane for testing, create and bind
	Plane plane(position_index);
	plane.bind_buffer_data();
	// plane.bind_to_vao();

	do {
		// Update camera
		camera.update(true);
		
		// Draw our current batch
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPatchParameteri(GL_PATCH_VERTICES, 3);
		glDrawElements(GL_PATCHES, plane.get_index_count(), GL_UNSIGNED_INT, 0);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	// Check if the ESC key was pressed or the window was closed
	} while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	cleanup(program_id);

	return 0;
}

void GLFWSetup(GLFWwindow **window)
{
	// Initialize GLFW
	if(!glfwInit())
	{
		cerr << "Failed to initialize GLFW" << endl;

		throw -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	*window = glfwCreateWindow(1920, 1080, "Genominator", NULL, NULL);

	if(*window == NULL)
	{
		cerr << "Failed to open GLFW window." << endl;
		glfwTerminate();

		throw -1;
	}

	glfwMakeContextCurrent(*window);

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(*window, GLFW_STICKY_KEYS, GL_TRUE);
}

void GLEWSetup()
{
	// Initialize GLEW
	glewExperimental = true; // Needed for core profile

	if(glewInit() != GLEW_OK)
	{
		cerr << "Failed to initialize GLEW." << endl;
		glfwTerminate();

		throw -1;
	}
}

void GLSetup(GLuint &program_id)
{
	// Enable depth test, accept if fragment is closer to camera
	// than the former one
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS); 

	// Enable culling
	glEnable(GL_CULL_FACE);

	// Create and compile our GLSL program from the shaders
	program_id = LoadShaders("../assets/shaders/genominator.vert",
				 "../assets/shaders/genominator.tesc",
				 "../assets/shaders/genominator.tese",
				 "../assets/shaders/genominator.geom",
				 "../assets/shaders/genominator.frag",
				 position_index);

	// Use our shader
	glUseProgram(program_id);
}

void cleanup(GLuint &program_id)
{
	// Cleanup VBO
	glDeleteProgram(program_id);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();
}
