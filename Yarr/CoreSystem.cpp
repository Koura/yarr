#include "CoreSystem.h"
#include "Window32.h"

CoreSystem::CoreSystem()
{
	m_window = 0;
	m_renderer = 0;
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
	if(m_renderer)
	{
		delete m_renderer;
		m_renderer = 0;
	}
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
	bool done;
	done = false;
	while(!done) 
	{
		if(!m_window->Update()) 
		{
			done = true;
		}
	}
}