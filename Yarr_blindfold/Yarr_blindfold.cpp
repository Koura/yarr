// Yarr_blindfold.cpp : Defines the entry point for the console application.
//

#include "CoreSystem.h"
#include "ConsoleWindow.h"
#include "Renderer.h"

int main(int argc, char* argv[])
{
	CoreSystem* System;
	Renderer* renderer;
	ConsoleWindow* cw;
	System= new CoreSystem;
	renderer= new Renderer;
	cw=new ConsoleWindow;
	System->SetWindow(cw);
	System->SetGraphics(renderer);
	System->Initialize(0,0);
	System->Run();
	return 0;
}

