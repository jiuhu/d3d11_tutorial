#include "Core/System.h"
#include "D3D11/DxDevices.h"
#include "Scene.h"
//--------------------------------------------------------------------

#ifdef DEBUG
int main()
#else
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
#endif
{
	System sys(800, 600);	
	DxDevices * devices = Devices::get();

	Scene scene;
	
	if (scene.init(devices))
	{
		while(sys.isRunning())
		{
			scene.update();

			devices->clear();

			scene.draw();
			
			devices->swap();
		};
	}
	else
	{
		sys.toggleVisibility(false);
		system("pause");
	}
	
	return 0;
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------