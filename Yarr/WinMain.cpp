#include "CoreSystem.h"
#include "Window32.h"
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdShow)
{ 
	CoreSystem* System;
	System = new CoreSystem;
	if(!System)
	{
		return 0;
	}
	if(System->Initialize())
	{
		System->Run();
	}
	System->Shutdown();
	delete System;
	System = 0;
	return 0;
}