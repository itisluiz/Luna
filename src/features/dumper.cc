#include <features/dumper.hh>
#include <features/printer.hh>
#include <windows/path.hh>
#include <settings.hh>
#include <imports.hh>
#include <set>

#define DUMPER_FOLDERNAME "dump"

namespace features::dumper
{
	static size_t dumpCount{ 0 };
	static std::optional<fs::path> path;
	static std::set<fs::path> seenFiles;

	void dumpScript(const char* filename, const char* script)
	{
		if (!settings::luaDump)
			return;

		if (!path.has_value())
		{
			path = getAppdata(fs::path(DUMPER_FOLDERNAME) / imports::iEngineClient->GetNetChannelInfo()->GetAddress());

			if (!path.has_value())
			{
				console << sdk::Color{ 255, 100, 100, 255 } << "Failed to acquire folder for the Lua dumper" "\n";
				return;
			}
		}
			
		fs::path sanitizedPath{ path.value() / sanitizePath(filename, "lua") };
		bool hasSeenFile{ seenFiles.find(sanitizedPath) != seenFiles.end() };

		std::ofstream outFile{ saveFile(sanitizedPath, hasSeenFile ? std::ios::app : std::ios::trunc) };
		if (!outFile)
		{
			console << sdk::Color{ 255, 100, 100, 255 } << "Failed to open file for writing: " << sanitizedPath << '\n';
			return;
		}

		if (hasSeenFile)
			outFile << '\n';

		++dumpCount;
		outFile << script;
		outFile.close();
	}

	void stats()
	{
		if (settings::luaDump)
			console << "Dumped " << (dumpCount ? sdk::Color{ 0, 200, 255, 255 } : sdk::Color{ 255, 100, 100, 255 }) << dumpCount << sdk::Color{ 255, 255, 255, 255 } << " scripts from " << sdk::Color{ 200, 200, 200, 255 } << imports::iEngineClient->GetNetChannelInfo()->GetAddress() << '\n';
	}

	void reset()
	{
		path = std::nullopt;
		seenFiles.clear();
		dumpCount = 0;
	}

}
