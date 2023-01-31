#include <commands/unload.hh>
#include <windows/entry.hh>

namespace commands::unload
{
	void callback(const std::vector<std::string_view>& tokens)
	{
		unloadLibrary(0);
	}

	std::pair<std::string, decltype(&callback)> commandPair()
	{
		return { "luna_unload", callback };
	}
}
