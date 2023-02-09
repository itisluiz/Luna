# Luna
Garry's Mod Lua state manipulator and dumper.

## Filesystem
Luna's folder will be created under `AppData\Local\Luna`

## Features
### **Lua dumper**
Will dump scripts ran on your client Lua interface to `Luna\dump\serveraddress`

### **Lua overrider**
Will override scripts attemped to be run on your client their path path matches a file under `Luna\override\serveraddress` or `Luna\override\any`

### **Lua executor**
Will run Lua scripts in one of the game's Lua interfaces. Can handle literal string scripts or filenames, which can be absolute paths or relative to `Luna\userscripts`.

## Commands
### **luna_unload**
Gracefully unloads luna

### **luna_dump** *[opt enabled]*
Client script dumper state

- *enabled*: Optional, 0 for disabled or 1 for enabled. If not provided will show current setting.

### **luna_override** *[opt enabled]*
Client script overrider state

- *enabled*: Optional, 0 for disabled or 1 for enabled. If not provided will show current setting.

### **luna_safepaint** *[opt hookname]*
Safe 2D drawing hook for Lua scripts

- *hookname*: Optional, 0 for disabled or name of the hook which will be called with `hook.Run` for drawing every frame. If not provided will show current setting. Drawing inside this hook will draw on top of everything else and cannot be captured (screen grabbed) from within Lua.

### **luna_clientmove** *[opt hookname]*
Unrestricted CreateMove hook for Lua scripts

- *hookname*: Optional, 0 for disabled or name of the hook which will be called with `hook.Run` for overriding createmove. If not provided will show current setting. The will pass a CUserCmd table with the following fields:
  `command_number, tick_count, viewangles, forwardmove, sidemove, upmove, buttons, impulse, random_seed, mousedx, mousedy, hasbeenpredicted`. The hook may return a table with the keys and values to override in CUserCmd, a boolean representing bSendPacket and a boolean for overriding the return value of CreateMove, respectively.

### **luna_run** *[state] [script]*
Lua script executor

- *state*: Lua state in which to run script (menu, client or server).
- *script*: Lua script to run. If it is a path to an existing file (absolute or relative to userscripts), that file will be ran. Otherwise will be interpreted as a literal Lua script string.