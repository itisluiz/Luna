#ifndef LUNA_COMMAND_RUN_HH
#define LUNA_COMMAND_RUN_HH
#include <vector>
#include <string_view>

namespace commands::run
{
	void callback(const std::vector<std::string_view>& tokens);
	std::pair<std::string, decltype(&callback)> commandPair();
}

#endif
