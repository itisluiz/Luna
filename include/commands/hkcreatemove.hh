#ifndef LUNA_COMMAND_HKCREATEMOVE_HH
#define LUNA_COMMAND_HKCREATEMOVE_HH
#include <vector>
#include <string_view>

namespace commands::hkcreatemove
{
	void callback(const std::vector<std::string_view>& tokens);
	std::pair<std::string, decltype(&callback)> commandPair();
}

#endif
