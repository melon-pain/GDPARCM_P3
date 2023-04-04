
#include "AppWindow.h"

#include "EngineTime.h"
#include "InputSystem.h"
#include "RenderSystem.h"

#include "GameObjectManager.h"
#include "GameObject.h"
#include "MeshComponent.h"
#include "TransformComponent.h"
#include "RotationMovementComponent.h"

#include "CameraManager.h"
#include "CameraComponent.h"

#include "SceneCamera.h"
#include "EngineBackend.h"
#include "ActionHistory.h"

// IMGUI
#include <ctype.h> 
#include <limits.h> 
#include <math.h> 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <Windows.h>

AppWindow::AppWindow()
{
}

AppWindow::~AppWindow()
{
}

AppWindow* AppWindow::sharedInstance = nullptr;

AppWindow* AppWindow::Get()
{
	return sharedInstance;
}

void AppWindow::Initialize()
{
	sharedInstance = new AppWindow();
	
}

void AppWindow::update()
{
}

SwapChain* AppWindow::GetSwapChain() const
{
	return m_swap_chain;
}

void AppWindow::onCreate()
{
	Window::onCreate();
	srand(time(NULL));

	EngineBackend::Initialize();
	ActionHistory::Initialize();
	
	sceneCamera = new SceneCamera();
	InputSystem::get()->addListener(sceneCamera);
	sceneCamera->GetTransform()->SetPosition(SimpleMath::Vector3(0.0f, 0.0f, 2.5f));

	GraphicsEngine::create();
	RECT rc = this->getClientWindowRect();
	m_swap_chain=GraphicsEngine::get()->getRenderSystem()->createSwapChain(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setRenderTargets(this->m_swap_chain);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setRenderState(this->m_swap_chain);

	GameObjectManager::Initialize();
	UIManager::Initialize(this->m_hwnd);
}

void AppWindow::onUpdate()
{
	Window::onUpdate();

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0.5f, 0.5f,0.5f, 1);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->clearDepthStencilView(this->m_swap_chain);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setRenderTargets(this->m_swap_chain);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setDepthStencilState(this->m_swap_chain);

	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	const float deltaTime = EngineTime::getDeltaTime();

	// Update scene camera
	sceneCamera->Update(deltaTime);

	EngineBackend* backend = EngineBackend::Get();
	GameObjectManager::Get()->Update();

	if (backend->GetMode() == EditorMode::PLAY) {
		//GameObjectManager::Get()->Update();
	}
	else if (backend->GetMode() == EditorMode::EDITOR) {
		//GameObjectManager::Get()->Update();

	}
	else if (backend->GetMode() == EditorMode::PAUSED) {
		if (backend->InsideFrameStep()) {
			backend->EndFrameStep();
		}
	}

	// Render ImGui
	//imObjProp->Render(sceneCamera->GetSelectedObj());

	// Draw UI
	UIManager::Get()->DrawAllUI();
	InputSystem::get()->update();

	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();

	EngineBackend::Destroy();

	GraphicsEngine::get()->release();
	InputSystem::get()->removeListener(sceneCamera);

	delete sceneCamera;
}

void AppWindow::onFocus()
{
	InputSystem::get()->addListener(sceneCamera);
}

void AppWindow::onKillFocus()
{
	InputSystem::get()->removeListener(sceneCamera);
}
