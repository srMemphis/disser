#pragma once
#include "fmepch.h"

#include "src/Render/Buffer.h"

class OpenGLVertexBuffer : public VertexBuffer
{
public:
	OpenGLVertexBuffer(float* vertices, uint32_t size);
	virtual ~OpenGLVertexBuffer();

	virtual void Bind() override;
	virtual void Unbind() override;

	virtual void SetData(const void* data, uint32_t size) override;

	virtual const BufferLayout& GetLayout() override { return m_Layout; }
	virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; };

private:
	uint32_t m_BufferID;
	BufferLayout m_Layout;
};

class OpenGLIndexBuffer : public IndexBuffer
{
public:
	OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
	virtual ~OpenGLIndexBuffer();

	virtual void Bind() override;
	virtual void Unbind() override;

	virtual uint32_t GetCount() override  { return m_Count; }

private:
	uint32_t m_BufferID;
	uint32_t m_Count;
};
