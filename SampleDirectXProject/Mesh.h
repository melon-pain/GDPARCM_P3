#pragma once

#include "Resource.h"
#include <d3d11.h>
#include <vector>

#include "Vertex.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

class VertexMesh;
class Mesh : public Resource
{
public:
	Mesh(const wchar_t* full_path);
	~Mesh();
public:
	VertexBuffer* GetVertexBuffer() const;
	IndexBuffer* GetIndexBuffer() const;
	const std::vector<VertexMesh>& GetVertices() const;
private:
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	std::vector<VertexMesh> list_vertices;
	std::vector<unsigned int> list_indices;
private:
	friend class DeviceContext;
};

