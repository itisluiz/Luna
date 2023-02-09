#include <initdeinit.hh>
#include <features/printer.hh>
#include <imports.hh>
#include <hooking.hh>
#include <command.hh>

bool init()
{
	if (!loadImports())
		return false;

	if (!loadHooks())
		return false;

	loadCommands();

	console << sdk::Color{ 100, 255, 100, 255 } << "Loaded" "\n";
	return true;
}

void deinit()
{
	unloadHooks();
	sdk::IClientMode::sendPacket(true);
	console << sdk::Color{ 200, 200, 200, 255 } << "Unloaded" "\n";
}