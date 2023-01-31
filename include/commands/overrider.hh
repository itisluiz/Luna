#ifndef LUNA_COMMAND_OVERRIDER_HH
#define LUNA_COMMAND_OVERRIDER_HH
#include <vector>
#include <string_view>

namespace commands::overrider
{
	void callback(const std::vector<std::string_view>& tokens);
	std::pair<std::string, decltype(&callback)> commandPair();
}

#endif
