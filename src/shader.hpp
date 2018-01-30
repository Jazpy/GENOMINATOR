#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>

GLuint load_shaders(const std::string vertex_filepath,
	const std::string fragment_filepath);

#endif
