#include <command.hh>
#include <map>

#include <commands/unload.hh>
#include <commands/dump.hh>
#include <commands/overrider.hh>
#include <commands/run.hh>

static std::map<std::string, commandCallbackFn*> registeredCommands;

static std::vector<std::string_view> tokenize(const std::string& command)
{
	std::vector<std::string_view> tokens;
	if (command.empty())
		return tokens;

	bool quoted{ false };
	for (size_t lastws{ 0 }, current{ 0 }; current <= command.size(); ++current)
	{
		unsigned char curChar{ static_cast<unsigned char>(command[current]) };

		if ((!quoted && std::isspace(curChar)) || (quoted && curChar == '\"') || current == command.size())
		{
			if (current - lastws > 0)
				tokens.push_back({ command.data() + lastws, current - lastws });
			
			lastws = current + 1;
		}

		if (curChar == '\"' && (quoted = !quoted))
			lastws = current + 1;
	}

	return tokens;
}

std::string tokensFrom(const std::vector<std::string_view> tokens, size_t index)
{
	if (tokens.size() <= index)
		return { };

	std::string result;

	for (auto token{ tokens.begin() + index }; token < tokens.end(); ++token)
		result += *token;

	return result;
}

bool runCommand(const std::string& command)
{
	std::vector<std::string_view> tokens = tokenize(command);

	if (tokens.empty())
		return false;

	std::string commandToken{ tokens.front() };
	for (char& c : commandToken)
		c = tolower(c);

	if (registeredCommands.find(commandToken) == registeredCommands.end())
		return false;

	registeredCommands[commandToken](tokens);
	return true;
}

void loadCommands()
{
	registeredCommands.insert(commands::unload::commandPair());
	registeredCommands.insert(commands::dump::commandPair());
	registeredCommands.insert(commands::overrider::commandPair());
	registeredCommands.insert(commands::run::commandPair());
}