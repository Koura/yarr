#pragma once
#include "GenWindow.h"
class ConsoleWindow :
	public GenWindow
{
public:
	ConsoleWindow(void){};
	virtual ~ConsoleWindow(void){};
	virtual bool Create(const wchar_t*, int&, int&);
	virtual void Shutdown();
	virtual bool Update();
};

