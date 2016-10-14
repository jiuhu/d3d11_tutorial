#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>
#include "DxDevices.h"
#include "Font.h"
#include <crtdbg.h>
#include <string>
//--------------------------------------------------------------------
	
DxDevices device;
Font font;
	
std::wstring message = L"Hello World!";
//--------------------------------------------------------------------

void draw()
{
	device.preDraw2D();
	font.drawText(100.0f, 100.0f, L"Hello World!");
	
	font.drawText(100.0f, 150.0f, message.c_str(), message.size());

	font.drawFormattedText(100.0f, 200.0f, L"Hello World x %d", 5);

	device.postDraw2D();

	device.preDraw3D();
	device.postDraw3D();

	//device.clearScreen();
	//device.swap();
}
//--------------------------------------------------------------------

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
		break;

		case WM_KEYDOWN:
			if (wParam == VK_ESCAPE) 
				PostQuitMessage(0);
		break;

		default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

// Main
#ifdef DEBUG
int main()
#else
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
#endif
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// Register windowclass
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));
	wc.cbSize = sizeof(wc);
	wc.lpszClassName = "MyClass";
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	RegisterClassEx(&wc);
	
	HWND hWnd = CreateWindowEx(0, wc.lpszClassName, "D3D11 with D2D", WS_VISIBLE | WS_OVERLAPPEDWINDOW,
									CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, wc.hInstance, NULL);
	

	device.init(hWnd);
	font.init(device.getWriteFactory(), device.getD2DRenderTarget(), L"Arial", 20.0f);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while(msg.message != WM_QUIT) 
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else 
		{
			draw();
		}
	}
	
	// Release
	
	UnregisterClass(wc.lpszClassName, hInstance);
	
	return 0;
}
//--------------------------------------------------------------------