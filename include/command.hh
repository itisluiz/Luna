#ifndef LUNA_COMMAND_HH
#define LUNA_COMMAND_HH
#include <vector>
#include <string>
#include <string_view>

using commandCallbackFn = void(const std::vector<std::string_view>& tokens);

std::string tokensFrom(const std::vector<std::string_view> tokens, size_t index);
bool runCommand(const std::string& command);
void loadCommands();

#endif
