#pragma once
#include "Point.h"

class InputListener
{
public:
	InputListener()
	{
		
	}

	virtual ~InputListener()
	{

	}

	virtual void onKeyDown(int key) = 0;
	virtual void onKeyUp(int key) = 0;

	virtual void onMouseMove(const Point& delta_mouse) = 0;

	virtual void onLeftMouseButtonDown(const Point& mouse_pos) = 0;
	virtual void onLeftMouseButtonUp(const Point& mouse_pos) = 0;

	virtual void onRightMouseButtonDown(const Point& mouse_pos) = 0;
	virtual void onRightMouseButtonUp(const Point& mouse_pos) = 0;
};