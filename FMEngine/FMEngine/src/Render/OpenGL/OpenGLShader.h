#pragma once
class OpenGLShader
{
public:
	OpenGLShader(const char* vertex_path, const char* fragment_path);
	~OpenGLShader();

	void Bind();
	void Unbind();

private:

	unsigned int m_ProgramID;


};

