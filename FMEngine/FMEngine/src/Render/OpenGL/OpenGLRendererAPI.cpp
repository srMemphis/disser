#include "OpenGLRendererAPI.h"
#include <glad/glad.h>
#include <iostream>
#include "GLDebugMessageCallback.h"

void OpenGLRendererAPI::Init()
{
	printf("OpenGL Info:\n");
	printf("\tVendor: %s\n",  glGetString(GL_VENDOR));
	printf("\tDevice: %s\n",  glGetString(GL_RENDERER));
	printf("\tVersion: %s\n", glGetString(GL_VERSION));

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(GLDebugMessageCallback, NULL);

	int maxSamples;
	glGetIntegerv(GL_MAX_SAMPLES, &maxSamples);
	printf("\tMax Samples: %i\n", maxSamples);

}

void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
	glViewport(x, y, width, height);
}

void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
{
	glClearColor(color.r, color.g, color.b, color.a);
}

void OpenGLRendererAPI::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
{
	vertexArray->Bind();
	uint32_t count = vertexArray->GetIndexBuffer()->GetCount();
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
}

void OpenGLRendererAPI::DrawLines(const std::shared_ptr<VertexArray>& vertexArray, uint32_t count)
{
	vertexArray->Bind();
	glDrawArrays(GL_LINE_STRIP, 0, count);
				//GL_LINE_STRIP
				//GL_LINES
}

void OpenGLRendererAPI::SetLineWidth(float width)
{
	glLineWidth(width);
}

void OpenGLRendererAPI::SetPolygonFill(bool fill)
{
	if (fill)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
}

void OpenGLRendererAPI::EnableBlend(bool enable)
{
	if (enable)
	{
		glEnable(GL_BLEND);
	}
	else
	{
		glDisable(GL_BLEND);
	}
}

void OpenGLRendererAPI::EnableDepthTest(bool enable)
{	
	if (enable)
	{
		glEnable(GL_DEPTH_TEST);
	}
	else
	{
		glDisable(GL_DEPTH_TEST);
	}
}

