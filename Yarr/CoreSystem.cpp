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

bool CoreSystem::Initialize(int screenWidth, int screenHeight)
{
	if(!m_window->Create(L"YARR", screenWidth, screenHeight))
	{
		return false;
	}
	return true;
}

void CoreSystem::Shutdown()
{
	if(m_renderer)
	{
		m_renderer->Shutdown();
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

void CoreSystem::SetWindow(GenWindow* genWin)
{
	m_window = genWin;
}

void CoreSystem::SetGraphics(IRenderer* iRenderer)
{
	m_renderer = iRenderer;
}

bool CoreSystem::InitGraphics(int screenWidth, int screenHeight)
{
	if(!m_renderer->Initialize(screenWidth, screenHeight))
	{
		return false;
	}
}
