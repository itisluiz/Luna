#ifndef LUNA_FEATURE_PRINTING
#define LUNA_FEATURE_PRINTING
#include <sstream>
#include <sdk/luaifaces.hh>

namespace features::printer
{
	class Console
	{
		sdk::Color m_color{ 255, 255, 255, 255 };
		bool m_newline{ true };

	private:
		Console() = default;
		Console(const Console&) = delete;

	public:
		static Console& getInstance();

	private:
		void prefix();

	public:
		void print(const std::string& msg);
		
		template <typename T>
		Console& operator<<(T value)
		{
			std::ostringstream buffer;
			buffer << value;
			print(buffer.str());
			return *this;
		}
		Console& operator<<(sdk::State state);
		Console& operator<<(const sdk::Color& value);
		
		Console& operator= (const Console&) = delete;
	};

}

extern features::printer::Console& console;

#endif
