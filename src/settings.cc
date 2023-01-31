#include <settings.hh>

namespace settings
{
	bool luaDump{ false };
	bool luaOverride{ false };

	namespace internals
	{
		std::queue<std::string> stateQueue[sdk::State::STATE_MAX];
	}
}