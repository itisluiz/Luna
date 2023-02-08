#ifndef LUNA_SDK_SOURCE_HH
#define LUNA_SDK_SOURCE_HH
#include <cstdint>

namespace sdk
{
	class model_t;
	class SurfInfo;
	class IMaterial;
	class player_info_t;
	class client_textmessage_t;
	class model_t;
	class CSentence;
	class CAudioSource;
	class ButtonCode_t;
	class VMatrix;
	class ISpatialQuery;
	class IMaterialSystem;
	class AudioState_t;
	class CPhysCollide;
	class matrix3x4_t;
	class color32;
	class color32_s;
	class vmode_s;
	class OcclusionParams_t;
	class SkyboxVisibility_t;
	class IAchievementMgr;
	class CGamestatsData;
	class KeyValues;
	class IClientEntity;
	class IGMODDataTable;
	class CGMODVariant;
	class CCommand;
	class CSteamAPIContext;
	class Vector;
	class QAngle;
	class CGlobalVarsBase;
	class ClientClass;
	class bf_write;
	class bf_read;
	class CViewSetup;
	class ScreenFade_t;
	class CEngineSprite;
	class ClientFrameStage_t;
	class CSaveRestoreData;
	class datamap_t;
	class typedescription_t;
	class CStandardRecvProxies;
	class IFileList;
	class CRenamedRecvTableInfo;
	class CMouthInfo;
	class IConVar;
	class VPANEL;
	class IntRect;
	class IHTML;
	class IHTMLEvents;
	class Vertex_t;
	class CharRenderInfo;
	class IVguiMatInfo;
	class IImage;

	struct Color
	{
		uint8_t r, g, b, a;
	};

	struct vrect_t
	{
		int x, y, width, height;
		vrect_t* pnext;
	};

	using SurfaceFeature_e = int;
	using FontDrawType_t = int;
	using InitReturnVal_t = int;
	using ImageFormat = int;
	using HFont = unsigned long;
	using HCursor = unsigned long;
	using HTexture = unsigned long;

	using CreateInterface = void* (const char* name, int* returnCode);

	class IAppSystem
	{
	public:
		virtual bool Connect(CreateInterface factory) = 0;
		virtual void Disconnect() = 0;
		virtual void* QueryInterface(const char* pInterfaceName) = 0;
		virtual InitReturnVal_t Init() = 0;
		virtual void Shutdown() = 0;
	};

	class INetChannelInfo
	{
	public:
		enum {
			GENERIC = 0,
			LOCALPLAYER,
			OTHERPLAYERS,
			ENTITIES,
			SOUNDS,
			EVENTS,
			USERMESSAGES,
			ENTMESSAGES,
			VOICE,
			STRINGTABLE,
			MOVE,
			STRINGCMD,
			SIGNON,
			TOTAL,
		};
		virtual const char* GetName(void) const = 0;
		virtual const char* GetAddress(void) const = 0;
		virtual float GetTime(void) const = 0;
		virtual float GetTimeConnected(void) const = 0;
		virtual int GetBufferSize(void) const = 0;
		virtual int GetDataRate(void) const = 0;
		virtual bool IsLoopback(void) const = 0;
		virtual bool IsTimingOut(void) const = 0;
		virtual bool IsPlayback(void) const = 0;
		virtual float GetLatency(int flow) const = 0;
		virtual float GetAvgLatency(int flow) const = 0;
		virtual float GetAvgLoss(int flow) const = 0;
		virtual float GetAvgChoke(int flow) const = 0;
		virtual float GetAvgData(int flow) const = 0;
		virtual float GetAvgPackets(int flow) const = 0;
		virtual int GetTotalData(int flow) const = 0;
		virtual int GetSequenceNr(int flow) const = 0;
		virtual bool IsValidPacket(int flow, int frame_number) const = 0;
		virtual float GetPacketTime(int flow, int frame_number) const = 0;
		virtual int GetPacketBytes(int flow, int frame_number, int group) const = 0;
		virtual bool GetStreamProgress(int flow, int* received, int* total) const = 0;
		virtual float GetTimeSinceLastReceived(void) const = 0;
		virtual	float GetCommandInterpolationAmount(int flow, int frame_number) const = 0;
		virtual void GetPacketResponseLatency(int flow, int frame_number, int* pnLatencyMsecs, int* pnChoke) const = 0;
		virtual void GetRemoteFramerate(float* pflFrameTime, float* pflFrameTimeStdDeviation) const = 0;
		virtual float GetTimeoutSeconds() const = 0;
	};

