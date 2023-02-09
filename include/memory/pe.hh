#ifndef LUNA_PE_HH
#define LUNA_PE_HH
#include <Windows.h>
#include <string>

class PESection
{
	PIMAGE_SECTION_HEADER m_section{ nullptr };

public:
	PESection() = default;
	PESection(const std::string& sectionName, const HMODULE hModule);
	PESection(const std::string& sectionName, const LPCSTR szModuleName);

public:
	operator bool() const;

public:
	size_t length() const;
	void* start() const;
	void* end() const;

};

#endif
