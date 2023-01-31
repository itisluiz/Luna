#ifndef LUNA_HOOKING_HH
#define LUNA_HOOKING_HH

void* vFuncAddress(void* object, size_t index);

bool loadHooks();
void unloadHooks();

#endif

