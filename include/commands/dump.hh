#ifndef LUNA_COMMAND_DUMP_HH
#define LUNA_COMMAND_DUMP_HH
#include <vector>
#include <string_view>

namespace commands::dump
{
	void callback(const std::vector<std::string_view>& tokens);
	std::pair<std::string, decltype(&callback)> commandPair();
}

#endif
