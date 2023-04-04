#pragma once
#include "Component.h"

class Camera;
class CameraComponent : public Component
{
public:
	~CameraComponent() override;

public:
	void Start() override;
	void Update(float deltaTime) override;

public:
	void SetActive() const;

protected:
	void UpdateViewMatrix();

protected:
	Camera* camera = nullptr;

public:
	Camera* GetCamera() const;
};
