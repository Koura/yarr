#include "CoreSystem.h"
#include "Window32.h"
#include "D3D10Class.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdShow)
{ 
	CoreSystem* System;
	Window32* window32;
	D3D10Class* d3d10;
	System = new CoreSystem;
	int screenWidth, screenHeight;
	screenWidth = 800;
	screenHeight = 600;
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
	if(!System->Initialize(screenWidth, screenHeight))
	{
		return 0;
	}
	d3d10 = new D3D10Class();
	d3d10->SetHWND(window32->GetHWND());
	System->SetGraphics(d3d10);
	if(System->InitGraphics(screenWidth, screenHeight))
	{
		System->Run();
	}
	System->Shutdown();
	delete System;
	System = 0;
	return 0;
}