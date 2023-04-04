
#pragma once
#include <d3d11.h>
#include "Prerequisites.h"

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* device_context, RenderSystem* system);
	void clearRenderTargetColor(SwapChain* swap_chain,float red, float green, float blue, float alpha);
	void clearDepthStencilView(SwapChain* swap_chain);
	void setRenderTargets(SwapChain* swap_chain);
	void setDepthStencilState(SwapChain* swap_chain);
	void setRenderState(SwapChain* swap_chain);

	void setVertexBuffer(VertexBuffer* vertex_buffer);
	void setIndexBuffer(IndexBuffer* index_buffer);

	void drawTriangleList(UINT vertex_count, UINT start_vertex_index);
	void drawIndexedTriangleList(UINT index_count, UINT start_vertex_index, UINT start_index_location);
	void drawIndexedTriangleList_Line(UINT index_count, UINT start_vertex_index, UINT start_index_location);
	void drawTriangleStrip(UINT vertex_count, UINT start_vertex_index);
	void drawIndexedTriangleStrip(UINT index_count, UINT start_vertex_index, UINT start_index_location);

	void setViewportSize(UINT width, UINT height);

	void setVertexShader(VertexShader* vertex_shader);
	void setPixelShader(PixelShader* pixel_shader);

	void setTexture(VertexShader* vertex_shader, class Texture* texture);
	void setTexture(PixelShader* pixel_shader, class Texture* texture);

	void setConstantBuffer(VertexShader* vertex_shader, ConstantBuffer* buffer);
	void setConstantBuffer(PixelShader* pixel_shader, ConstantBuffer* buffer);
	
	~DeviceContext();
private:
	ID3D11DeviceContext * m_device_context;
	RenderSystem* m_system = nullptr;
private:
	friend class ConstantBuffer;
};

