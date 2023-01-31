#include <windows/path.hh>
#include <Windows.h>
#include <ShlObj.h>
#include <cwctype>
#include <sstream>
#include <optional>

#define APPDATA_APP "Luna"

std::wstring sanitizePathComponent(std::wstring pathComponent, bool checkBadNames)
{
	const wchar_t badChars[]{ L'<', L'>', L':', L'\"', L'/', L'\\', L'|', L'?', L'*' };
	const wchar_t* badNames[]{ L".", L"con", L"prn", L"aux", L"nul", L"com\x01", L"lpt\x01"};

	for (wchar_t& c : pathComponent)
	{
		for (const wchar_t badChar : badChars)
		{
			if (c <= 31 || c == badChar)
				c = '_';
		}
	}

	if (checkBadNames)
	{
		for (const wchar_t* badName : badNames)
		{
			size_t badNameLen{ std::wcslen(badName) };

			if (badNameLen != pathComponent.size())
				continue;

			bool isBadName{ true };
			for (size_t charPos{ 0 }; charPos < badNameLen; ++charPos)
			{
				wchar_t pathChar{ static_cast<wchar_t>(std::towlower(pathComponent[charPos])) };
				wchar_t badChar{ badName[charPos] };

				if (badChar == L'\x01')
				{
					if (pathChar == L'0' || !std::iswdigit(pathChar))
						isBadName = false;
				}
				else if (pathChar != badChar)
					isBadName = false;

				if (!isBadName)
					break;
			}

			if (isBadName)
				return pathComponent.insert(0, 1, L'_');
		}

	}

	return pathComponent;
}
std::string sanitizePathComponent(std::string pathComponent, bool checkBadNames)
{
	std::wstring wideComponent(pathComponent.begin(), pathComponent.end());
	std::wstring wideSanitized{ sanitizePathComponent(wideComponent, checkBadNames) };

	return { wideSanitized.begin(), wideSanitized.end() };
}

fs::path sanitizePath(fs::path path)
{
	fs::path sanitizedPath;
	std::wistringstream pathStream(path.make_preferred().wstring());

	std::wstring pathComponent;
	for (size_t entryCount{ 0 }; std::getline(pathStream, pathComponent, path.preferred_separator); ++entryCount)
	{
		if (!entryCount && path.is_absolute())
		{
			sanitizedPath = pathComponent + path.preferred_separator;
			continue;
		}

		sanitizedPath /= sanitizePathComponent(pathComponent, true);
	}

	if (!sanitizedPath.has_filename())
		sanitizedPath.replace_filename("unnamed");

	return sanitizedPath;
}
fs::path sanitizePath(fs::path path, std::string ext)
{
	return sanitizePath(path).replace_extension(ext);
}

std::optional<fs::path> getAppdata(const fs::path& subPath)
{
	static fs::path appData;

	if (appData.empty())
	{
		wchar_t* outPath;
		if (SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &outPath) == S_OK)
		{
			appData = outPath;
			appData /= sanitizePathComponent(APPDATA_APP, true);
		}
		else
			return std::nullopt;
	}

	fs::path pathOut{ appData };

	if (!subPath.empty())
		pathOut /= sanitizePath(subPath);

	if (!fs::exists(pathOut) && !fs::create_directories(pathOut))
		return std::nullopt;

	return pathOut;
}

std::ofstream saveFile(fs::path path, std::ios_base::openmode openMode)
{
	std::ofstream outFileStream;

	fs::path fileName{ path.filename() };
	path.remove_filename();
	fs::create_directories(path);

	if (!fs::exists(path))
		return outFileStream;

	path.replace_filename(fileName);

	outFileStream.open(path, std::ios::out | openMode);
	return outFileStream;
}

std::ifstream openFile(fs::path path)
{
	return std::ifstream(path);
}