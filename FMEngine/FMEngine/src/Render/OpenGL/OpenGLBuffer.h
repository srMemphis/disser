#pragma once
#include <iostream>
#include <initializer_list>
#include <vector>

enum class ShaderDataType
{
	None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
};

static unsigned int ShaderDataTypeSize(ShaderDataType type)
{
	switch (type)
	{
	case ShaderDataType::Float:    return 4;
	case ShaderDataType::Float2:   return 4 * 2;
	case ShaderDataType::Float3:   return 4 * 3;
	case ShaderDataType::Float4:   return 4 * 4;
	case ShaderDataType::Mat3:     return 4 * 3 * 3;
	case ShaderDataType::Mat4:     return 4 * 4 * 4;
	case ShaderDataType::Int:      return 4;
	case ShaderDataType::Int2:     return 4 * 2;
	case ShaderDataType::Int3:     return 4 * 3;
	case ShaderDataType::Int4:     return 4 * 4;
	case ShaderDataType::Bool:     return 1;
	}

	std::cout << "ERROR: Unknown ShaderDataType!\n";
	return 0;
}

struct BufferElement
{
	std::string Name;
	ShaderDataType Type;
	unsigned int Size;
	unsigned int Offset;
	bool Normalized;

	BufferElement() = default;

	BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
		: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
	{
	}

	unsigned int GetComponentCount() const
	{
		switch (Type)
		{
		case ShaderDataType::Float:   return 1;
		case ShaderDataType::Float2:  return 2;
		case ShaderDataType::Float3:  return 3;
		case ShaderDataType::Float4:  return 4;
		case ShaderDataType::Mat3:    return 3; // 3* float3
		case ShaderDataType::Mat4:    return 4; // 4* float4
		case ShaderDataType::Int:     return 1;
		case ShaderDataType::Int2:    return 2;
		case ShaderDataType::Int3:    return 3;
		case ShaderDataType::Int4:    return 4;
		case ShaderDataType::Bool:    return 1;
		}

		std::cout << "ERROR: Unknown ShaderDataType!\n";
		return 0;
	}
};

class BufferLayout
{
public:
	BufferLayout() {}

	BufferLayout(std::initializer_list<BufferElement> elements)
		: m_Elements(elements)
	{	
		// stride is a size of a vertex
		CalculateOffsetsAndStride();
	}

	unsigned int GetStride() const { return m_Stride; }
	const std::vector<BufferElement>& GetElements() const { return m_Elements; }

	std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
	std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
	std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
	std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

private:
	void CalculateOffsetsAndStride()
	{
		unsigned int cur_offset = 0;
		for (auto& element : m_Elements)
		{
			element.Offset = cur_offset;
			cur_offset += element.Size;
		}
		m_Stride = cur_offset;
	}

private:
	std::vector<BufferElement> m_Elements;
	unsigned int m_Stride = 0;
};

class OpenGLVertexBuffer
{
public:
	OpenGLVertexBuffer(float* vertices, unsigned int size);
	~OpenGLVertexBuffer();

	void Bind();
	void Unbind();

	void SetData(const void* data, unsigned int size);

	const BufferLayout& GetLayout() { return m_Layout; }
	void SetLayout(const BufferLayout& layout);

private:
	unsigned int m_BufferID;
	BufferLayout m_Layout;
};

class OpenGLIndexBuffer
{
public:
	OpenGLIndexBuffer(unsigned int* indices, unsigned int count);
	~OpenGLIndexBuffer();

	void Bind();
	void Unbind();

	unsigned int GetCount() const { return m_Count; }
private:
	unsigned int m_BufferID;
	unsigned int m_Count;
};
