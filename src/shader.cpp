#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>

#include "shader.hpp"

GLuint LoadShaders(const std::string vert_filepath, const std::string tesc_filepath,
	const std::string tese_filepath, const std::string geom_filepath,
	const std::string frag_filepath, const GLuint position_index)
{
	// Create the shaders
	GLuint vert_shader_id = glCreateShader(GL_VERTEX_SHADER);
	GLuint tesc_shader_id = glCreateShader(GL_TESS_CONTROL_SHADER);
	GLuint tese_shader_id = glCreateShader(GL_TESS_EVALUATION_SHADER);
	GLuint geom_shader_id = glCreateShader(GL_GEOMETRY_SHADER);
	GLuint frag_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string vert_shader_code;
	std::ifstream vert_shader_stream(vert_filepath, std::ios::in);
	if(vert_shader_stream.is_open())
	{
		std::stringstream sstr;
		sstr << vert_shader_stream.rdbuf();
		vert_shader_code = sstr.str();
		vert_shader_stream.close();
	} else {
		std::cout << "Impossible to open " << vert_filepath << 
			". Are you in the right directory ? " << std::endl;

		return 0;
	}

	// Read the Tesselation Control Shader code from the file
	std::string tesc_shader_code;
	std::ifstream tesc_shader_stream(tesc_filepath, std::ios::in);
	if(tesc_shader_stream.is_open())
	{
		std::stringstream sstr;
		sstr << tesc_shader_stream.rdbuf();
		tesc_shader_code = sstr.str();
		tesc_shader_stream.close();
	} else {
		std::cout << "Impossible to open " << tesc_filepath << 
			". Are you in the right directory ? " << std::endl;

		return 0;
	}

	// Read the Tesselation Evaluation Shader code from the file
	std::string tese_shader_code;
	std::ifstream tese_shader_stream(tese_filepath, std::ios::in);
	if(tese_shader_stream.is_open())
	{
		std::stringstream sstr;
		sstr << tese_shader_stream.rdbuf();
		tese_shader_code = sstr.str();
		tese_shader_stream.close();
	} else {
		std::cout << "Impossible to open " << tese_filepath << 
			". Are you in the right directory ? " << std::endl;

		return 0;
	}

	// Read the Geometry Shader code from the file
	std::string geom_shader_code;
	std::ifstream geom_shader_stream(geom_filepath, std::ios::in);
	if(geom_shader_stream.is_open())
	{
		std::stringstream sstr;
		sstr << geom_shader_stream.rdbuf();
		geom_shader_code = sstr.str();
		geom_shader_stream.close();
	} else {
		std::cout << "Impossible to open " << geom_filepath << 
			". Are you in the right directory ? " << std::endl;

		return 0;
	}
	
	// Read the Fragment Shader code from the file
	std::string frag_shader_code;
	std::ifstream frag_shader_stream(frag_filepath, std::ios::in);
	if(frag_shader_stream.is_open())
	{
		std::stringstream sstr;
		sstr << frag_shader_stream.rdbuf();
		frag_shader_code = sstr.str();
		frag_shader_stream.close();
	}

	GLint result = GL_FALSE;
	int info_log_length;

	// Compile Vertex Shader
	std::cout << "Compiling shader: " << vert_filepath << std::endl;
	char const *vert_source_pointer = vert_shader_code.c_str();
	glShaderSource(vert_shader_id, 1, &vert_source_pointer, NULL);
	glCompileShader(vert_shader_id);

	// Check Vertex Shader
	glGetShaderiv(vert_shader_id, GL_COMPILE_STATUS, &result);
	glGetShaderiv(vert_shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
	if(info_log_length > 0)
	{
		std::vector<char> vert_shader_error_message(
			info_log_length + 1);
		glGetShaderInfoLog(vert_shader_id, info_log_length,
			NULL, &vert_shader_error_message[0]);
		std::cout << &vert_shader_error_message[0] << std::endl;
	}

	// Compile Tesselation Control Shader
	std::cout << "Compiling shader: " << tesc_filepath << std::endl;
	char const *tesc_source_pointer = tesc_shader_code.c_str();
	glShaderSource(tesc_shader_id, 1, &tesc_source_pointer, NULL);
	glCompileShader(tesc_shader_id);

	// Check Tesselation Control Shader
	glGetShaderiv(tesc_shader_id, GL_COMPILE_STATUS, &result);
	glGetShaderiv(tesc_shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
	if(info_log_length > 0)
	{
		std::vector<char> tesc_shader_error_message(
			info_log_length + 1);
		glGetShaderInfoLog(tesc_shader_id, info_log_length,
			NULL, &tesc_shader_error_message[0]);
		std::cout << &tesc_shader_error_message[0] << std::endl;
	}

	// Compile Tesselation Evaluation Shader
	std::cout << "Compiling shader: " << tese_filepath << std::endl;
	char const *tese_source_pointer = tese_shader_code.c_str();
	glShaderSource(tese_shader_id, 1, &tese_source_pointer, NULL);
	glCompileShader(tese_shader_id);

	// Check Tesselation Evaluation Shader
	glGetShaderiv(tese_shader_id, GL_COMPILE_STATUS, &result);
	glGetShaderiv(tese_shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
	if(info_log_length > 0)
	{
		std::vector<char> tese_shader_error_message(
			info_log_length + 1);
		glGetShaderInfoLog(tese_shader_id, info_log_length,
			NULL, &tese_shader_error_message[0]);
		std::cout << &tese_shader_error_message[0] << std::endl;
	}

	// Compile Geometry Shader
	std::cout << "Compiling shader: " << geom_filepath << std::endl;
	char const *geom_source_pointer = geom_shader_code.c_str();
	glShaderSource(geom_shader_id, 1, &geom_source_pointer, NULL);
	glCompileShader(geom_shader_id);

	// Check Geometry Shader
	glGetShaderiv(geom_shader_id, GL_COMPILE_STATUS, &result);
	glGetShaderiv(geom_shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
	if(info_log_length > 0)
	{
		std::vector<char> geom_shader_error_message(
			info_log_length + 1);
		glGetShaderInfoLog(geom_shader_id, info_log_length,
			NULL, &geom_shader_error_message[0]);
		std::cout << &geom_shader_error_message[0] << std::endl;
	}

	// Compile Fragment Shader
	std::cout << "Compiling shader: " << frag_filepath << std::endl;
	char const *frag_source_pointer = frag_shader_code.c_str();
	glShaderSource(frag_shader_id, 1, &frag_source_pointer, NULL);
	glCompileShader(frag_shader_id);

	// Check Fragment Shader
	glGetShaderiv(frag_shader_id, GL_COMPILE_STATUS, &result);
	glGetShaderiv(frag_shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
	if(info_log_length > 0)
	{
		std::vector<char> frag_shader_error_message(
			info_log_length + 1);
		glGetShaderInfoLog(frag_shader_id, info_log_length,
			NULL, &frag_shader_error_message[0]);
		std::cout << &frag_shader_error_message[0] << std::endl;
	}

	// Link the program
	std::cout << "Linking program\n" << std::endl;
	GLuint program_id = glCreateProgram();
	glAttachShader(program_id, vert_shader_id);
	glAttachShader(program_id, tesc_shader_id);
	glAttachShader(program_id, tese_shader_id);
	glAttachShader(program_id, geom_shader_id);
	glAttachShader(program_id, frag_shader_id);
	glBindAttribLocation(program_id, position_index, "Position");
	glLinkProgram(program_id);

	// Check the program
	glGetProgramiv(program_id, GL_LINK_STATUS, &result);
	glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_log_length);
	if(info_log_length > 0){
		std::vector<char> program_error_message(info_log_length + 1);
		glGetProgramInfoLog(program_id, info_log_length,
			NULL, &program_error_message[0]);
		std::cout << &program_error_message[0] << std::endl;
	}
	
	glDetachShader(program_id, vert_shader_id);
	glDetachShader(program_id, tesc_shader_id);
	glDetachShader(program_id, tese_shader_id);
	glDetachShader(program_id, geom_shader_id);
	glDetachShader(program_id, frag_shader_id);
	
	glDeleteShader(vert_shader_id);
	glDeleteShader(tesc_shader_id);
	glDeleteShader(tese_shader_id);
	glDeleteShader(geom_shader_id);
	glDeleteShader(frag_shader_id);

	return program_id;
}


