#ifndef LUNA_COMMAND_SAFEPAINT_HH
#define LUNA_COMMAND_SAFEPAINT_HH
#include <vector>
#include <string_view>

namespace commands::safepaint
{
	void callback(const std::vector<std::string_view>& tokens);
	std::pair<std::string, decltype(&callback)> commandPair();
}

#endif
