#include <commands/overrider.hh>
#include <features/printer.hh>
#include <settings.hh>

namespace commands::overrider
{
	void callback(const std::vector<std::string_view>& tokens)
	{
		if (tokens.size() >= 2)
			settings::luaOverride = std::atoi(std::string(tokens[1]).c_str());

		console << "Lua overrding: " << (settings::luaOverride ? sdk::Color{ 100, 255, 100, 255 } : sdk::Color{ 255, 100, 100, 255 }) << (settings::luaOverride ? "On" : "Off") << '\n';
	}

	std::pair<std::string, decltype(&callback)> commandPair()
	{
		return { "luna_override", callback };
	}
}
