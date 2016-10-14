#pragma once

#ifndef WIN32_LEAN_AND_MEAN
	#define WIN32_LEAN_AND_MEAN 1
#endif
#include <windows.h>
#include "Utilities/Singleton.h"
//--------------------------------------------------------------------

class WinInputDevice
{
public:

	struct Point2
	{
		Point2():x(0), y(0){}
		int x;
		int y;
	};

	/*
		Constructor.
	*/
	WinInputDevice();

	/*
		This function is called to verify a particular key press status.
	*/
	bool isKeyOnPress(char key) const;

	/*
		This function is called to verify a particular key holding status.
	*/
	bool isKeyOnHold(char key) const;

	/*
		This function is called to set the pressed keyboard data.
	*/
	void setKeyboardPressed(char key);

	/*
		This function is called to get the pressed keyboard data.
	*/
	char getKeyboardPressed();
	
	/*
		This function is called to get the absolute Point2 position.
	*/
	const Point2& getAbsolutePosition() const;
	
	/*
		This function is called to get the absolute Point2 position at x-axis.
	*/
	int getAbsolutePositionX() const;
	
	/*
		This function is called to get the absolute Point2 position at y-axis.
	*/
	int getAbsolutePositionY() const;

	/*
		This function is called to get the absolute Point2 position.
	*/
	void getAbsolutePosition(int &x, int &y) const;
	
	/*
		This function is called to get the relative Point2 position.
	*/
	const Point2& getRelativePosition() const;
	
	/*
		This function is called to get the relative Point2 position at x-axis.
	*/
	int getRelativePositionX() const;
	
	/*
		This function is called to get the relative Point2 position at y-axis.
	*/
	int getRelativePositionY() const;

	/*
		This function is called to get the relative Point2 position.
	*/
	void getRelativePosition(int &x, int &y) const;

	/*
		This function is called to set mouse wheel data.
	*/
	void setMouseWheel(int mouseWheel);

	/*
		This function is called to get the mouse wheel data.
	*/
	int getMouseWheel();

	/*
		This function is called to process the mouse move data.
	*/
	void mouseMove(int x, int y);

	/*
		This function is called to update the input data.
	*/
	void update(HWND hWnd);

private:

	//	The pressed key value.
	char m_keyPressed;

	//	Absolute Point2er on screen position.
	Point2 m_absolutePosition;

	//	Relative Point2er position.
	Point2 m_relativePosition;

	//	Mouse wheel.
	int m_mouseWheel;
};
//--------------------------------------------------------------------

//	Define a global for input device.
typedef Singleton<WinInputDevice> Input;
//--------------------------------------------------------------------

inline bool WinInputDevice::isKeyOnPress(char key) const
{
	return ((GetAsyncKeyState(key) & 0x0001) != 0);
}
//--------------------------------------------------------------------

inline bool WinInputDevice::isKeyOnHold(char key) const
{
	return ((GetAsyncKeyState(key) & 0x8000) != 0);
}
//--------------------------------------------------------------------

inline void WinInputDevice::setKeyboardPressed(char key)
{
	m_keyPressed = key;
}
//--------------------------------------------------------------------

inline char WinInputDevice::getKeyboardPressed()
{
	char tmp = m_keyPressed;
	m_keyPressed = NULL;
	return tmp;
}
//--------------------------------------------------------------------

inline const WinInputDevice::Point2& WinInputDevice::getAbsolutePosition() const
{
	return m_absolutePosition;
}
//--------------------------------------------------------------------

inline int WinInputDevice::getAbsolutePositionX() const
{
	return m_absolutePosition.x;
}
//--------------------------------------------------------------------

inline int WinInputDevice::getAbsolutePositionY() const
{
	return m_absolutePosition.y;
}
//--------------------------------------------------------------------

inline void WinInputDevice::getAbsolutePosition(int &x, int &y) const
{
	x = m_absolutePosition.x;
	y = m_absolutePosition.y;
}
//--------------------------------------------------------------------

inline const WinInputDevice::Point2& WinInputDevice::getRelativePosition() const
{
	return m_relativePosition;
}
//--------------------------------------------------------------------

inline int WinInputDevice::getRelativePositionX() const
{
	return m_relativePosition.x;
}
//--------------------------------------------------------------------

inline int WinInputDevice::getRelativePositionY() const
{
	return m_relativePosition.y;
}
//--------------------------------------------------------------------

inline void WinInputDevice::getRelativePosition(int &x, int &y) const
{
	x = m_relativePosition.x;
	y = m_relativePosition.y;
}
//--------------------------------------------------------------------

inline void WinInputDevice::setMouseWheel(int mouseWheel)
{
	m_mouseWheel = mouseWheel;
}
//--------------------------------------------------------------------

inline int WinInputDevice::getMouseWheel()
{
	int tmp = m_mouseWheel;
	m_mouseWheel = 0;
	return tmp;
}
//--------------------------------------------------------------------