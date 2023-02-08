#include <sdk/source.hh>
#include <windows/pe.hh>
#include <windows/pattern.hh>
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