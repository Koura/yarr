#include "CoreSystem.h"
#include "Window32.h"

CoreSystem::CoreSystem()
{
	m_window = 0;
	m_renderer = 0;
	m_audio = 0;
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

	if(m_audio)
	{
		delete m_audio;
		m_audio = 0;
	}
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

void CoreSystem::SetWindow(GenWindow* genWin)
{
	m_window = genWin;
}

void CoreSystem::SetGraphics(IRenderer* iRenderer)
{
	m_renderer = iRenderer;
}

bool CoreSystem::InitGraphics()
{
	return true;
}

bool CoreSystem::InitAudio()
{
	if (m_audio->Initialize())
	{
		return true;
	}

	return false;
}
