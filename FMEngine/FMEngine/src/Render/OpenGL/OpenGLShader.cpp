#include "OpenGLShader.h"

#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>

#include "external/glad/include/glad/glad.h"

std::string read_from_file(const char* file_Path);


OpenGLShader::OpenGLShader(const char* vertex_path, const char* fragment_path)
{
	// Read our shaders into the appropriate buffers
	std::string vertexSource = read_from_file(vertex_path);     // Get source code for vertex shader.
	std::string fragmentSource = read_from_file(fragment_path); // Get source code for fragment shader.

	// Create an empty vertex shader handle
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// Send the vertex shader source code to GL
	// Note that std::string's .c_str is NULL character terminated.
	const GLchar* source = (const GLchar*)vertexSource.c_str();
	glShaderSource(vertexShader, 1, &source, 0);

	// Compile the vertex shader
	glCompileShader(vertexShader);

	GLint isCompiled = 0;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

		// We don't need the shader anymore.
		glDeleteShader(vertexShader);
		
		std::cout << "Vertex shader compilation ERROR:\n";
		for (GLchar letter : infoLog)
			std::cout << letter;

		return;
	}

	// Create an empty fragment shader handle
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Send the fragment shader source code to GL
	// Note that std::string's .c_str is NULL character terminated.
	source = (const GLchar*)fragmentSource.c_str();
	glShaderSource(fragmentShader, 1, &source, 0);

	// Compile the fragment shader
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

		// We don't need the shader anymore.
		glDeleteShader(fragmentShader);
		// Either of them. Don't leak shaders.
		glDeleteShader(vertexShader);

		std::cout << "Fragment shader compilation ERROR\n";
		for (GLchar letter : infoLog)
			std::cout << letter;

		return;
	}

	// Vertex and fragment shaders are successfully compiled.
	// Now time to link them together into a program.
	// Get a program object.
	m_ProgramID = glCreateProgram();

	// Attach our shaders to our program
	glAttachShader(m_ProgramID, vertexShader);
	glAttachShader(m_ProgramID, fragmentShader);

	// Link our program
	glLinkProgram(m_ProgramID);

	// Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(m_ProgramID, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(m_ProgramID, maxLength, &maxLength, &infoLog[0]);

		// We don't need the program anymore.
		glDeleteProgram(m_ProgramID);
		// Don't leak shaders either.
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		std::cout << "Shader program linling ERROR:\n";
		for (GLchar letter : infoLog)
			std::cout << letter;

		return;
	}

	// Always detach shaders after a successful link.
	glDetachShader(m_ProgramID, vertexShader);
	glDetachShader(m_ProgramID, fragmentShader);
}

OpenGLShader::~OpenGLShader()
{
	glDeleteProgram(m_ProgramID);
}

void OpenGLShader::Bind()
{
	glUseProgram(m_ProgramID);
}
void OpenGLShader::Unbind()
{
	glUseProgram(0);
	
}

std::string read_from_file(const char* file_Path)
{
	std::ifstream fileStream(file_Path);
	if (fileStream.is_open())
	{	
		std::stringstream buffer;
		buffer << fileStream.rdbuf();
		return buffer.str();
	}

	std::cerr << "Cannot open file: " << file_Path << '\n';
	return "";
}
