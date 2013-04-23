#ifndef _CORESYSTEM_H_
#define _CORESYSTEM_H_


#include "GenWindow.h"
#include "IRenderer.h"
#include "LuaApi.h"

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
	void SetGraphics();
	void SetGraphics(IRenderer*);
	bool InitGraphics(int, int);
	void Reload();

private:
	GenWindow* m_window;
	IRenderer* m_renderer;
	lua_State* m_LuaState;
	LuaApi* m_luaApi;
};
#endif