#ifndef LUNA_IMPORTS_HH
#define LUNA_IMPORTS_HH
#include <sdk/luaifaces.hh>
#include <sdk/source.hh>
#include <sdk/lua.hh>

namespace imports
{
	extern sdk::IVEngineClient* iEngineClient;
	extern sdk::ILuaShared* iLuaShared;
	extern sdk::luaL_loadstring* lua_loadstring;
	extern sdk::luaL_loadfile* lua_loadfile;
}

bool loadImports();

#endif