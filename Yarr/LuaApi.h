#pragma once

#include "string"

extern "C" {
  #include "lua.h"
}

class LuaApi
{
public:
	explicit LuaApi(lua_State*);
	~LuaApi();
	void RegisterToLua();
private:
	lua_State* m_luaState;
};

namespace lApi{
	void Print(std::string);
}
