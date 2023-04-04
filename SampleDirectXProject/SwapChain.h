
#pragma once
#include <d3d11.h>
#include "Prerequisites.h"

class SwapChain
{
public:
	SwapChain(HWND hwnd, UINT width, UINT height, RenderSystem* system);
	bool present(bool vsync);
	~SwapChain();

public:
	void SetDepthEnabled(bool enable);

	void SetFillMode(D3D11_FILL_MODE fill_mode);
	void SetCullMode(D3D11_CULL_MODE cull_mode);

	bool UpdateRasterizerState();

private:
	IDXGISwapChain * m_swap_chain;
	ID3D11RenderTargetView* m_rtv;

	// Depth buffer
	ID3D11DepthStencilView* m_dsv;
	ID3D11Texture2D* m_dsb;
	ID3D11DepthStencilState* m_dss;
	RenderSystem* m_system = nullptr;
	ID3D11RasterizerState* m_rasterizer_state;

private:
	D3D11_FILL_MODE fillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	D3D11_CULL_MODE cullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;

private:
	friend class DeviceContext;
};

