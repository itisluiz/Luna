#include <settings.hh>

namespace settings
{
	bool luaDump{ false };
	bool luaOverride{ false };
	std::string luaSafePaintHk;
	std::string luaClientMoveHk;

	namespace internals
	{
		std::queue<std::string> stateQueue[sdk::State::STATE_MAX];
	}
}