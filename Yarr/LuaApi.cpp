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
#include "Scene.h"

void LuaApi::RegisterToLua()
{
	luabind::module(m_luaState) [
		luabind::def("print", &lApi::Print)
	];
	luabind::module(m_luaState) [	//TODO: find out how to add overloads for static static functions
		luabind::def("printi", &lApi::Printi)
	];
	luabind::module(m_luaState) [
		luabind::class_<Entity>("Entity")
		.def(luabind::constructor<>())
		.def("SetPosition", &Entity::SetPosition)
		.def("GetPosition", &Entity::GetPosition)
		.def("GetName", &Entity::GetName)
	];
	luabind::module(m_luaState) [
		luabind::class_<POSITION>("POSITION")
			.def_readwrite("x", &POSITION::x)
			.def_readwrite("y", &POSITION::y)
			.def_readwrite("z", &POSITION::z)
	];
	luabind::module(m_luaState) [
		luabind::class_<Scene>("Scene")
		.def(luabind::constructor<>())
		.def("NewEntity", (Entity* (Scene::*)(void))&Scene::NewEntity)
	];
}

void lApi::Print(std::string str)
{
	std::cout << str << std::endl;
}

void lApi::Printi(int i)
{
	std::cout << i << std::endl;
}
