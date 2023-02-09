#ifndef LUNA_COMMAND_CLIENTMOVE_HH
#define LUNA_COMMAND_CLIENTMOVE_HH
#include <vector>
#include <string_view>

namespace commands::clientmove
{
	void callback(const std::vector<std::string_view>& tokens);
	std::pair<std::string, decltype(&callback)> commandPair();
}

#endif
