#pragma once
#define NOMINMAX
#include <Windows.h>

class Window
{
public:
	Window();
	//Initialize the window
	bool init();
	bool broadcast();
	//Release the window
	bool release();
	bool IsRunning();

	RECT getClientWindowRect();
	void setHWND(HWND hwnd);


	//EVENTS
	virtual void onCreate();
	virtual void onUpdate();
	virtual void onDestroy();

	virtual void onFocus();
	virtual void onKillFocus();

	virtual ~Window();

public:
	float GetWidth() const;
	float GetHeight() const;
	void GetWindowSize(float& width, float& height) const;

	const HWND& GetWindowHandle() const;

protected:
	HINSTANCE m_hinstance;
	HWND m_hwnd;
	bool m_is_run;
};

