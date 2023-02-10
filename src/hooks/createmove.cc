#include <hooks/createmove.hh>
#include <features/luamanager.hh>
#include <hooking.hh>
#include <imports.hh>
#include <command.hh>
#include <settings.hh>

#define VTABLE_INDEX 21

namespace hooks::createmove
{
	decltype(&hook) original;

	bool __fastcall hook(sdk::IClientMode* clientMode EDX_PARAM float flInputSampleTime, sdk::CUserCmd* cmd)
	{
		bool result{ original(clientMode EDX_ARG flInputSampleTime, cmd) };
		sdk::ILuaInterface* clientInterface{ imports::iLuaShared->GetLuaInterface(sdk::State::CLIENT) };

		if (!clientInterface || settings::luaHkCreateMove.empty())
		{
			clientMode->sendPacket(true);
			return result;
		}

		clientInterface->CreateTable();
		{
			clientInterface->PushNumber(cmd->command_number);
			clientInterface->SetField(-2, "command_number");

			clientInterface->PushNumber(cmd->tick_count);
			clientInterface->SetField(-2, "tick_count");

			clientInterface->PushAngle(cmd->viewangles);
			clientInterface->SetField(-2, "viewangles");

			clientInterface->PushNumber(cmd->forwardmove);
			clientInterface->SetField(-2, "forwardmove");

			clientInterface->PushNumber(cmd->sidemove);
			clientInterface->SetField(-2, "sidemove");

			clientInterface->PushNumber(cmd->upmove);
			clientInterface->SetField(-2, "upmove");

			clientInterface->PushNumber(cmd->buttons);
			clientInterface->SetField(-2, "buttons");

			clientInterface->PushNumber(cmd->impulse);
			clientInterface->SetField(-2, "impulse");

			clientInterface->PushNumber(cmd->random_seed);
			clientInterface->SetField(-2, "random_seed");

			clientInterface->PushNumber(cmd->mousedx);
			clientInterface->SetField(-2, "mousedx");

			clientInterface->PushNumber(cmd->mousedy);
			clientInterface->SetField(-2, "mousedy");

			clientInterface->PushBool(cmd->hasbeenpredicted);
			clientInterface->SetField(-2, "hasbeenpredicted");
		}

		int returnCount{ features::luamanager::runHook(clientInterface, settings::luaHkCreateMove, 1, 3) };

		if (returnCount > 0 && clientInterface->IsType(-returnCount, sdk::LuaType::lua_Table))
		{
			clientInterface->GetField(-returnCount, "command_number");
			if (clientInterface->GetType(-1) == sdk::LuaType::lua_Number)
				cmd->command_number = clientInterface->GetNumber();
			clientInterface->Pop();

			clientInterface->GetField(-returnCount, "tick_count");
			if (clientInterface->GetType(-1) == sdk::LuaType::lua_Number)
				cmd->tick_count = clientInterface->GetNumber();
			clientInterface->Pop();

			clientInterface->GetField(-returnCount, "viewangles");
			if (clientInterface->GetType(-1) == sdk::LuaType::lua_Angle)
				cmd->viewangles = clientInterface->GetAngle();
			clientInterface->Pop();

			clientInterface->GetField(-returnCount, "forwardmove");
			if (clientInterface->GetType(-1) == sdk::LuaType::lua_Number)
				cmd->forwardmove = clientInterface->GetNumber();
			clientInterface->Pop();

			clientInterface->GetField(-returnCount, "sidemove");
			if (clientInterface->GetType(-1) == sdk::LuaType::lua_Number)
				cmd->sidemove = clientInterface->GetNumber();
			clientInterface->Pop();

			clientInterface->GetField(-returnCount, "upmove");
			if (clientInterface->GetType(-1) == sdk::LuaType::lua_Number)
				cmd->upmove = clientInterface->GetNumber();
			clientInterface->Pop();

			clientInterface->GetField(-returnCount, "buttons");
			if (clientInterface->GetType(-1) == sdk::LuaType::lua_Number)
				cmd->buttons = clientInterface->GetNumber();
			clientInterface->Pop();

			clientInterface->GetField(-returnCount, "impulse");
			if (clientInterface->GetType(-1) == sdk::LuaType::lua_Number)
				cmd->impulse = clientInterface->GetNumber();
			clientInterface->Pop();

			clientInterface->GetField(-returnCount, "weaponselect");
			if (clientInterface->GetType(-1) == sdk::LuaType::lua_Number)
				cmd->weaponselect = clientInterface->GetNumber();
			clientInterface->Pop();

			clientInterface->GetField(-returnCount, "weaponsubtype");
			if (clientInterface->GetType(-1) == sdk::LuaType::lua_Number)
				cmd->weaponsubtype = clientInterface->GetNumber();
			clientInterface->Pop();

			clientInterface->GetField(-returnCount, "random_seed");
			if (clientInterface->GetType(-1) == sdk::LuaType::lua_Number)
				cmd->random_seed = clientInterface->GetNumber();
			clientInterface->Pop();

			clientInterface->GetField(-returnCount, "mousedx");
			if (clientInterface->GetType(-1) == sdk::LuaType::lua_Number)
				cmd->mousedx = clientInterface->GetNumber();
			clientInterface->Pop();

			clientInterface->GetField(-returnCount, "mousedy");
			if (clientInterface->GetType(-1) == sdk::LuaType::lua_Number)
				cmd->mousedy = clientInterface->GetNumber();
			clientInterface->Pop();

			clientInterface->GetField(-returnCount, "hasbeenpredicted");
			if (clientInterface->GetType(-1) == sdk::LuaType::lua_Bool)
				cmd->hasbeenpredicted = clientInterface->GetBool();
			clientInterface->Pop();
		}

		if (returnCount > 1 && clientInterface->GetType(-returnCount + 1) == sdk::LuaType::lua_Bool)
			clientMode->sendPacket(clientInterface->GetBool(-returnCount + 1));
		else
			clientMode->sendPacket(true);

		if (returnCount > 2 && clientInterface->GetType(-returnCount + 2) == sdk::LuaType::lua_Bool)
			result = clientInterface->GetBool(-returnCount + 2);

		clientInterface->Pop(returnCount);
		return result;
	}

	MH_STATUS apply()
	{
		return MH_CreateHook(vFuncAddress(imports::iClientMode, VTABLE_INDEX), hook, reinterpret_cast<void**>(&original));
	}
}
