#pragma once
#include "src/Render/Buffer.h"

class Mesh
{
public:
	Mesh() = default;
	~Mesh();
	
	void SetLayout(std::initializer_list<BufferElement> elements);

	const void* GetData() const;

private:
	BufferLayout m_Layout;
	void* m_Data = nullptr;
	size_t m_Size = 0;
};
