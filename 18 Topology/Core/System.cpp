#include "System.h"
#include "Input.h"
#include "D3D11/DxDevices.h"
#include "Utilities/Debug.h"
//--------------------------------------------------------------------

#define WINDOW_TITLE "Direct3D Window"
//--------------------------------------------------------------------
	
System::System()
	:	m_hWnd(nullptr)
{
	//	Empty
}
//--------------------------------------------------------------------

System::System(UINT width, UINT height)
	:	m_hWnd(nullptr)
{
	init(width, height);
}
//--------------------------------------------------------------------

System::~System()
{
	UnregisterClass(WINDOW_TITLE, GetModuleHandle(NULL));
	
	m_hWnd = nullptr;
		
	Input::release();

	Devices::release();
}
//--------------------------------------------------------------------

bool System::init(UINT width, UINT height)
{
	detectMemoryLeak();

	//--------------------------------
	//	Initialize window
	//--------------------------------

	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize			= sizeof(WNDCLASSEX);
	wc.hInstance		= GetModuleHandle(NULL);
	wc.lpfnWndProc		= WindowProcedure;
	wc.lpszClassName	= WINDOW_TITLE;
	wc.style			= CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	m_hWnd = CreateWindowEx(0, WINDOW_TITLE, WINDOW_TITLE, WS_VISIBLE | WS_OVERLAPPEDWINDOW,
								0, 0, width, height, NULL, NULL, wc.hInstance, NULL);
		

	return Devices::get()->init(m_hWnd);
		

	//--------------------------------
	//	End initialization
	//--------------------------------
}
//--------------------------------------------------------------------

bool System::isRunning()
{
	static MSG msg;
	//while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT) return false;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	Input::get()->update(m_hWnd);

	return true;
}
//--------------------------------------------------------------------
	
LRESULT WINAPI System::WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static WinInputDevice * input = Input::get();

	switch(msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;

		default:
			input->setKeyboardPressed((char)wParam);
			break;
		}
		break;

	//case WM_MOUSEMOVE:
	//	input->mouseMove(LOWORD(lParam), HIWORD(lParam));
	//	break;
			
	case WM_MOUSEWHEEL:            
		input->setMouseWheel((short)HIWORD(wParam) / 120);
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------