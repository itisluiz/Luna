#ifndef LUNA_COMMAND_HKPAINT_HH
#define LUNA_COMMAND_HKPAINT_HH
#include <vector>
#include <string_view>

namespace commands::hkpaint
{
	void callback(const std::vector<std::string_view>& tokens);
	std::pair<std::string, decltype(&callback)> commandPair();
}

#endif
