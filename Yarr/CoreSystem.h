#pragma once

#include "GenWindow.h"
#include "IRenderer.h"
#include "Scene.h"
class ModelFactory;

class LuaApi;
extern "C" {
  #include "lua.h"
}

class CoreSystem
{
public:
	CoreSystem();
	CoreSystem(const CoreSystem&);
	~CoreSystem();
	bool Initialize(int, int);
	void Shutdown();
	void Run();
	void SetWindow(GenWindow*);
	void ReloadScripts();
	void SetGraphics(IRenderer*);
	bool InitGraphics(int, int);
	void InitScene(ModelFactory*);
	void Reload();

private:
	GenWindow* m_window;
	IRenderer* m_renderer;
	lua_State* m_LuaState;
	LuaApi* m_luaApi;
	Scene* m_scene;
};