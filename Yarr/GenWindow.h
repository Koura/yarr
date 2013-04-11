#ifndef _GENWINDOW_H_
#define _GENWINDOW_H_
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

#endif

