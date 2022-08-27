#include "OpenGLShader.h"

#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>

#include "glad/glad.h"
#include <glm/gtc/type_ptr.hpp>

std::string read_from_file(const std::string& file_Path)
{
	std::ifstream fileStream(file_Path);
	if (fileStream.is_open())
	{
		std::stringstream buffer;
		buffer << fileStream.rdbuf();
		return buffer.str();
	}

	std::cerr << "Shader ERROR: Cannot open file: " << file_Path << '\n';
	return "";
}

OpenGLShader::OpenGLShader()
	: OpenGLShader("Common", "Shaders/Common.vert", "Shaders/Common.frag")
{
}

OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	: m_ProgramID(0), m_name(name)
{
	// Read our shaders into the appropriate buffers
	std::string vertexSource = read_from_file(vertexSrc);     // Get source code for vertex shader.
	std::string fragmentSource = read_from_file(fragmentSrc); // Get source code for fragment shader.
	
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
		
		std::cerr << "Vertex shader compilation ERROR:\n";
		for (GLchar letter : infoLog)
			std::cerr << letter;

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
			std::cout << letter << '\n';

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

void OpenGLShader::Bind() const
{
	glUseProgram(m_ProgramID);
}

void OpenGLShader::Unbind() const
{
	glUseProgram(0);
	
}

void OpenGLShader::SetInt(const std::string& name, int value)
{
	GLint location = glGetUniformLocation(m_ProgramID, name.c_str());
	glUniform1i(location, value);
}

void OpenGLShader::SetIntArray(const std::string& name, int* values, uint32_t count)
{
}

void OpenGLShader::SetFloat(const std::string& name, float value)
{
	GLint location = glGetUniformLocation(m_ProgramID, name.c_str());
	glUniform1f(location, value);
}

void OpenGLShader::SetFloat2(const std::string& name, const glm::vec2& value)
{
	GLint location = glGetUniformLocation(m_ProgramID, name.c_str());
	glUniform2f(location, value.x, value.y);
}

void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value)
{
	GLint location = glGetUniformLocation(m_ProgramID, name.c_str());
	glUniform3f(location, value.x, value.y, value.z);
}

void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value)
{
	GLint location = glGetUniformLocation(m_ProgramID, name.c_str());
	glUniform4f(location, value.x, value.y, value.z, value.w);
}

void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value)
{
	GLint location = glGetUniformLocation(m_ProgramID, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

const std::string& OpenGLShader::GetName() const
{
	return m_name;
}
