#include <windows/pattern.hh>
#include <sstream>
#include <algorithm>

Pattern::Pattern(const std::string& idaPattern, ptrdiff_t offset) : m_offset(offset)
{
    std::stringstream parser(idaPattern);
    parser.flags(std::ios::skipws | std::ios::hex);

    for (uint16_t buffer; ~(parser >> buffer).rdstate() & (std::ios::failbit | std::ios::eofbit);)
    {
        if (!parser.fail())
            m_bytes.push_back(static_cast<uint8_t>(buffer));
        else
        {
            m_bytes.push_back(std::nullopt);

            parser.clear();
            parser.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
        }
    }
}

bool Pattern::predicate(const uint8_t& data, const std::optional<uint8_t>& pattern)
{
    return pattern.has_value() ? pattern.value() == data : true;
}

void* Pattern::locate(void* start, void* end) const
{
    void* result{ std::search(reinterpret_cast<uint8_t*>(start), reinterpret_cast<uint8_t*>(end),
        m_bytes.begin(), m_bytes.end(), Pattern::predicate) };

    if (result == end) return nullptr;

    return reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(result) + m_offset);
}

std::string Pattern::str() const
{
    std::stringstream parser;
    parser.flags(std::ios::hex | std::ios::uppercase);

    for (const auto& byte : m_bytes)
    {
        if (&byte != &(*m_bytes.begin()))
            parser << ' ';

        if (byte.has_value())
        {
            if (byte.value() < 0x10)
                parser << '0';

            parser << static_cast<uint16_t>(byte.value());
        }
        else
            parser << "??";
    }

    return parser.str();
}
