#pragma once

#include <string>

GLuint LoadShaders(const std::string vert_filepath, const std::string tesc_filepath,
	const std::string tese_filepath, const std::string geom_filepath,
	const std::string frag_filepath, const GLuint position_index);
