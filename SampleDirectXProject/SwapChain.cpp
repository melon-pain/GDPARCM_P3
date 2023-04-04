
#include "SwapChain.h"
#include "GraphicsEngine.h"
#include "RenderSystem.h"
#include <exception>


SwapChain::SwapChain(HWND hwnd, UINT width, UINT height, RenderSystem* system) : m_system(system)
{
	ID3D11Device* device = m_system->m_d3d_device;

	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.BufferCount = 2;
	desc.BufferDesc.Width = width;
	desc.BufferDesc.Height = height;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = hwnd;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Windowed = TRUE;

	HRESULT hr = m_system->m_dxgi_factory->CreateSwapChain(device, &desc, &m_swap_chain);

	if (FAILED(hr))
	{
		throw std::exception("SwapChain not created successfully");
	}

	ID3D11Texture2D* buffer = NULL;
	hr = m_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);

	if (FAILED(hr))
	{
		throw std::exception("SwapChain not created successfully");
	}

	hr = device->CreateRenderTargetView(buffer, NULL, &m_rtv);
	buffer->Release();

	if (FAILED(hr))
	{
		throw std::exception("SwapChain not created successfully");
	}

	// DEPTH BUFFER
	D3D11_TEXTURE2D_DESC depthBufferDesc;
	depthBufferDesc.Width = width;
	depthBufferDesc.Height = height;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	hr = m_system->m_d3d_device->CreateTexture2D(&depthBufferDesc, nullptr, &buffer);

	if (FAILED(hr))
	{
		throw std::exception("Texture2D not created successfully");
	}

	hr = m_system->m_d3d_device->CreateDepthStencilView(buffer, nullptr, &m_dsv);

	if (FAILED(hr))
	{
		throw std::exception("DepthStencilView not created successfully");
	}

	D3D11_DEPTH_STENCIL_DESC depthStencildesc;
	ZeroMemory(&depthStencildesc, sizeof(D3D11_DEPTH_STENCIL_DESC));

	depthStencildesc.DepthEnable = true;
	depthStencildesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencildesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	depthStencildesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
	depthStencildesc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
	depthStencildesc.StencilEnable = true;

	depthStencildesc.BackFace.StencilFunc = D3D11_COMPARISON_NEVER;
	depthStencildesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencildesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencildesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencildesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	depthStencildesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencildesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencildesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_INCR_SAT;

	//depthStencildesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_GREATER;


	hr = m_system->m_d3d_device->CreateDepthStencilState(&depthStencildesc, &m_dss);
	if (FAILED(hr))
	{
		throw std::exception("DepthBuffer not created successfully");
	}

	D3D11_RASTERIZER_DESC rastDesc; 
	ZeroMemory(&rastDesc, sizeof(D3D11_RASTERIZER_DESC));
	rastDesc.FillMode = fillMode;
	rastDesc.CullMode = cullMode;
	hr = device->CreateRasterizerState(&rastDesc, &m_rasterizer_state);

	if (FAILED(hr))
	{
		throw std::exception("DepthBuffer not created successfully");
	}
}

SwapChain::~SwapChain()
{
	m_swap_chain->Release();
	m_rtv->Release();
	m_dsv->Release();
}

void SwapChain::SetDepthEnabled(bool enable)
{
	D3D11_DEPTH_STENCIL_DESC depthStencildesc;
	ZeroMemory(&depthStencildesc, sizeof(D3D11_DEPTH_STENCIL_DESC));

	depthStencildesc.DepthEnable = enable;
	depthStencildesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencildesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	depthStencildesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
	depthStencildesc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
	depthStencildesc.StencilEnable = true;

	depthStencildesc.BackFace.StencilFunc = D3D11_COMPARISON_NEVER;
	depthStencildesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencildesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencildesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencildesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	depthStencildesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencildesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencildesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_INCR_SAT;

	//depthStencildesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_GREATER;


	HRESULT hr = m_system->m_d3d_device->CreateDepthStencilState(&depthStencildesc, &m_dss);
	if (FAILED(hr))
	{
		throw std::exception("DepthBuffer not created successfully");
	}
}

void SwapChain::SetFillMode(D3D11_FILL_MODE fill_mode)
{
	fillMode = fill_mode;
	UpdateRasterizerState();
}

void SwapChain::SetCullMode(D3D11_CULL_MODE cull_mode)
{
	cullMode = cull_mode;
	UpdateRasterizerState();
}

bool SwapChain::UpdateRasterizerState()
{
	ID3D11Device* device = m_system->m_d3d_device;

	D3D11_RASTERIZER_DESC rastDesc;
	ZeroMemory(&rastDesc, sizeof(D3D11_RASTERIZER_DESC));
	rastDesc.FillMode = fillMode;
	rastDesc.CullMode = cullMode;
	HRESULT hr = device->CreateRasterizerState(&rastDesc, &m_rasterizer_state);

	if (FAILED(hr))
	{
		throw std::exception("Rasterizer state not updated");
		return false;
	}

	return true;
}

bool SwapChain::present(bool vsync)
{
	m_swap_chain->Present(vsync, NULL);

	return true;
}
