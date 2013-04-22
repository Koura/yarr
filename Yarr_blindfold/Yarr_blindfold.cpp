// Yarr_blindfold.cpp : Defines the entry point for the console application.
//

#include "CoreSystem.h"
#include "ConsoleWindow.h"

int main(int argc, char* argv[])
{
	CoreSystem System;
	ConsoleWindow cw;
	System.SetWindow(&cw);
	System.Initialize(0,0);
	System.Run();
	return 0;
}

