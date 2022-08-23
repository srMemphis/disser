#pragma once
#include "src/Render/FrameBuffer.h"

class OpenGLFrameBuffer : public FrameBuffer
{
public:
	OpenGLFrameBuffer(uint32_t width, uint32_t height);
	OpenGLFrameBuffer();
	~OpenGLFrameBuffer();

	virtual uint32_t GetBufferID() override;
	virtual uint32_t GetTextureID() override;
	virtual void Bind() override;
	virtual void Unbind() override;
	virtual void Resize(int32_t width, int32_t height) override;

private:
	uint32_t m_TextureID;
	uint32_t m_BufferID;
	uint32_t m_RBO;

	int32_t m_Width;
	int32_t m_Height;
private:
	void Invalidate();
};
