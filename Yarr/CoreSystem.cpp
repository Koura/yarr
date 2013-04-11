#include "CoreSystem.h"
#include "Window32.h"

CoreSystem::CoreSystem()
{
	m_window = 0;
}

CoreSystem::CoreSystem(const CoreSystem& other)
{
}

CoreSystem::~CoreSystem()
{
}

bool CoreSystem::Initialize()
{
	int x, y;
	m_window = new Window32;
	if(!m_window)
	{
		return false;
	}
	x = 800;
	y = 600;
	if(!m_window->Create(L"YARR", x, y))
	{
		return false;
	}
	return true;
}

void CoreSystem::Shutdown()
{
	if(m_window)
	{
		m_window->Shutdown();
		delete m_window;
		m_window = 0;
	}
	return;
}

void CoreSystem::Run()
{
	m_window->Update();
}