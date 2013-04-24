#include "LuaApi.h"
#include "CoreSystem.h"

extern "C" {
  #include "lua.h"
}
#include "luabind/luabind.hpp"

#include "iostream"


LuaApi::LuaApi(lua_State* state)
{
	m_luaState= state;
}

LuaApi::~LuaApi()
{
}

void LuaApi::RegisterToLua()
{
	luabind::module(m_luaState) [
		luabind::def("print", &lApi::Print)
	];

}

void lApi::Print(std::string str)
{
	std::cout << str << std::endl;
}
