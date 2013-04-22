#include "CoreSystem.h"

//temporary
#include <iostream>
#include <string>

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
	//luabind
	m_LuaState = luaL_newstate();
	luabind::open(m_LuaState);

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
	luaL_dostring(
    m_LuaState,
    "function add(first, second)\n"
    "  return first + second\n"
    "end\n"
  );
 
  std::cout << "Result: "
       << luabind::call_function<int>(m_LuaState, "add", 2, 3)
       << std::endl;
	//
	bool done;
	done = false;
	while(!done) 
	{
		if(!m_window->Update()) 
		{
			done = true;
		}
	}
	lua_close(m_LuaState);
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
