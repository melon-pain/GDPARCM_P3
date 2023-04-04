#pragma once
#include "Component.h"
#include "SimpleMath.h"

class ConstantBuffer;
class PixelShader;
class VertexShader;
class IndexBuffer;
class VertexBuffer;

class Mesh;

using namespace DirectX;
using namespace DirectX::SimpleMath;


class MeshComponent: public Component
{
public:
	MeshComponent();
	~MeshComponent() override;

public:
	void Start() override;
	void Update(float deltaTime) override;
	void SetMesh(Mesh* inMesh);

	void CalculateBounds();
	BoundingBox GetBounds() const;

	bool GetOutlined() const;
	void SetOutlined(bool flag);


protected:
	Mesh* mesh = nullptr;

protected:
	VertexBuffer* m_vb_outline = nullptr;
	VertexBuffer* m_vb = nullptr;
	IndexBuffer* m_ib = nullptr;
	VertexShader* m_vs = nullptr;
	PixelShader* m_ps = nullptr;
	PixelShader* m_ps_outline = nullptr;
	ConstantBuffer* m_cb = nullptr;

	BoundingBox bounds;
private:
	bool isOutlined = false;
protected:
	friend class Mesh;
};
