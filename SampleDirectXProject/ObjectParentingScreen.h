#pragma once
#include "UIScreen.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include <vector>
#include <map>
#include <unordered_map>
#include <iostream>

using namespace std;

class ObjectParentingScreen : public UIScreen
{
public:
	ObjectParentingScreen();
	~ObjectParentingScreen();
	void DrawUI() override;
private:
	void CreateComboObj(GameObject* obj);
};

