#pragma once
#include "src/Render/GraphicsContext.h"

struct GLFWwindow;
class OpenGLContext : public GraphicsContext
{
public:
	OpenGLContext(GLFWwindow *windowHandle);
	~OpenGLContext();

	virtual void Init() override;
	virtual void SwapBuffers() override;

private:
	GLFWwindow *m_WindowHandle;
};
