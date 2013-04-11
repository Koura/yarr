#ifndef _WINDOW32_H_
#define _WINDOW32_H_


#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "GenWindow.h"

class Window32 : public GenWindow
{
public:
	Window32();
	Window32(const Window32&);
	~Window32();
	bool Create(const wchar_t*, int&, int&);
	void Shutdown();
	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);
	bool Update();

private:
	LPCWSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;
};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
static Window32* ApplicationHandle = 0;

#endif