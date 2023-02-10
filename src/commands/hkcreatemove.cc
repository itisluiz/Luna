#include <commands/hkcreatemove.hh>
#include <features/printer.hh>
#include <settings.hh>

namespace commands::hkcreatemove
{
	void callback(const std::vector<std::string_view>& tokens)
	{
		if (tokens.size() >= 2)
		{
			if (tokens[1] == "0")
				settings::luaHkCreateMove.clear();
			else
				settings::luaHkCreateMove = tokens[1];
		}

		console << "Lua hkcreatemove: " << (!settings::luaHkCreateMove.empty() ? sdk::Color{ 100, 255, 100, 255 } : sdk::Color{ 255, 100, 100, 255 }) << (!settings::luaHkCreateMove.empty() ? settings::luaHkCreateMove : "Off") << '\n';
	}

	std::pair<std::string, decltype(&callback)> commandPair()
	{
		return { "luna_createmove_hk", callback };
	}
}
