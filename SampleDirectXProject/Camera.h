#pragma once
#include "CameraProjection.h"
#include "SimpleMath.h"

using namespace DirectX;

class Camera
{
public:
	Camera();

public:
	SimpleMath::Matrix GetViewMatrix() const;
	SimpleMath::Matrix GetProjectionMatrix() const;

public:
	SimpleMath::Ray ScreenPointToRay(SimpleMath::Vector3 point);

public:
	void SetViewMatrix(const SimpleMath::Matrix& matrix);

public:
	void SetCameraProjection(const CameraProjectionType& projection);

// Orthographic
protected:
	float orthoSize = 300.0f;
	float orthoNearPlane = 0.0f;
	float orthoFarPlane = 100.0f;

// Perspective
protected:
	float fov = 1.57f;
	float zNearPlane = 0.01f;
	float zFarPlane = 100.0f;

protected:
	SimpleMath::Matrix viewMatrix;
	SimpleMath::Matrix projectionMatrix;
};

