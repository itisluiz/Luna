#include <commands/run.hh>
#include <features/printer.hh>
#include <features/luamanager.hh>
#include <command.hh>

namespace commands::run
{
	void callback(const std::vector<std::string_view>& tokens)
	{
		if (tokens.size() < 3)
		{
			console << "Usage: " << sdk::Color{ 0, 200, 255, 255 } << "luna_run" << sdk::Color{ 200, 200, 200, 255 } << " [state] [script]" "\n";
			return;
		}

		sdk::State state{ features::luamanager::toState(std::string(tokens[1])) };

		if (!features::luamanager::enqueueScript(tokensFrom(tokens, 2), state))
			console << "Interface " << state << " is not available" "\n";
	}

	std::pair<std::string, decltype(&callback)> commandPair()
	{
		return { "luna_run", callback };
	}
}
