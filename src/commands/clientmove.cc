#include <commands/clientmove.hh>
#include <features/printer.hh>
#include <settings.hh>

namespace commands::clientmove
{
	void callback(const std::vector<std::string_view>& tokens)
	{
		if (tokens.size() >= 2)
		{
			if (tokens[1] == "0")
				settings::luaClientMoveHk.clear();
			else
				settings::luaClientMoveHk = tokens[1];
		}

		console << "Lua clientmove: " << (!settings::luaClientMoveHk.empty() ? sdk::Color{ 100, 255, 100, 255 } : sdk::Color{ 255, 100, 100, 255 }) << (!settings::luaClientMoveHk.empty() ? settings::luaClientMoveHk : "Off") << '\n';
	}

	std::pair<std::string, decltype(&callback)> commandPair()
	{
		return { "luna_clientmove", callback };
	}
}
