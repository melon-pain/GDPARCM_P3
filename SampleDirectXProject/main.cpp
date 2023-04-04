#include "AppWindow.h"
#include <iostream>

#include "CameraManager.h"

int main()
{
	AppWindow::Initialize();
	CameraManager::Initialize();
	AppWindow* window = AppWindow::Get();

	if (window->init())
	{
		while (window->IsRunning())
		{
			window->broadcast();
		}
	}

	return 0;
}
