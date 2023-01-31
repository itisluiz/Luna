#ifndef LUNA_COMMAND_UNLOAD_HH
#define LUNA_COMMAND_UNLOAD_HH
#include <vector>
#include <string_view>

namespace commands::unload
{
	void callback(const std::vector<std::string_view>& tokens);
	std::pair<std::string, decltype(&callback)> commandPair();
}

#endif
