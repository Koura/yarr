#include "Window32.h"

Window32::Window32()
{
}

Window32::Window32(const Window32& other)
{
}

Window32::~Window32()
{
}

LRESULT CALLBACK Window32::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	switch(umsg)
	{
	case WM_KEYDOWN:
		{
			return 0;
		}
	case WM_KEYUP:
		{
			return 0;
		}
	default:
		{
			return DefWindowProc(hwnd, umsg, wparam, lparam);
		}
	}
}

bool Window32::Create(const wchar_t* title, int& screenWidth, int& screenHeight) 
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY;
	ApplicationHandle = this;
	m_hinstance = GetModuleHandle(NULL);
	m_applicationName = (LPWSTR)title;
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hinstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);
	RegisterClassEx(&wc);
	posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth)/2;
	posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight)/2;
	m_hwnd = CreateWindowEx(WS_EX_CONTROLPARENT, m_applicationName, m_applicationName, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE, posX, posY, screenWidth, screenHeight, NULL, NULL, m_hinstance, NULL);
	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);
	return true;
}

void Window32::Shutdown()
{
	DestroyWindow(m_hwnd);
	m_hwnd = NULL;
	UnregisterClass(m_applicationName, m_hinstance);
	m_hinstance = NULL;
	ApplicationHandle = NULL;
	return;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch(umessage)
	{
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}
	default:
		{
			return ApplicationHandle->MessageHandler(hwnd, umessage, wparam, lparam);
		}
	}
}

void Window32::Update() 
{
	Sleep(5000);
}