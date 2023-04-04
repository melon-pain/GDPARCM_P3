#pragma once
#include "SimpleMath.h"

using namespace DirectX;

class VertexMesh
{
public:
	VertexMesh() :position(), texcoord()
	{
	}
	VertexMesh(SimpleMath::Vector3 _position, SimpleMath::Vector2 _texcoord) :position(_position), texcoord(_texcoord)
	{
	}
	VertexMesh(const VertexMesh& vertex) :position(vertex.position), texcoord(vertex.texcoord)
	{
	}
	~VertexMesh()
	{
	}
public:
	SimpleMath::Vector3 position;
	SimpleMath::Vector2 texcoord;
};
