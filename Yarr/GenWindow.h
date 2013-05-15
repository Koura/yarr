#pragma once

class GenWindow
{
public:
	GenWindow(){};
	GenWindow(const GenWindow&){};
	virtual ~GenWindow(){};
	virtual bool Create(const wchar_t*, int&, int&) = 0;
	virtual void Shutdown() = 0;
	virtual bool Update() = 0;
};



