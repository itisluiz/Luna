#include <commands/safepaint.hh>
#include <features/printer.hh>
#include <settings.hh>

namespace commands::safepaint
{
	void callback(const std::vector<std::string_view>& tokens)
	{
		if (tokens.size() >= 2)
		{
			if (tokens[1] == "0")
				settings::luaSafePaint.clear();
			else
				settings::luaSafePaint = tokens[1];
		}

		console << "Lua safepaint: " << (!settings::luaSafePaint.empty() ? sdk::Color{100, 255, 100, 255} : sdk::Color{255, 100, 100, 255}) << (!settings::luaSafePaint.empty() ? settings::luaSafePaint : "Off") << '\n';
	}

	std::pair<std::string, decltype(&callback)> commandPair()
	{
		return { "luna_safepaint", callback };
	}
}
