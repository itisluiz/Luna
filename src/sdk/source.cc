#include <sdk/source.hh>
#include <memory/pe.hh>
#include <memory/pattern.hh>
#include <features/printer.hh>

namespace sdk
{
	bool IVEngineClient::IsRecordingMovie()
	{
		static bool* recordingMovie{ nullptr };

		if (!recordingMovie)
		{
			PESection section(".text", "engine.dll");
#ifdef _WIN64
			Pattern pattern("80 3D ?? ?? ?? ?? 00 74 19", 2);
			int32_t* recordingMovieOffset = reinterpret_cast<int32_t*>(pattern.locate(section.start(), section.end()));
			recordingMovie = reinterpret_cast<bool*>(reinterpret_cast<uintptr_t>(recordingMovieOffset) + *recordingMovieOffset + 5);
#else
			Pattern pattern("80 3D ?? ?? ?? ?? 00 74 66", 2);
			recordingMovie = *reinterpret_cast<bool**>(pattern.locate(section.start(), section.end()));
#endif
		}

		return *recordingMovie;
	}

	void IClientMode::sendPacket(bool sendpacket)
	{
		constexpr uint16_t noChokeInstruction{ 0x840F };
		constexpr uint16_t chokeInstruction{ 0xE990 };

		static uint16_t* instruction{ nullptr };

		if (!instruction)
		{
			PESection section(".text", "engine.dll");
#ifdef _WIN64
			Pattern pattern("48 45 84 F6 0F 84", 4);
#else
			Pattern pattern("FF 50 ?? 84 DB 0F 84", 5);
#endif
			instruction = reinterpret_cast<uint16_t*>(pattern.locate(section.start(), section.end()));
		}

		if ((sendpacket && *instruction == noChokeInstruction) || (!sendpacket && *instruction == chokeInstruction))
			return;

		DWORD oldProtect, newProtect;
		if (!VirtualProtect(instruction, 2, PAGE_EXECUTE_READWRITE, &oldProtect))
			return;

		*instruction = sendpacket ? noChokeInstruction : chokeInstruction;
		VirtualProtect(instruction, 2, oldProtect, &newProtect);
	}


	void ISurface::StartDrawing()
	{
		using StartDrawingFn = void(__thiscall*)(ISurface*);
		static StartDrawingFn StartDrawing{ nullptr };

		if (!StartDrawing)
		{
			PESection section(".text", "vguimatsurface.dll");
#ifdef _WIN64
			Pattern pattern("40 53 56 57 48 83 EC ?? 48 8B F9 80");
#else
			Pattern pattern("55 8B EC 64 A1 ? ? ? ? 6A FF 68 ? ? ? ? 50 64 89 25 ? ? ? ? 83 EC 14");
#endif
			StartDrawing = reinterpret_cast<StartDrawingFn>(pattern.locate(section.start(), section.end()));
		}

		StartDrawing(this);
	}

	void ISurface::FinishDrawing()
	{
		using FinishDrawingFn = void(__thiscall*)(ISurface*);
		static FinishDrawingFn FinishDrawing{ nullptr };

		if (!FinishDrawing)
		{
			PESection section(".text", "vguimatsurface.dll");
#ifdef _WIN64
			Pattern pattern("40 53 48 83 EC ?? 33 C9");
#else
			Pattern pattern("55 8B EC 6A FF 68 ? ? ? ? 64 A1 ? ? ? ? 50 64 89 25 ? ? ? ? 51 56 6A 00");
#endif
			FinishDrawing = reinterpret_cast<FinishDrawingFn>(pattern.locate(section.start(), section.end()));
		}

		FinishDrawing(this);
	}

}