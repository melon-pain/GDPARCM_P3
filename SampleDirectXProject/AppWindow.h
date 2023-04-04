#pragma once

#include <vector>

#include "Window.h"
#include "InputListener.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
//#include "IMObjectProperty.h"
#include "UIManager.h"

class GameObject;
class AppWindow: public Window
{
public:
	AppWindow();
	~AppWindow() override;

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
	virtual void onFocus() override;
	virtual void onKillFocus() override;

	static AppWindow* sharedInstance;

	static AppWindow* Get();

	static void Initialize();

	void update();

public:
	SwapChain* GetSwapChain() const;
private:
	SwapChain * m_swap_chain;

private:
	class SceneCamera* sceneCamera = nullptr;

	//IMObjectProperty* imObjProp;
};

