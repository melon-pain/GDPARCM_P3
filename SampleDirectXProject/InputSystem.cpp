#include "InputSystem.h"
#include "AppWindow.h"
#include <Windows.h>

InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
}

void InputSystem::update()
{
	POINT current_mouse_pos = {};
	::GetCursorPos(&current_mouse_pos);

	if (m_first_time)
	{
		m_old_mouse_pos = Point(current_mouse_pos.x, current_mouse_pos.y);
		m_first_time = false;
	}

	if (current_mouse_pos.x != m_old_mouse_pos.x || current_mouse_pos.y != m_old_mouse_pos.y)
	{
		auto it = m_set_listeners.begin();
		while (it != m_set_listeners.end()) {
			(*it)->onMouseMove(Point(current_mouse_pos.x, current_mouse_pos.y));
			++it;
		}
	}

	m_old_mouse_pos = Point(current_mouse_pos.x, current_mouse_pos.y);

	if (::GetKeyboardState(m_keys_state))
	{
		for (int i = 0; i < 256; i++)
		{
			// Key down
			if (m_keys_state[i] & 0x80)
			{
				auto it = m_set_listeners.begin();
				while (it != m_set_listeners.end()) {

					if(i == VK_LBUTTON && !lmbConsumed)
					{
						if (m_keys_state[i] != m_old_keys_state[i])
							(*it)->onLeftMouseButtonDown(Point(current_mouse_pos.x, current_mouse_pos.y));
					}
					if (i == VK_RBUTTON)
					{
						if (m_keys_state[i] != m_old_keys_state[i])
							(*it)->onRightMouseButtonDown(Point(current_mouse_pos.x, current_mouse_pos.y));
					}

					(*it)->onKeyDown(i);
					++it;
				}
			}
			// Key up
			else
			{
				if (m_keys_state[i] != m_old_keys_state[i])
				{
					auto it = m_set_listeners.begin();
					while (it != m_set_listeners.end()) {
						if (i == VK_LBUTTON)
						{
							(*it)->onLeftMouseButtonUp(Point(current_mouse_pos.x, current_mouse_pos.y));
						}
						if (i == VK_RBUTTON)
						{
							(*it)->onRightMouseButtonUp(Point(current_mouse_pos.x, current_mouse_pos.y));
						}

						(*it)->onKeyUp(i);
						++it;
					}
				}
			}
		}

		::memcpy(m_old_keys_state, m_keys_state, sizeof(unsigned char) * 256);
	}

	lmbConsumed = false;
}

void InputSystem::addListener(InputListener* listener)
{
	m_set_listeners.insert(listener);
}

void InputSystem::removeListener(InputListener* listener)
{
	m_set_listeners.erase(listener);
}

void InputSystem::setCursorPosition(const Point& point)
{
	::SetCursorPos(point.x, point.y);
}

void InputSystem::showCursor(bool show)
{
	::ShowCursor(show);
}

Point InputSystem::GetMousePositionInWindow() const
{
	POINT current_mouse_window_pos;
	::GetCursorPos(&current_mouse_window_pos);
	::ScreenToClient(AppWindow::Get()->GetWindowHandle(), &current_mouse_window_pos);

	return Point(current_mouse_window_pos.x, current_mouse_window_pos.y);
}

InputSystem* InputSystem::get()
{
	static InputSystem system;
	return &system;
}

void InputSystem::ConsumeLeftMouseButton()
{
	lmbConsumed = true;
}
