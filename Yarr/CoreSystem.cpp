#include "CoreSystem.h"

extern "C" {
  #include "lua.h"
  #include "lualib.h"
  #include "lauxlib.h"
}
#include "luabind/luabind.hpp"


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
	luaL_openlibs(m_LuaState);
	luabind::open(m_LuaState);
	m_luaApi = new LuaApi(m_LuaState);
	m_luaApi->RegisterToLua();
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
	if(m_LuaState)
	{
		lua_close(m_LuaState);
		m_LuaState = 0;
	}
	if(m_luaApi)
	{
		m_luaApi->~LuaApi();
		m_luaApi = 0;
	}
	return;
}

void CoreSystem::Run()
{
	Reload();
	bool done;
	done = false;
	while(!done) 
	{
		Reload();
		luabind::call_function<void>(m_LuaState, "update");

		if(!m_window->Update()) 
		{
			done = true;
		}
	}
}

void CoreSystem::Reload()
{
	
	luaL_dofile(
		m_LuaState,
		"../Game/init.lua"
	);
	luaL_dofile(
		m_LuaState,
		"../Game/update.lua"
	);
	luabind::call_function<void>(m_LuaState, "init");
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