	class IVEngineClient013
	{
	public:
		virtual int GetIntersectingSurfaces(const model_t* model, const Vector & vCenter, const float radius,const bool bOnlyVisibleSurfaces, SurfInfo* pInfos, const int nMaxInfos) = 0;
		virtual Vector GetLightForPoint(const Vector& pos, bool bClamp) = 0;
		virtual IMaterial* TraceLineMaterialAndLighting(const Vector& start, const Vector& end, Vector& diffuseLightColor, Vector& baseColor) = 0;
		virtual const char* ParseFile(const char* data, char* token, int maxlen) = 0;
		virtual bool CopyLocalFile(const char* source, const char* destination) = 0;
		virtual void GetScreenSize(int& width, int& height) = 0;
		virtual void ServerCmd(const char* szCmdString, bool bReliable = true) = 0;
		virtual void ClientCmd(const char* szCmdString) = 0;
		virtual bool GetPlayerInfo(int ent_num, player_info_t* pinfo) = 0;
		virtual int GetPlayerForUserID(int userID) = 0;
		virtual client_textmessage_t* TextMessageGet(const char* pName) = 0;
		virtual bool Con_IsVisible(void) = 0;
		virtual int GetLocalPlayer(void) = 0;
		virtual const model_t* LoadModel(const char* pName, bool bProp = false) = 0;
		virtual float Time(void) = 0;
		virtual float GetLastTimeStamp(void) = 0;
		virtual CSentence* GetSentence(CAudioSource* pAudioSource) = 0;
		virtual float GetSentenceLength(CAudioSource* pAudioSource) = 0;
		virtual bool IsStreaming(CAudioSource* pAudioSource) const = 0;
		virtual void GetViewAngles(QAngle& va) = 0;
		virtual void SetViewAngles(QAngle& va) = 0;
		virtual int GetMaxClients(void) = 0;
		virtual	const char* Key_LookupBinding(const char* pBinding) = 0;
		virtual const char* Key_BindingForKey(ButtonCode_t code) = 0;
		virtual void StartKeyTrapMode(void) = 0;
		virtual bool CheckDoneKeyTrapping(ButtonCode_t& code) = 0;
		virtual bool IsInGame(void) = 0;
		virtual bool IsConnected(void) = 0;
		virtual bool IsDrawingLoadingImage(void) = 0;
		virtual void Con_NPrintf(int pos, const char* fmt, ...) = 0;
		virtual void Con_NXPrintf(const struct con_nprint_s* info, const char* fmt, ...) = 0;
		virtual int IsBoxVisible(const Vector& mins, const Vector& maxs) = 0;
		virtual int IsBoxInViewCluster(const Vector& mins, const Vector& maxs) = 0;
		virtual bool CullBox(const Vector& mins, const Vector& maxs) = 0;
		virtual void Sound_ExtraUpdate(void) = 0;
		virtual const char* GetGameDirectory(void) = 0;
		virtual const VMatrix& WorldToScreenMatrix() = 0;
		virtual const VMatrix& WorldToViewMatrix() = 0;
		virtual int GameLumpVersion(int lumpId) const = 0;
		virtual int GameLumpSize(int lumpId) const = 0;
		virtual bool LoadGameLump(int lumpId, void* pBuffer, int size) = 0;
		virtual int LevelLeafCount() const = 0;
		virtual ISpatialQuery* GetBSPTreeQuery() = 0;
		virtual void LinearToGamma(float* linear, float* gamma) = 0;
		virtual float LightStyleValue(int style) = 0;
		virtual void ComputeDynamicLighting(const Vector& pt, const Vector* pNormal, Vector& color) = 0;
		virtual void GetAmbientLightColor(Vector& color) = 0;
		virtual int GetDXSupportLevel() = 0;
		virtual bool SupportsHDR() = 0;
		virtual void Mat_Stub(IMaterialSystem* pMatSys) = 0;
		virtual void GetChapterName(char* pchBuff, int iMaxLength) = 0;
		virtual char const* GetLevelName(void) = 0;
		virtual int GetLevelVersion(void) = 0;
		virtual struct IVoiceTweak_s* GetVoiceTweakAPI(void) = 0;
		virtual void EngineStats_BeginFrame(void) = 0;
		virtual void EngineStats_EndFrame(void) = 0;
		virtual void FireEvents() = 0;
		virtual int GetLeavesArea(int* pLeaves, int nLeaves) = 0;
		virtual bool DoesBoxTouchAreaFrustum(const Vector& mins, const Vector& maxs, int iArea) = 0;
		virtual void SetAudioState(const AudioState_t& state) = 0;
		virtual int SentenceGroupPick(int groupIndex, char* name, int nameBufLen) = 0;
		virtual int SentenceGroupPickSequential(int groupIndex, char* name, int nameBufLen, int sentenceIndex, int reset) = 0;
		virtual int SentenceIndexFromName(const char* pSentenceName) = 0;
		virtual const char* SentenceNameFromIndex(int sentenceIndex) = 0;
		virtual int SentenceGroupIndexFromName(const char* pGroupName) = 0;
		virtual const char* SentenceGroupNameFromIndex(int groupIndex) = 0;
		virtual float SentenceLength(int sentenceIndex) = 0;
		virtual void ComputeLighting(const Vector& pt, const Vector* pNormal, bool bClamp, Vector& color, Vector* pBoxColors = NULL) = 0;
		virtual void ActivateOccluder(int nOccluderIndex, bool bActive) = 0;
		virtual bool IsOccluded(const Vector& vecAbsMins, const Vector& vecAbsMaxs) = 0;
		virtual void* SaveAllocMemory(size_t num, size_t size) = 0;
		virtual void SaveFreeMemory(void* pSaveMem) = 0;
		virtual INetChannelInfo* GetNetChannelInfo(void) = 0;
		virtual void DebugDrawPhysCollide(const CPhysCollide* pCollide, IMaterial* pMaterial, matrix3x4_t& transform, const color32& color) = 0;
		virtual void CheckPoint(const char* pName) = 0;
		virtual void DrawPortals() = 0;
		virtual bool IsPlayingDemo(void) = 0;
		virtual bool IsRecordingDemo(void) = 0;
		virtual bool IsPlayingTimeDemo(void) = 0;
		virtual int GetDemoRecordingTick(void) = 0;
		virtual int GetDemoPlaybackTick(void) = 0;
		virtual int GetDemoPlaybackStartTick(void) = 0;
		virtual float GetDemoPlaybackTimeScale(void) = 0;
		virtual int GetDemoPlaybackTotalTicks(void) = 0;
		virtual bool IsPaused(void) = 0;
		virtual bool IsTakingScreenshot(void) = 0;
		virtual bool IsHLTV(void) = 0;
		virtual bool IsLevelMainMenuBackground(void) = 0;
		virtual void GetMainMenuBackgroundName(char* dest, int destlen) = 0;
		virtual void GetVideoModes(int& nCount, vmode_s*& pModes) = 0;
		virtual void SetOcclusionParameters(const OcclusionParams_t& params) = 0;
		virtual void GetUILanguage(char* dest, int destlen) = 0;
		virtual SkyboxVisibility_t IsSkyboxVisibleFromPoint(const Vector& vecPoint) = 0;
		virtual const char* GetMapEntitiesString() = 0;
		virtual bool IsInEditMode(void) = 0;
		virtual float GetScreenAspectRatio() = 0;
		virtual bool REMOVED_SteamRefreshLogin(const char* password, bool isSecure) = 0;
		virtual bool REMOVED_SteamProcessCall(bool& finished) = 0;
		virtual unsigned int GetEngineBuildNumber() = 0; 		virtual const char* GetProductVersionString() = 0; 
		virtual void GrabPreColorCorrectedFrame(int x, int y, int width, int height) = 0;
		virtual bool IsHammerRunning() const = 0;
		virtual void ExecuteClientCmd(const char* szCmdString) = 0;
		virtual bool MapHasHDRLighting(void) = 0;
		virtual int GetAppID() = 0;
		virtual Vector GetLightForPointFast(const Vector& pos, bool bClamp) = 0;
		virtual void ClientCmd_Unrestricted(const char* szCmdString) = 0;
		virtual void SetRestrictServerCommands(bool bRestrict) = 0;
		virtual void SetRestrictClientCommands(bool bRestrict) = 0;
		virtual void SetOverlayBindProxy(int iOverlayID, void* pBindProxy) = 0;
		virtual bool CopyFrameBufferToMaterial(const char* pMaterialName) = 0;
		virtual void ChangeTeam(const char* pTeamName) = 0;
		virtual void ReadConfiguration(const bool readDefault = false) = 0;
		virtual void SetAchievementMgr(IAchievementMgr* pAchievementMgr) = 0;
		virtual IAchievementMgr* GetAchievementMgr() = 0;
		virtual bool MapLoadFailed(void) = 0;
		virtual void SetMapLoadFailed(bool bState) = 0;
		virtual bool IsLowViolence() = 0;
		virtual const char* GetMostRecentSaveGame(void) = 0;
		virtual void SetMostRecentSaveGame(const char* lpszFilename) = 0;
		virtual void StartXboxExitingProcess() = 0;
		virtual bool IsSaveInProgress() = 0;
		virtual uint32_t OnStorageDeviceAttached(void) = 0;
		virtual void OnStorageDeviceDetached(void) = 0;
		virtual void ResetDemoInterpolation(void) = 0;
		virtual void SetGamestatsData(CGamestatsData* pGamestatsData) = 0;
		virtual CGamestatsData* GetGamestatsData() = 0;
		virtual void GetMouseDelta(int& x, int& y, bool bIgnoreNextMouseDelta = false) = 0;
		virtual void ServerCmdKeyValues(KeyValues* pKeyValues) = 0;
		virtual bool IsSkippingPlayback(void) = 0;
		virtual bool IsLoadingDemo(void) = 0;
		virtual bool IsPlayingDemoALocallyRecordedDemo() = 0;
		virtual	const char* Key_LookupBindingExact(const char* pBinding) = 0;
		virtual void GMOD_SetTimeManipulator(float fScaleFramerate) = 0;
		virtual	void GMOD_SendToServer(void* data, unsigned int dataSize, bool reliable) = 0;
		virtual void GMOD_PlaceDecalMaterial(IMaterial*, bool, int, IClientEntity*, const Vector&, const Vector&, const color32_s&, float, float) = 0;
		virtual void GMOD_GetSpew(char* buffer, unsigned int bufferSize) = 0;
		virtual void GMOD_SetViewEntity(uint32_t) = 0;
		virtual void GMOD_BrushMaterialOverride(IMaterial* matOverride) = 0;
		virtual void GMOD_R_RedownloadAllLightmaps(bool) = 0;
		virtual void GMOD_RawClientCmd_Unrestricted(const char* command) = 0;
		virtual IGMODDataTable* GMOD_CreateDataTable(void(*)(void*, int, const CGMODVariant&)) = 0;
		virtual void GMOD_DestroyDataTable(IGMODDataTable* dataTable) = 0;
		virtual void GMOD_LoadModel(const char* path) = 0;
	};

