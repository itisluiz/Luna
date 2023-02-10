#include <commands/hkpaint.hh>
#include <features/printer.hh>
#include <settings.hh>

namespace commands::hkpaint
{
	void callback(const std::vector<std::string_view>& tokens)
	{
		if (tokens.size() >= 2)
		{
			if (tokens[1] == "0")
				settings::luaHkPaint.clear();
			else
				settings::luaHkPaint = tokens[1];
		}

		console << "Lua hkpaint: " << (!settings::luaHkPaint.empty() ? sdk::Color{100, 255, 100, 255} : sdk::Color{255, 100, 100, 255}) << (!settings::luaHkPaint.empty() ? settings::luaHkPaint : "Off") << '\n';
	}

	std::pair<std::string, decltype(&callback)> commandPair()
	{
		return { "luna_paint_hk", callback };
	}
}
