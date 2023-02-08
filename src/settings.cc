#include <settings.hh>

namespace settings
{
	bool luaDump{ false };
	bool luaOverride{ false };
	std::string luaSafePaint;

	namespace internals
	{
		std::queue<std::string> stateQueue[sdk::State::STATE_MAX];
	}
}