	class IVEngineClient : public IVEngineClient013
	{
	public:
		virtual uint32_t GetProtocolVersion() = 0;
		virtual bool IsWindowedMode() = 0;
		virtual void FlashWindow() = 0;
		virtual int GetClientVersion() const = 0;
		virtual bool IsActiveApp() = 0;
		virtual void DisconnectInternal() = 0;
		virtual bool IsInCommentaryMode() = 0;

		bool IsRecordingMovie();
	};
#define ENGINECLIENT_IFACESTR "VENGINECLIENT015"

	class IBaseClientDLL
	{
	public:
		virtual int Init(CreateInterface appSystemFactory, CreateInterface physicsFactory, CGlobalVarsBase *pGlobals) = 0;
		virtual void PostInit() = 0;
		virtual void Shutdown(void) = 0;
		virtual bool ReplayInit(CreateInterface replayFactory) = 0;
		virtual bool ReplayPostInit() = 0;
		virtual void LevelInitPreEntity(char const* pMapName) = 0;
		virtual void LevelInitPostEntity() = 0;
		virtual void LevelShutdown(void) = 0;
		virtual ClientClass *GetAllClasses(void) = 0;
		virtual int HudVidInit(void) = 0;
		virtual void HudProcessInput(bool bActive) = 0;
		virtual void HudUpdate(bool bActive) = 0;
		virtual void HudReset(void) = 0;
		virtual void HudText(const char* message) = 0;
		virtual void IN_ActivateMouse(void) = 0;
		virtual void IN_DeactivateMouse(void) = 0;
		virtual void IN_Accumulate(void) = 0;
		virtual void IN_ClearStates(void) = 0;
		virtual bool IN_IsKeyDown(const char *name, bool& isdown) = 0;
		virtual void IN_OnMouseWheeled(int nDelta) = 0;
		virtual int IN_KeyEvent(int eventcode, ButtonCode_t keynum, const char *pszCurrentBinding) = 0;
		virtual void CreateMove(int sequence_number, float input_sample_frametime,	bool active) = 0;				
		virtual void ExtraMouseSample(float frametime, bool active) = 0;
		virtual bool WriteUsercmdDeltaToBuffer(bf_write *buf, int from, int to, bool isnewcommand) = 0;
		virtual void EncodeUserCmdToBuffer(bf_write& buf, int slot) = 0;
		virtual void DecodeUserCmdFromBuffer(bf_read& buf, int slot) = 0;
		virtual void View_Render(vrect_t *rect) = 0;
		virtual void RenderView(const CViewSetup &view, int nClearFlags, int whatToDraw) = 0;
		virtual void View_Fade(ScreenFade_t *pSF) = 0;
		virtual void SetCrosshairAngle(const QAngle& angle) = 0;
		virtual void InitSprite(CEngineSprite *pSprite, const char *loadname) = 0;
		virtual void ShutdownSprite(CEngineSprite *pSprite) = 0;
		virtual int GetSpriteSize(void) const = 0;
		virtual void VoiceStatus(int entindex, int bTalking) = 0;
		virtual void InstallStringTableCallback(char const *tableName) = 0;
		virtual void FrameStageNotify(ClientFrameStage_t curStage) = 0;
		virtual bool DispatchUserMessage(int msg_type, bf_read &msg_data) = 0;
		virtual CSaveRestoreData *SaveInit(int size) = 0;
		virtual void SaveWriteFields(CSaveRestoreData *, const char *, void *, datamap_t *, typedescription_t *, int) = 0;
		virtual void SaveReadFields(CSaveRestoreData *, const char *, void *, datamap_t *, typedescription_t *, int) = 0;
		virtual void PreSave(CSaveRestoreData *) = 0;
		virtual void Save(CSaveRestoreData *) = 0;
		virtual void WriteSaveHeaders(CSaveRestoreData *) = 0;
		virtual void ReadRestoreHeaders(CSaveRestoreData *) = 0;
		virtual void Restore(CSaveRestoreData *, bool) = 0;
		virtual void DispatchOnRestore() = 0;
		virtual CStandardRecvProxies* GetStandardRecvProxies() = 0;
		virtual void WriteSaveGameScreenshot(const char *pFilename) = 0;
		virtual void EmitSentenceCloseCaption(char const *tokenstream) = 0;
		virtual void EmitCloseCaption(char const *captionname, float duration) = 0;
		virtual bool CanRecordDemo(char *errorMsg, int length) const = 0;
		virtual void OnDemoRecordStart(char const* pDemoBaseName) = 0;
		virtual void OnDemoRecordStop() = 0;
		virtual void OnDemoPlaybackStart(char const* pDemoBaseName) = 0;
		virtual void OnDemoPlaybackStop() = 0;
		virtual bool ShouldDrawDropdownConsole() = 0;
		virtual int GetScreenWidth() = 0;
		virtual int GetScreenHeight() = 0;
		virtual void WriteSaveGameScreenshotOfSize(const char *pFilename, int width, int height, bool bCreatePowerOf2Padded = false, bool bWriteVTF = false) = 0;
		virtual bool GetPlayerView(CViewSetup &playerView) = 0;
		virtual void SetupGameProperties(void* contexts, void* properties) = 0;
		virtual uint32_t GetPresenceID(const char *pIDName) = 0;
		virtual const char *GetPropertyIdString(const uint32_t id) = 0;
		virtual void GetPropertyDisplayString(uint32_t id, uint32_t value, char *pOutput, int nBytes) = 0;
		virtual void StartStatsReporting(void* handle, bool bArbitrated) = 0;
		virtual void InvalidateMdlCache() = 0;
		virtual void IN_SetSampleTime(float frametime) = 0;
		virtual void ReloadFilesInList(IFileList *pFilesToReload) = 0;
		virtual bool HandleUiToggle() = 0;
		virtual bool ShouldAllowConsole() = 0;
		virtual CRenamedRecvTableInfo *GetRenamedRecvTableInfos() = 0;
		virtual CMouthInfo *GetClientUIMouthInfo() = 0;
		virtual void FileReceived(const char * fileName, unsigned int transferID) = 0;
		virtual const char* TranslateEffectForVisionFilter(const char *pchEffectType, const char *pchEffectName) = 0;
		virtual void ClientAdjustStartSoundParams(struct StartSoundParams_t& params) = 0;
		virtual bool DisconnectAttempt(void) = 0;
		virtual bool IsConnectedUserInfoChangeAllowed(IConVar *pCvar) = 0;
	};
#define BASECLIENT_IFACESTR "VClient017"

