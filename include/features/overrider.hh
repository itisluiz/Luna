#ifndef LUNA_FEATURE_OVERRIDING
#define LUNA_FEATURE_OVERRIDING
#include <optional>
#include <string>

namespace features::overrider
{
	std::optional<std::string> overrideScript(const char* filename);
	void stats();
	void reset();
}

#endif
