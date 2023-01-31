#include <features/overrider.hh>
#include <features/printer.hh>
#include <windows/path.hh>
#include <imports.hh>
#include <settings.hh>
#include <sstream>

#define OVERRIDER_FOLDERNAME "override"
#define OVERRIDER_GENERIC_FOLDERNAME "any"

namespace features::overrider
{
	static size_t overrideCount{ 0 };
	static std::optional<std::pair<fs::path, fs::path>> paths;

	std::optional<std::string> overrideScript(const char* filename)
	{
		if (!settings::luaOverride)
			return std::nullopt;

		if (!paths.has_value())
		{
			std::optional<fs::path> firstPath{ getAppdata(fs::path(OVERRIDER_FOLDERNAME) / imports::iEngineClient->GetNetChannelInfo()->GetAddress()) };
			std::optional<fs::path> secondPath{ getAppdata(fs::path(OVERRIDER_FOLDERNAME) / OVERRIDER_GENERIC_FOLDERNAME) };

			if (!firstPath.has_value() || !secondPath.has_value())
			{
				console << sdk::Color{ 255, 100, 100, 255 } << "Failed to acquire folder for the Lua overrider" "\n";
				return std::nullopt;
			}

			paths = { firstPath.value(), secondPath.value() };
		}

		fs::path sanitizedPath;
		fs::path sanitizedFilename{ sanitizePath(filename, "lua") };

		if (!fs::exists((sanitizedPath = paths.value().first / sanitizedFilename)) && !fs::exists((sanitizedPath = paths.value().second / sanitizedFilename)))
			return std::nullopt;
		
		std::ifstream inFile{ openFile(sanitizedPath) };
		if (!inFile)
		{
			console << sdk::Color{ 255, 100, 100, 255 } << "Failed to open file for reading: " << sanitizedPath << '\n';
			return std::nullopt;
		}

		++overrideCount;
		std::stringstream scriptBuffer;
		scriptBuffer << inFile.rdbuf();

		return scriptBuffer.str();
	}

	void stats()
	{
		if (settings::luaOverride)
			console << "Overriden " << (overrideCount ? sdk::Color{ 0, 200, 255, 255 } : sdk::Color{ 255, 100, 100, 255 }) << overrideCount << sdk::Color{ 255, 255, 255, 255 } << " scripts from " << sdk::Color{ 200, 200, 200, 255 } << imports::iEngineClient->GetNetChannelInfo()->GetAddress() << '\n';
	}

	void reset()
	{
		paths = std::nullopt;
		overrideCount = 0;
	}

}