#ifndef LUNA_SDK_LUA_HH
#define LUNA_SDK_LUA_HH

namespace sdk
{
	class lua_State;
	class lua_Debug;
	using luaL_loadstring = int(lua_State* L, const char* s);
	using luaL_loadfile = int(lua_State* L, const char* filename);
}

#endif