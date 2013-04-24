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

#include "Entity.h"

void LuaApi::RegisterToLua()
{
	luabind::module(m_luaState) [
		luabind::def("print", &lApi::Print)
		
	];
	luabind::module(m_luaState) [
		luabind::class_<Entity>("Entity")
		.def(luabind::constructor<>())
		.def("SetPosition", &Entity::SetPosition)
		//.def("GetPosition", &Entity::GetPosition)
		//.def("SetPosition", &Entity::SetPosition)
	];
}

void lApi::Print(std::string str)
{
	std::cout << str << std::endl;
}
