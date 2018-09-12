#include <iostream>

using std::cout;	using std::cerr;
using std::cin;		using std::endl;

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <shader.hpp>
#include <tree.hpp>
#include <camera.hpp>

// Auxiliary setup functions
void GLFWSetup(GLFWwindow **window);
void GLEWSetup();
void GLSetup(GLuint &vao, GLuint &program_id);

// Auxiliary cleanup function
void Cleanup(GLuint &vao, GLuint &program_id);

int main()
{
	// Get user input for iterations
	int iterations;
	cout << "Number of iterations: ";
	cin >> iterations;

	// Initialize GLFW and GLEW
	GLFWwindow *window;

	try
	{
		GLFWSetup(&window);
		GLEWSetup();
	} catch(int e) {
		return e;
	}

	// Setup OpenGL, includes binding VAO and loading shaders
	GLuint vertex_array_id;
	GLuint program_id;
	GLSetup(vertex_array_id, program_id);

	// Setup our camera
	Camera camera(program_id, 45.0f, 4.0f / 3.0f, 0.1f, 1000.0f);

	// Simple tree for testing, create and bind
	Tree tree(iterations);
	tree.BindToVAO();

	do {
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Rotate camera
		camera.rotate_origin();
		
		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(camera.get_handle(), 1,
			GL_FALSE, camera.get_transformation());

		// Draw our current batch
		glDrawArrays(GL_LINES, 0, tree.get_lines() * 2);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	// Check if the ESC key was pressed or the window was closed
	} while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

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
	*window = glfwCreateWindow(1024, 768, "Fractals", NULL, NULL);

	if(*window == NULL)
	{
		cerr << "Failed to open GLFW window. "
			"If you have an Intel GPU, "
			"they are not 3.3 compatible" << endl;
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

void GLSetup(GLuint &vao, GLuint &program_id)
{
	// Enable depth test, accept if fragment is closer to camera
	// than the former one
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS); 

	// Enable culling
	glEnable(GL_CULL_FACE);

	// Generate and bind our VAO
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Create and compile our GLSL program from the shaders
	program_id = LoadShaders("../assets/shaders/transform.vshader",
		"../assets/shaders/color.fshader");

	// Use our shader
	glUseProgram(program_id);
}

void Cleanup(GLuint &vao, GLuint &program_id)
{
	// Cleanup VBO and shader
	glDeleteProgram(program_id);
	glDeleteVertexArrays(1, &vao);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();
}
