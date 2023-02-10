#include <settings.hh>

namespace settings
{
	bool luaDump{ false };
	bool luaOverride{ false };
	bool luaUnrestrictCmd{ false };
	std::string luaHkPaint;
	std::string luaHkCreateMove;

	namespace internals
	{
		std::queue<std::string> stateQueue[sdk::State::STATE_MAX];
	}
}