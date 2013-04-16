#include "CoreSystem.h"
#include "Window32.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdShow)
{ 
	CoreSystem* System;
	Window32* window32;
	System = new CoreSystem;
	if(!System)
	{
		return 0;
	}
	window32 = new Window32();
	if(!window32)
	{
		return 0;
	}
	System->SetWindow(window32);
	if(!System->Initialize())
	{
		return 0;
	}
	if(System->InitGraphics())
	{
		System->Run();
	}
	System->Shutdown();
	delete System;
	System = 0;
	return 0;
}