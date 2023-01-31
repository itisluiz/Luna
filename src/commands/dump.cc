#include <commands/dump.hh>
#include <features/printer.hh>
#include <settings.hh>

namespace commands::dump
{
	void callback(const std::vector<std::string_view>& tokens)
	{
		if (tokens.size() >= 2)
			settings::luaDump = std::atoi(std::string(tokens[1]).c_str());

		console << "Lua dumping: " << (settings::luaDump ? sdk::Color{ 100, 255, 100, 255 } : sdk::Color{ 255, 100, 100, 255 }) << (settings::luaDump ? "On" : "Off") << '\n';
	}

	std::pair<std::string, decltype(&callback)> commandPair()
	{
		return { "luna_dump", callback };
	}
}
