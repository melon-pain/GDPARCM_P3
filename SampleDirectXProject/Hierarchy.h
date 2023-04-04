#pragma once
#include "UIScreen.h"
#include "GameObjectManager.h"
#include "GameObject.h"

#include <vector>

using namespace std;

class Hierarchy : public UIScreen
{
public:
	Hierarchy();
	~Hierarchy();
	void DrawUI() override;
private:
	void SetupNode(GameObject* obj);
};

