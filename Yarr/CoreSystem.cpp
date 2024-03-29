#include "CoreSystem.h"
#include "LuaApi.h"

extern "C" {
  #include "lua.h"
  #include "lualib.h"
}
#include "luabind/luabind.hpp"
#include "Entity.h"

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
	m_scene = new Scene();
	if(!m_scene)
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
	if(m_scene)
	{
		m_scene->Shutdown();
		delete m_scene;
		m_scene = 0;
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
		ReloadScripts(); //move this to lua as soon as possible
		try{
			luabind::call_function<void>(m_LuaState, "update");
		}catch(luabind::error &sError){
			lApi::Print("lua update error");
			ReloadScripts();
		}
		
		if(!m_window->Update()) 
		{
			done = true;
		}
		if(m_renderer)
		{
			m_renderer->Frame();
		}
	}
}

void CoreSystem::ReloadScripts(){
		try{
			Reload();
		}catch(luabind::error &sError){
			lApi::Print("lua reload error");
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
	luabind::globals(m_LuaState)["scene"] = m_renderer->GetScene();
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
	return true;
}

void CoreSystem::InitScene(ModelFactory* modelFactory)
{
	m_scene->Initialize(modelFactory);
	m_renderer->SetScene(m_scene);
}
