#include <features/printer.hh>
#include <imports.hh>

namespace features::printer
{
	Console& Console::getInstance()
	{
		static Console m_instance;

		return m_instance;
	}

	void Console::prefix()
	{
		m_newline = false;
		*this << sdk::Color{ 255, 255, 255, 255 } << '[' << sdk::Color{ 0, 200, 255, 255 } << "Luna" << sdk::Color{ 255, 255, 255, 255 } << "] ";
	}

	void Console::print(const std::string& msg)
	{
		if (m_newline)
			prefix();

		for (char c : msg)
		{
			if (c == '\n')
				m_newline = true;
			else if (m_newline)
				prefix();
		}
		
		sdk::ILuaInterface* menuInterface;
		if (!imports::iLuaShared || !(menuInterface = imports::iLuaShared->GetLuaInterface(sdk::State::MENU)))
			return;

		menuInterface->MsgColour(m_color, msg.c_str());
	}

	Console& Console::operator<<(sdk::State state)
	{
		sdk::Color oldColor{ m_color };

		switch (state)
		{
		case sdk::State::CLIENT:
			*this << sdk::Color{ 255, 222, 102, 255 } << "CLIENT";
			break;
		case sdk::State::SERVER:
			*this << sdk::Color{ 145, 219, 231, 255 } << "SERVER";
			break;
		case sdk::State::MENU:
			*this << sdk::Color{ 96, 201, 96, 255 } << "MENU";
			break;
		default:
			*this << sdk::Color{ 128, 128, 128, 255 } << "UNKNOWN";
		}

		return *this << oldColor;
	}

	Console& Console::operator<<(const sdk::Color& value)
	{
		if (m_newline)
			prefix();

		m_color = value;
		return *this;
	}

}

features::printer::Console& console{ features::printer::Console::getInstance() };