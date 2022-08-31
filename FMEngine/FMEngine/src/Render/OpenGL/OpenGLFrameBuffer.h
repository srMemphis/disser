#pragma once
#include "src/Render/FrameBuffer.h"

class OpenGLFrameBuffer : public FrameBuffer
{
public:
	OpenGLFrameBuffer(uint32_t width, uint32_t height, bool multisample);
	OpenGLFrameBuffer();
	~OpenGLFrameBuffer();

	virtual uint32_t GetBufferID() override;
	virtual uint32_t GetTextureID() override;
	virtual void Bind() override;
	virtual void Unbind() override;
	virtual void Resize(int32_t width, int32_t height) override;
	virtual void BlitFrom(const std::shared_ptr<FrameBuffer>& source) override;
	virtual uint32_t GetWidth() override;
	virtual uint32_t GetHeight() override;
	virtual void SetSamples(uint8_t samples) override;
private:
	uint32_t m_TextureID;
	uint32_t m_BufferID;
	uint32_t m_RBO;

	uint8_t m_Samples;
	uint32_t m_Width;
	uint32_t m_Height;
	bool m_Multisample;
private:
	void Invalidate();
};
