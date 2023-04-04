#include "Camera.h"
#include "AppWindow.h"

#include <iostream>

Camera::Camera() = default;

SimpleMath::Matrix Camera::GetViewMatrix() const
{
	return viewMatrix;
}

SimpleMath::Matrix Camera::GetProjectionMatrix() const
{
	return projectionMatrix;
}

SimpleMath::Ray Camera::ScreenPointToRay(SimpleMath::Vector3 point)
{
	float width, height;
	AppWindow::Get()->GetWindowSize(width, height);

	float x = (((2.0f * point.x) / width) - 1.0f) / projectionMatrix._11;
	float y = ((((2.0f * point.y) / height) - 1.0f) * -1.0f) / projectionMatrix._22;

	SimpleMath::Matrix view = viewMatrix;
	SimpleMath::Matrix invView = view.Invert();

	SimpleMath::Ray r;
	r.position = SimpleMath::Vector3::Zero;
	r.direction = SimpleMath::Vector3(x, y, -1);

	r.position = SimpleMath::Vector3::Transform(r.position, invView);
	r.direction = SimpleMath::Vector3::TransformNormal(r.direction, invView);
	r.direction.Normalize();

	return r;
}

void Camera::SetViewMatrix(const SimpleMath::Matrix& matrix)
{
	viewMatrix = matrix;
}

void Camera::SetCameraProjection(const CameraProjectionType& projection)
{
	float width, height;
	AppWindow::Get()->GetWindowSize(width, height);

	switch (projection)
	{
	case CameraProjectionType::Orthographic:
		projectionMatrix = SimpleMath::Matrix::CreateOrthographic(width / orthoSize, height / orthoSize, orthoNearPlane, orthoFarPlane);
		break;
	case CameraProjectionType::Perspective:
		projectionMatrix = SimpleMath::Matrix::CreatePerspectiveFieldOfView(fov, width / height, zNearPlane, zFarPlane);
		break;
	}
}
