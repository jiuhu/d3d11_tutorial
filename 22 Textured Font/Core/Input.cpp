#include "Input.h"
//--------------------------------------------------------------------

WinInputDevice::WinInputDevice()
	:	m_keyPressed(0),
		m_absolutePosition(),
		m_relativePosition(),
		m_mouseWheel(0)
{
	//	Empty
}
//--------------------------------------------------------------------

void WinInputDevice::mouseMove(int x, int y)
{
	m_relativePosition.x = x - m_absolutePosition.x;
	m_relativePosition.y = -1 * (y - m_absolutePosition.y);

	m_absolutePosition.x = x;
	m_absolutePosition.y = y;
}
//--------------------------------------------------------------------

void WinInputDevice::update(HWND hWnd)
{
	static POINT mousePosition;
	GetCursorPos(&mousePosition);
	ScreenToClient(hWnd, &mousePosition);
	
	mouseMove(mousePosition.x, mousePosition.y);
}
//--------------------------------------------------------------------