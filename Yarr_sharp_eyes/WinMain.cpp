#include "CoreSystem.h"
#include "Window32.h"
#include "D3D10Renderer.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdShow)
{ 
	CoreSystem* System;
	Window32* window32;
	D3D10Renderer* d3d10;
	DX10ModelFactory* dx10ModelFactory;
	Scene* scene;
	System = new CoreSystem;
	int screenWidth, screenHeight;
	screenWidth = 800;
	screenHeight = 600;
	if(!System)
	{
		return 1;
	}
	window32 = new Window32;
	if(!window32)
	{
		return 1;
	}
	System->SetWindow(window32);
	if(!System->Initialize(screenWidth, screenHeight))
	{
		return 1;
	}
	d3d10 = new D3D10Renderer;
	if(!d3d10)
	{
		return 1;
	}
	d3d10->SetHWND(window32->GetHWND());
	
	System->SetGraphics(d3d10);
	if(System->InitGraphics(screenWidth, screenHeight))
	{
		dx10ModelFactory = new DX10ModelFactory;
		dx10ModelFactory->SetID3D10Device(d3d10->GetDevice());
		d3d10->SetModelFactory(dx10ModelFactory);
		System->InitScene(dx10ModelFactory);
		System->Run();
	}
	System->Shutdown();
	delete System;
	System = 0;
	return 0;
}