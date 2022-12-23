#pragma once
#include "fmepch.h"

class FrameBuffer
{
public:
	virtual uint32_t GetBufferID() = 0;
	virtual uint32_t GetTextureID() = 0;
	virtual void Bind() = 0;
	virtual void Unbind() = 0;
	virtual void Resize(int32_t width, int32_t height) = 0;
	virtual void BlitFrom(const std::shared_ptr<FrameBuffer>& source) = 0;
	virtual uint32_t GetWidth() = 0;
	virtual uint32_t GetHeight() = 0;
	virtual void SetSamples(uint8_t samples) = 0;

	static FrameBuffer* Create(int32_t width, int32_t height, bool multisample);
};
