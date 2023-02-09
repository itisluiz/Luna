#include <memory/pe.hh>

PESection::PESection(const std::string& sectionName, const HMODULE hModule)
{
	if (!hModule) return;

	PIMAGE_DOS_HEADER dosHeader{ reinterpret_cast<PIMAGE_DOS_HEADER>(hModule) };
	PIMAGE_NT_HEADERS ntHeader{ reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<uintptr_t>(dosHeader) + dosHeader->e_lfanew) };
	PIMAGE_SECTION_HEADER sectionHeader{ reinterpret_cast<PIMAGE_SECTION_HEADER>(ntHeader + 1) };

	for (uint16_t sectionIndex{ 0 }; sectionIndex < ntHeader->FileHeader.NumberOfSections; ++sectionIndex)
		if (sectionName == reinterpret_cast<char*>(sectionHeader[sectionIndex].Name))
			m_section = sectionHeader + sectionIndex;
}

PESection::PESection(const std::string& sectionName, const LPCSTR szModuleName)
	: PESection(sectionName, GetModuleHandleA(szModuleName)) { }

PESection::operator bool() const
{
	return m_section != nullptr;
}

size_t PESection::length() const { return m_section->Misc.VirtualSize; }
void* PESection::start() const { return reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(m_section) + m_section->VirtualAddress); }
void* PESection::end() const { return reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(start()) + length()); }
