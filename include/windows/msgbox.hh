#ifndef LUNA_WINDOWS_MSGBOX_HH
#define LUNA_WINDOWS_MSGBOX_HH
#include <Windows.h>
#include <WinUser.h>
#include <sstream>

#define DEFAULT_MSGBOX_TITLE "Luna"

namespace msgbox
{
	extern std::ostringstream message;

	struct ShowOptions
	{
		uint8_t icon;
		uint8_t type;
		std::string title;

	public:
		ShowOptions(uint8_t icon = MB_ICONINFORMATION, uint8_t type = MB_OK, const std::string& title = DEFAULT_MSGBOX_TITLE);

	};

	std::ostream& operator<<(std::ostream& msgbox, const ShowOptions& msgtype);
}


#endif
