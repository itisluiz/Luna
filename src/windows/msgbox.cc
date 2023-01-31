#include <windows/msgbox.hh>

namespace msgbox
{
	std::ostringstream message(std::ios_base::in | std::ios_base::out);

	ShowOptions::ShowOptions(uint8_t icon, uint8_t type, const std::string& title)
	{
		this->icon = icon;
		this->type = type;
		this->title = title;
	}

	std::ostream& operator<<(std::ostream& msgbox, const ShowOptions& msgshow)
	{
		std::ostringstream osstream;
		osstream << msgbox.rdbuf();

		msgbox.clear();
		MessageBoxA(NULL, osstream.str().c_str(), msgshow.title.c_str(), MB_SYSTEMMODAL | MB_TOPMOST | msgshow.type | msgshow.icon);
		msgbox.flush();

		return msgbox;
	}

}
