#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "UIScreen.h"
#include "InputSystem.h"
#include "EngineMathConstants.h"
#include <iostream>

class ObjectProperty : public UIScreen
{
public:
	ObjectProperty();
	~ObjectProperty();
	void DrawUI() override;
private:
	float* pos;
	float* rot;
	float* scale;
};

