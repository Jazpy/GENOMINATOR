#include <line.hpp>

using std::vector;

Line::Line()
{
	// Dummy vertex values
	vertex_buffer_data.push_back(1.0f);
	vertex_buffer_data.push_back(1.0f);
	vertex_buffer_data.push_back(-1.0f);

	vertex_buffer_data.push_back(-1.0f);
	vertex_buffer_data.push_back(-1.0f);
	vertex_buffer_data.push_back(-1.0f);

	vertex_buffer_data.push_back(-1.0f);
	vertex_buffer_data.push_back(1.0f);
	vertex_buffer_data.push_back(-1.0f);

	// Dummy color values
	color_buffer_data.push_back(1.0f);
	color_buffer_data.push_back(1.0f);
	color_buffer_data.push_back(1.0f);

	color_buffer_data.push_back(1.0f);
	color_buffer_data.push_back(1.0f);
	color_buffer_data.push_back(1.0f);

	color_buffer_data.push_back(1.0f);
	color_buffer_data.push_back(1.0f);
	color_buffer_data.push_back(1.0f);

	// Bind vertex buffer data
	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER,
		vertex_buffer_data.size() * sizeof(float),
		&vertex_buffer_data[0], GL_STATIC_DRAW);

	// Bind color buffer data
	glGenBuffers(1, &color_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
	glBufferData(GL_ARRAY_BUFFER,
		color_buffer_data.size() * sizeof(float),
		&color_buffer_data[0], GL_STATIC_DRAW);

}

Line::~Line()
{
	// Cleanup VBO
	glDeleteBuffers(1, &vertex_buffer);
	glDeleteBuffers(1, &color_buffer);

	// Cleanup attributes
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void Line::BindToVAO()
{
	// Bind our VBOs
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
}
