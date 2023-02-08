#ifndef LUNA_PATTERN_HH
#define LUNA_PATTERN_HH
#include <vector>
#include <string>
#include <optional>

class Pattern
{
	std::vector<std::optional<uint8_t>> m_bytes{ };
	ptrdiff_t m_offset{ 0 };

public:
	Pattern(const std::string& idaPattern, ptrdiff_t offset = 0);

private:
	static inline bool predicate(const uint8_t& data, const std::optional<uint8_t>& pattern);

public:
	std::string str() const;
	void* locate(void* start, void* end) const;

};

#endif
