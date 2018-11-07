#include <iostream>

using std::cout;	using std::cerr;
using std::cin;		using std::endl;

#include <glm/glm.hpp>

using glm::vec3;

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <shader.hpp>
#include <tower.hpp>
#include <camera.hpp>
#include <time.hpp>

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
	Camera camera(program_id, 90.0, 16.0 / 9.0, 0.5, 300.0, 8, 8);
	camera.lookat(vec3(40, 80, 0), vec3(0, 80, 0));

	// Simple plane for testing, create and bind
	/*
	Plane plane(30.0f, 30.0f, 11, 11, position_index);
	plane.bind_buffer_data();
	*/
	Tower tower(50.0f, 160.0f, 200, 200, position_index);
	tower.bind_buffer_data();

	do {
		// Update camera
		camera.update(true);
		// Update delta time for animations
		Time::update();

		// Update model
		//plane.ripple();
		tower.sine_wave();
		
		// Draw our current batch
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//plane.render();
		tower.render();

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

	// Might want to enable culling later, not sure yet
	// glEnable(GL_CULL_FACE);

	// Create and compile our GLSL program from the shaders
	/*
	program_id = LoadShaders("../assets/shaders/tess/genominator.vert",
				 "../assets/shaders/tess/genominator.tesc",
				 "../assets/shaders/tess/genominator.tese",
				 "../assets/shaders/tess/genominator.geom",
				 "../assets/shaders/tess/genominator.frag",
				 position_index);
	*/
	program_id = LoadShadersSimple("../assets/shaders/simple/genominator.vert",
				       "../assets/shaders/simple/genominator.frag",
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
