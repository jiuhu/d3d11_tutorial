#pragma once

#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>
//--------------------------------------------------------------------

class System
{
public:
	
	/*
		Constructor with initialization process.
	*/
	System(UINT width, UINT height);

	/*
		Destructor.
	*/
	~System();

	/*
		This function is called to check is the window still running.
	*/
	bool isRunning();

	/*
		This function is called to end the window.
	*/
	void quit();

	/*
		This function is called to return the instance handle.
	*/
	HINSTANCE getInstanceHandle();

	/*
		This function is called to return the window handle.
	*/
	HWND getWindowHandle();

	/*
		This function is called to modify the window's name.
	*/
	void changeWindowName(const char * const name);

	/*
		This function is called to return the window's name.
	*/
	void getWindowName(char * const name) const;

	/*
		This function is called to return the window's size.
	*/
	void getWindowSize(int &width, int &height);

	/*
		This function is called to toggle window's visibility.
	*/
	void toggleVisibility(bool isVisible);

private:
	
	//	Window handle.
	HWND m_hWnd;
		
	/*
		This function is called to create window.
	*/
	bool create();
		
	/*
		The window procedure.
	*/
	static LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};
//--------------------------------------------------------------------

inline void System::quit()
{
	PostQuitMessage(0);
}
//--------------------------------------------------------------------

inline HINSTANCE System::getInstanceHandle()
{
	return GetModuleHandle(NULL);
}
//--------------------------------------------------------------------

inline HWND System::getWindowHandle()
{
	return m_hWnd;
}
//--------------------------------------------------------------------

inline void System::changeWindowName(const char * const name)
{
	SetWindowText(m_hWnd, name);
}
//--------------------------------------------------------------------

inline void System::getWindowName(char * const name) const
{
	GetWindowText(m_hWnd, name, 32);
}
//--------------------------------------------------------------------

inline void System::getWindowSize(int &width, int &height)
{
	RECT windowedRect;
	GetWindowRect(m_hWnd, &windowedRect);
	width = windowedRect.right - windowedRect.left;
	height = windowedRect.bottom - windowedRect.top;
}
//--------------------------------------------------------------------

inline void System::toggleVisibility(bool isVisible)
{
	ShowWindow(m_hWnd, isVisible);
}
//--------------------------------------------------------------------