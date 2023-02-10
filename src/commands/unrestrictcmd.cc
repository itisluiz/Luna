#include <commands/unrestrictcmd.hh>
#include <features/printer.hh>
#include <settings.hh>
#include <command.hh>

namespace commands::unrestrictcmd
{
	void callback(const std::vector<std::string_view>& tokens)
	{
		if (tokens.size() >= 2)
			settings::luaUnrestrictCmd = std::atoi(std::string(tokens[1]).c_str());

		console << "Lua unrestrictcmd: " << (settings::luaUnrestrictCmd ? sdk::Color{ 100, 255, 100, 255 } : sdk::Color{ 255, 100, 100, 255 }) << (settings::luaUnrestrictCmd ? "On" : "Off") << '\n';
	}

	std::pair<std::string, decltype(&callback)> commandPair()
	{
		return { "luna_unrestrictcmd", callback };
	}
}
