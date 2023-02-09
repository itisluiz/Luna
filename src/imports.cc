#include <imports.hh>
#include <hooking.hh>
#include <map>
#include <windows/entry.hh>
#include <windows/msgbox.hh>

namespace imports
{
	sdk::IVEngineClient* iEngineClient;
	sdk::IBaseClientDLL* iBaseClient;
	sdk::IClientMode* iClientMode;
	sdk::ISurface* iSurface;
	sdk::ILuaShared* iLuaShared;
	sdk::luaL_loadstring* lua_loadstring;
	sdk::luaL_loadfile* lua_loadfile;
}

static HMODULE acquireModule(const std::string& moduleName, size_t retryCount = 15, DWORD delay = 250)
{
	static std::map<std::string, HMODULE> acquiredModules;

	if (acquiredModules.find(moduleName) == acquiredModules.end())
	{
		HMODULE hModule{ GetModuleHandleA(moduleName.c_str()) };
		for (uint8_t retry{ 0 }; retry < retryCount && !hModule; ++retry, hModule = GetModuleHandleA(moduleName.c_str()))
			Sleep(delay);

		if (!hModule)
			msgbox::message << "Failed to get module handle to " << moduleName << " (" << GetLastError() << ')' << msgbox::ShowOptions(MB_ICONERROR);

		acquiredModules[moduleName] = hModule;
	}

	return acquiredModules[moduleName];
}

template<typename T>
static bool acquireExport(T*& importOut, const std::string& moduleName, const std::string& exportName)
{
	T* importResult{ reinterpret_cast<T*>(GetProcAddress(acquireModule(moduleName), exportName.c_str()))};

	if (!importResult)
	{
		msgbox::message << "Failed to get export '" << exportName << "' from " << moduleName << " (" << GetLastError() << ')' << msgbox::ShowOptions(MB_ICONERROR);
		return false;
	}

	importOut = importResult;
	return true;
}

template<typename T>
static bool acquireInterface(T*& interfaceOut, const std::string& moduleName, const std::string& interfaceName)
{
	static std::map<std::string, sdk::CreateInterface*> acquiredCreateInterfaces;

	if (acquiredCreateInterfaces.find(moduleName) == acquiredCreateInterfaces.end())
	{
		sdk::CreateInterface* createInterface;
		acquireExport(createInterface, moduleName, "CreateInterface");

		if (!createInterface)
			return false;

		acquiredCreateInterfaces[moduleName] = createInterface;
	}

	T* interfaceResult{ reinterpret_cast<T*>(acquiredCreateInterfaces[moduleName](interfaceName.c_str(), nullptr)) };

	if (!interfaceResult)
	{
		msgbox::message << "Failed to get interface '" << interfaceName << "' from " << moduleName << msgbox::ShowOptions(MB_ICONERROR);
		return false;
	}

	interfaceOut = interfaceResult;
	return true;
}

static sdk::ILuaInterface* getLuaInterface(sdk::State state, size_t retryCount)
{
	sdk::ILuaInterface* luaInterfaceResult;

	for (uint8_t retry{ 0 }; !(luaInterfaceResult = imports::iLuaShared->GetLuaInterface(sdk::State::MENU)) && retry < retryCount; ++retry)
		Sleep(250);

	if (!luaInterfaceResult)
		msgbox::message << "Failed to get Lua interface interface #" << state << msgbox::ShowOptions(MB_ICONERROR);

	return luaInterfaceResult;
}

static bool acquireClientMode()
{
	bool success{ true };
	uintptr_t hudProcessInput{ reinterpret_cast<uintptr_t>(vFuncAddress(imports::iBaseClient, 10)) };

#ifdef _WIN64
	if (std::memcmp(reinterpret_cast<void*>(hudProcessInput), "\x48\x8B\x0D", 3))
		success = false;
	else
	{
		int32_t* clientModeOffset = reinterpret_cast<int32_t*>(hudProcessInput + 3);
		imports::iClientMode = *reinterpret_cast<sdk::IClientMode**>(hudProcessInput + 7 + *clientModeOffset);
	}
#else
	if (std::memcmp(reinterpret_cast<void*>(hudProcessInput), "\x55\x8B\xEC", 3))
		success = false;
	else
		imports::iClientMode = **reinterpret_cast<sdk::IClientMode***>(hudProcessInput + 5);
#endif

	if (!success)
		msgbox::message << "Failed to get interface 'IClientMode' from client.dll " << msgbox::ShowOptions(MB_ICONERROR);

	return success;
}

bool loadImports()
{
	if (!acquireInterface(imports::iEngineClient, "engine.dll", ENGINECLIENT_IFACESTR))
		return false;

	if (!acquireInterface(imports::iBaseClient, "client.dll", BASECLIENT_IFACESTR))
		return false;

	if (!acquireInterface(imports::iSurface, "vguimatsurface.dll", MATSURFACE_IFACESTR))
		return false;

	if (!acquireInterface(imports::iLuaShared, "lua_shared.dll", LUASHARED_IFACESTR))
		return false;

	if (!acquireExport(imports::lua_loadfile, "lua_shared.dll", "luaL_loadfile"))
		return false;

	if (!acquireExport(imports::lua_loadstring, "lua_shared.dll", "luaL_loadstring"))
		return false;
	
	if (!acquireClientMode())
		return false;

	if (!getLuaInterface(sdk::State::MENU, 30))
		return false;

	return true;
}
