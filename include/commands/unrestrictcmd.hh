#ifndef LUNA_COMMAND_UNRESTRICTCMD_HH
#define LUNA_COMMAND_UNRESTRICTCMD_HH
#include <vector>
#include <string_view>

namespace commands::unrestrictcmd
{
	void callback(const std::vector<std::string_view>& tokens);
	std::pair<std::string, decltype(&callback)> commandPair();
}

#endif
