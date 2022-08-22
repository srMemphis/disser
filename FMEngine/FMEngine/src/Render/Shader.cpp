#include "Shader.h"
#include "Renderer.h"
#include "OpenGL/OpenGLShader.h"

#include <cassert>

Shader* Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
{
	switch (Renderer::GetAPI())
	{
	case RendererAPI::API::None:    std::cerr << "RendererAPI::None is currently not supported!"; return nullptr;
	case RendererAPI::API::OpenGL:  return new OpenGLShader(name, vertexSrc, fragmentSrc);
	}

	assert(false && "Unknown RendererAPI!");
	return nullptr;
}

Shader* Shader::Create()
{
	switch (Renderer::GetAPI())
	{
	case RendererAPI::API::None:    std::cerr << "RendererAPI::None is currently not supported!"; return nullptr;
	case RendererAPI::API::OpenGL:  return new OpenGLShader();
	}

	assert(false && "Unknown RendererAPI!");
	return nullptr;
}

void ShaderLibrary::Add(const std::shared_ptr<Shader>& shader)
{
	auto& name = shader->GetName();
	assert(!Exists(name) && "Shader already exists!");
	m_Shaders[name] = shader;
}

std::shared_ptr<Shader> ShaderLibrary::Get(const std::string& name)
{
	assert(Exists(name) && "Shader not found!");
	return m_Shaders[name];
}

bool ShaderLibrary::Exists(const std::string& name) const
{
	return m_Shaders.find(name) != m_Shaders.end();
}
