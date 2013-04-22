#ifndef _CORESYSTEM_H_
#define _CORESYSTEM_H_

extern "C" {
  #include "lua.h"
  #include "lualib.h"
  #include "lauxlib.h"
}
#include "luabind/luabind.hpp"

#include "GenWindow.h"
#include "IRenderer.h"

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

private:
	GenWindow* m_window;
	IRenderer* m_renderer;
	lua_State *m_LuaState;
};
#endif