	class ISurface : public IAppSystem
	{
		virtual void unkn01() = 0;
		virtual void unkn02() = 0;
		virtual void unkn03() = 0;
		virtual void unkn04() = 0;
	public:
		virtual void Shutdown() = 0;
		virtual void RunFrame() = 0;
		virtual VPANEL GetEmbeddedPanel() = 0;
		virtual void SetEmbeddedPanel(VPANEL pPanel) = 0;
		virtual void PushMakeCurrent(VPANEL panel, bool useInsets) = 0;
		virtual void PopMakeCurrent(VPANEL panel) = 0;
		virtual void DrawSetColor(int r, int g, int b, int a) = 0;
		virtual void DrawSetColor(Color col) = 0;
		virtual void DrawFilledRect(int x0, int y0, int x1, int y1) = 0;
		virtual void DrawFilledRectArray(IntRect* pRects, int numRects) = 0;
		virtual void DrawOutlinedRect(int x0, int y0, int x1, int y1) = 0;
		virtual void DrawLine(int x0, int y0, int x1, int y1) = 0;
		virtual void DrawPolyLine(int* px, int* py, int numPoints) = 0;
		virtual void DrawSetTextFont(HFont font) = 0;
		virtual void DrawSetTextColor(int r, int g, int b, int a) = 0;
		virtual void DrawSetTextColor(Color col) = 0;
		virtual void DrawSetTextPos(int x, int y) = 0;
		virtual void DrawGetTextPos(int& x, int& y) = 0;
		virtual void DrawPrintText(const wchar_t* text, int textLen, FontDrawType_t drawType = 0) = 0;
		virtual void DrawUnicodeChar(wchar_t wch, FontDrawType_t drawType = 0) = 0;
		virtual void DrawFlushText() = 0;
		virtual IHTML* CreateHTMLWindow(IHTMLEvents* events, VPANEL context) = 0;
		virtual void PaintHTMLWindow(IHTML* htmlwin) = 0;
		virtual void DeleteHTMLWindow(IHTML* htmlwin) = 0;
		virtual int	 DrawGetTextureId(char const* filename) = 0;
		virtual bool DrawGetTextureFile(int id, char* filename, int maxlen) = 0;
		virtual void DrawSetTextureFile(int id, const char* filename, int hardwareFilter, bool forceReload) = 0;
		virtual void DrawSetTextureRGBA(int id, const unsigned char* rgba, int wide, int tall, int hardwareFilter, bool forceReload) = 0;
		virtual void DrawSetTexture(int id) = 0;
		virtual void DrawGetTextureSize(int id, int& wide, int& tall) = 0;
		virtual void DrawTexturedRect(int x0, int y0, int x1, int y1) = 0;
		virtual bool IsTextureIDValid(int id) = 0;
		virtual int CreateNewTextureID(bool procedural = false) = 0;
		virtual void GetScreenSize(int& wide, int& tall) = 0;
		virtual void SetAsTopMost(VPANEL panel, bool state) = 0;
		virtual void BringToFront(VPANEL panel) = 0;
		virtual void SetForegroundWindow(VPANEL panel) = 0;
		virtual void SetPanelVisible(VPANEL panel, bool state) = 0;
		virtual void SetMinimized(VPANEL panel, bool state) = 0;
		virtual bool IsMinimized(VPANEL panel) = 0;
		virtual void FlashWindow(VPANEL panel, bool state) = 0;
		virtual void SetTitle(VPANEL panel, const wchar_t* title) = 0;
		virtual void SetAsToolBar(VPANEL panel, bool state) = 0;
		virtual void CreatePopup(VPANEL panel, bool minimised, bool showTaskbarIcon = true, bool disabled = false, bool mouseInput = true, bool kbInput = true) = 0;
		virtual void SwapBuffers(VPANEL panel) = 0;
		virtual void Invalidate(VPANEL panel) = 0;
		virtual void SetCursor(HCursor cursor) = 0;
		virtual bool IsCursorVisible() = 0;
		virtual void ApplyChanges() = 0;
		virtual bool IsWithin(int x, int y) = 0;
		virtual bool HasFocus() = 0;
		virtual bool SupportsFeature(SurfaceFeature_e feature) = 0;
		virtual void RestrictPaintToSinglePanel(VPANEL panel) = 0;
		virtual void SetModalPanel(VPANEL) = 0;
		virtual VPANEL GetModalPanel() = 0;
		virtual void UnlockCursor() = 0;
		virtual void LockCursor() = 0;
		virtual void SetTranslateExtendedKeys(bool state) = 0;
		virtual VPANEL GetTopmostPopup() = 0;
		virtual void SetTopLevelFocus(VPANEL panel) = 0;
		virtual HFont CreateFont() = 0;
		virtual bool SetFontGlyphSet(HFont font, const char* windowsFontName, int tall, int weight, int blur, int scanlines, int flags) = 0;
		virtual bool AddCustomFontFile(const char* fontName, const char* fontFileName) = 0;
		virtual int GetFontTall(HFont font) = 0;
		virtual int GetFontAscent(HFont font, wchar_t wch) = 0;
		virtual bool IsFontAdditive(HFont font) = 0;
		virtual void GetCharABCwide(HFont font, int ch, int& a, int& b, int& c) = 0;
		virtual int GetCharacterWidth(HFont font, int ch) = 0;
		virtual void GetTextSize(HFont font, const wchar_t* text, int& wide, int& tall) = 0;
		virtual VPANEL GetNotifyPanel() = 0;
		virtual void SetNotifyIcon(VPANEL context, HTexture icon, VPANEL panelToReceiveMessages, const char* text) = 0;
		virtual void PlaySound(const char* fileName) = 0;
		virtual int GetPopupCount() = 0;
		virtual VPANEL GetPopup(int index) = 0;
		virtual bool ShouldPaintChildPanel(VPANEL childPanel) = 0;
		virtual bool RecreateContext(VPANEL panel) = 0;
		virtual void AddPanel(VPANEL panel) = 0;
		virtual void ReleasePanel(VPANEL panel) = 0;
		virtual void MovePopupToFront(VPANEL panel) = 0;
		virtual void MovePopupToBack(VPANEL panel) = 0;
		virtual void SolveTraverse(VPANEL panel, bool forceApplySchemeSettings = false) = 0;
		virtual void PaintTraverse(VPANEL panel) = 0;
		virtual void EnableMouseCapture(VPANEL panel, bool state) = 0;
		virtual void GetWorkspaceBounds(int& x, int& y, int& wide, int& tall) = 0;
		virtual void GetAbsoluteWindowBounds(int& x, int& y, int& wide, int& tall) = 0;
		virtual void GetProportionalBase(int& width, int& height) = 0;
		virtual void CalculateMouseVisible() = 0;
		virtual bool NeedKBInput() = 0;
		virtual bool HasCursorPosFunctions() = 0;
		virtual void SurfaceGetCursorPos(int& x, int& y) = 0;
		virtual void SurfaceSetCursorPos(int x, int y) = 0;
		virtual void DrawTexturedLine(const Vertex_t& a, const Vertex_t& b) = 0;
		virtual void DrawOutlinedCircle(int x, int y, int radius, int segments) = 0;
		virtual void DrawTexturedPolyLine(const Vertex_t* p, int n) = 0;
		virtual void DrawTexturedSubRect(int x0, int y0, int x1, int y1, float texs0, float text0, float texs1, float text1) = 0;
		virtual void DrawTexturedPolygon(int n, Vertex_t* pVertices) = 0;
		virtual const wchar_t* GetTitle(VPANEL panel) = 0;
		virtual bool IsCursorLocked(void) const = 0;
		virtual void SetWorkspaceInsets(int left, int top, int right, int bottom) = 0;
		virtual bool DrawGetUnicodeCharRenderInfo(wchar_t ch, CharRenderInfo& info) = 0;
		virtual void DrawRenderCharFromInfo(const CharRenderInfo& info) = 0;
		virtual void DrawSetAlphaMultiplier(float alpha) = 0;
		virtual float DrawGetAlphaMultiplier() = 0;
		virtual void SetAllowHTMLJavaScript(bool state) = 0;
		virtual void OnScreenSizeChanged(int nOldWidth, int nOldHeight) = 0;
		virtual IVguiMatInfo* DrawGetTextureMatInfoFactory(int id) = 0;
		virtual void PaintTraverseEx(VPANEL panel, bool paintPopups = false) = 0;
		virtual float GetZPos() const = 0;
		virtual void SetPanelForInput(VPANEL vpanel) = 0;
		virtual void DrawFilledRectFade(int x0, int y0, int x1, int y1, unsigned int alpha0, unsigned int alpha1, bool bHorizontal) = 0;
		virtual void DrawSetTextureRGBAEx(int id, const unsigned char* rgba, int wide, int tall, ImageFormat imageFormat) = 0;
		virtual void DrawSetTextScale(float sx, float sy) = 0;
		virtual bool SetBitmapFontGlyphSet(HFont font, const char* windowsFontName, float scalex, float scaley, int flags) = 0;
		virtual bool AddBitmapFontFile(const char* fontFileName) = 0;
		virtual void SetBitmapFontName(const char* pName, const char* pFontFilename) = 0;
		virtual const char* GetBitmapFontName(const char* pName) = 0;
		virtual IImage* GetIconImageForFullPath(char const* pFullPath) = 0;
		virtual void DrawUnicodeString(const wchar_t* pwString, FontDrawType_t drawType = 0) = 0;

		void StartDrawing();
		void FinishDrawing();
	};
#define MATSURFACE_IFACESTR "VGUI_Surface030"
	
}
#endif