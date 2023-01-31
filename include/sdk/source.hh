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
	
	struct Color
	{
		uint8_t r, g, b, a;
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
	};
#define ENGINECLIENT_IFACESTR "VENGINECLIENT015"

	using CreateInterface = void* (const char* name, int* returnCode);
}
#endif