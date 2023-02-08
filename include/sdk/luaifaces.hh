#ifndef LUNA_SDK_LUAIFACES_HH
#define LUNA_SDK_LUAIFACES_HH
#include <sdk/lua.hh>
#include <sdk/source.hh>
#include <string>
#include <vector>

namespace sdk
{
	struct BBuffer
	{
		void* pData;
		unsigned int iSize;
		unsigned int iPos;
		unsigned int iWritten;
	};

	struct File
	{
		int time;
		std::string name;
		std::string source;
		std::string contents;
		BBuffer compressed;
		unsigned int timesloadedserver;
		unsigned int timesloadedclient;
	};

	class ILuaObject;
	class ILuaThreadedCall;
	class ILuaGameCallback;
	class IGet;
	class LuaClientDatatableHook;
	class BaseEntity;
	class IPhysicsObject;

	using CFunc = int(__cdecl*)(lua_State*);

	enum State : uint8_t
	{
		CLIENT,
		SERVER,
		MENU,
		STATE_MAX
	};

	enum SpecialField : int32_t
	{
		INDEX_GLOBAL = -10002,
		INDEX_ENVIRONMENT,
		INDEX_REGISTRY,
	};

	enum SpecialPush : uint8_t
	{
		SPECIAL_GLOB,
		SPECIAL_ENV,
		SPECIAL_REG,
	};

	enum LuaType
	{
		lua_None = -1,
		lua_Nil,
		lua_Bool,
		lua_LightUserData,
		lua_Number,
		lua_String,
		lua_Table,
		lua_Function,
		lua_UserData,
		lua_Thread,
		lua_Entity,
		lua_Vector,
		lua_Angle,
		lua_PhysObj,
		lua_Save,
		lua_Restore,
		lua_DamageInfo,
		lua_EffectData,
		lua_MoveData,
		lua_RecipientFilter,
		lua_UserCmd,
		lua_ScriptedVehicle,
		lua_Material,
		lua_Panel,
		lua_Particle,
		lua_ParticleEmitter,
		lua_Texture,
		lua_UserMsg,
		lua_ConVar,
		lua_IMesh,
		lua_Matrix,
		lua_Sound,
		lua_PixelVisHandle,
		lua_DLight,
		lua_Video,
		lua_File,
		lua_Locomotion,
		lua_Path,
		lua_NavArea,
		lua_SoundHandle,
		lua_NavLadder,
		lua_ParticleSystem,
		lua_ProjectedTexture,
		lua_PhysCollide,
		lua_SurfaceInfo,
		lua_Type_Count
	};

	class ILuaBase
	{
	public:
		lua_State* state;
        virtual int Top(void) = 0;
        virtual void Push(int iStackPos) = 0;
        virtual void Pop(int iAmt = 1) = 0;
        virtual void voidGetTable(int iStackPos) = 0;
        virtual void GetField(int iStackPos, const char* strName) = 0;
        virtual void SetField(int iStackPos, const char* strName) = 0;
        virtual void CreateTable() = 0;
		virtual void SetTable(int iStackPos) = 0;
        virtual void SetMetaTable(int iStackPos) = 0;
        virtual bool GetMetaTable(int i) = 0;
		virtual void Call(int iArgs, int iResults) = 0;
        virtual int PCall(int iArgs, int iResults, int iErrorFunc) = 0;
        virtual int Equal(int iA, int iB) = 0;
        virtual int RawEqual(int iA, int iB) = 0;
        virtual void Insert(int iStackPos) = 0;
        virtual void Remove(int iStackPos) = 0;
        virtual int Next(int iStackPos) = 0;
        virtual void* NewUserdata(unsigned int iSize) = 0;
        virtual void ThrowError(const char* strError) = 0;
        virtual void CheckType(int iStackPos, int iType) = 0;
        virtual void ArgError(int iArgNum, const char* strMessage) = 0;
        virtual void RawGet(int iStackPos) = 0;
		virtual void RawSet(int iStackPos) = 0;
		virtual const char* GetString(int iStackPos = -1, unsigned int* iOutLen = nullptr) = 0;
		virtual double GetNumber(int iStackPos = -1) = 0;
		virtual bool GetBool(int iStackPos = -1) = 0;
		virtual CFunc GetCFunction(int iStackPos = -1) = 0;
        virtual void* GetUserdata(int iStackPos = -1) = 0;
		virtual void PushNil() = 0;
        virtual void PushString(const char* val, unsigned int iLen = 0) = 0;
        virtual void PushNumber(double val) = 0;
        virtual void PushBool(bool val) = 0;
        virtual void PushCFunction(CFunc val) = 0;
        virtual void PushCClosure(CFunc val, int iVars) = 0;
        virtual void PushUserdata(void*) = 0;
		virtual int ReferenceCreate() = 0;
        virtual void ReferenceFree(int i) = 0;
        virtual void ReferencePush(int i) = 0;
		virtual void PushSpecial(int iType) = 0;
        virtual bool IsType(int iStackPos, int iType) = 0;
        virtual int GetType(int iStackPos) = 0;
        virtual const char* GetTypeName(int iType) = 0;
        virtual void CreateMetaTableType(const char* strName, int iType) = 0;
        virtual const char* CheckString(int iStackPos = -1) = 0;
        virtual double CheckNumber(int iStackPos = -1) = 0;
        virtual int ObjLen(int iStackPos = -1) = 0;
        virtual const QAngle& GetAngle(int iStackPos = -1) = 0;
        virtual const Vector& GetVector(int iStackPos = -1) = 0;
        virtual void PushAngle(const QAngle& val) = 0;
        virtual void PushVector(const Vector& val) = 0;
        virtual void SetState(lua_State* L) = 0;
        virtual int CreateMetaTable(const char* strName) = 0;
        virtual bool PushMetaTable(int iType) = 0;
        virtual void PushUserType(void* data, int iType) = 0;
        virtual void SetUserType(int iStackPos, void* data) = 0;
	};

	class ILuaObject
	{
	public:
		virtual void Set(ILuaObject* obj) = 0;
		virtual void SetFromStack(int i) = 0;
		virtual void UnReference() = 0;
		virtual int GetType() = 0;
		virtual const char* GetString() = 0;
		virtual float GetFloat() = 0;
		virtual int GetInt() = 0;
		virtual void* GetUserData() = 0;
		virtual void SetMember(const char* name) = 0;
		virtual void SetMember(const char* name, ILuaObject* obj) = 0;
		virtual void SetMember(const char* name, float val) = 0;
		virtual void SetMember(const char* name, bool val) = 0;
		virtual void SetMember(const char* name, const char* val) = 0;
		virtual void SetMember(const char* name, CFunc f) = 0;
		virtual bool GetMemberBool(const char* name, bool b = true) = 0;
		virtual int GetMemberInt(const char* name, int i = 0) = 0;
		virtual float GetMemberFloat(const char* name, float f = 0.0f) = 0;
		virtual const char* GetMemberStr(const char* name, const char* s = "") = 0;
		virtual void* GetMemberUserData(const char* name, void* u = 0) = 0;
		virtual void* GetMemberUserData(float name, void* u = 0) = 0;
		virtual ILuaObject* GetMember(const char* name) = 0;
		virtual ILuaObject* GetMember(ILuaObject* key) = 0;
		virtual void SetMetaTable(ILuaObject* obj) = 0;
		virtual void SetUserData(void* obj) = 0;
		virtual void Push() = 0;
		virtual bool isNil() = 0;
		virtual bool isTable() = 0;
		virtual bool isString() = 0;
		virtual bool isNumber() = 0;
		virtual bool isFunction() = 0;
		virtual bool isUserData() = 0;
		virtual ILuaObject* GetMember(float fKey) = 0;
		virtual void* Remove_Me_1(const char* name, void* = 0) = 0;
		virtual void SetMember(float fKey) = 0;
		virtual void SetMember(float fKey, ILuaObject* obj) = 0;
		virtual void SetMember(float fKey, float val) = 0;
		virtual void SetMember(float fKey, bool val) = 0;
		virtual void SetMember(float fKey, const char* val) = 0;
		virtual void SetMember(float fKey, CFunc f) = 0;
		virtual const char* GetMemberStr(float name, const char* s = "") = 0;
		virtual void SetMember(ILuaObject* k, ILuaObject* v) = 0;
		virtual bool GetBool() = 0;
		virtual bool PushMemberFast(int iStackPos) = 0;
		virtual void SetMemberFast(int iKey, int iValue) = 0;
		virtual void SetFloat(float val) = 0;
		virtual void SetString(const char* val) = 0;
		virtual double GetDouble() = 0;
		virtual void SetMember_FixKey(const char*, float) = 0;
		virtual void SetMember_FixKey(const char*, const char*) = 0;
		virtual void SetMember_FixKey(const char*, ILuaObject*) = 0;
		virtual void SetMember_FixKey(const char*, double) = 0;
		virtual void SetMember_FixKey(const char*, int) = 0;
		virtual bool isBool() = 0;
		virtual void SetMemberDouble(const char*, double) = 0;
		virtual void SetMemberNil(const char*) = 0;
		virtual void SetMemberNil(float) = 0;
		virtual bool RemoveMe() = 0;
		virtual void Init() = 0;
		virtual void SetFromGlobal(const char*) = 0;
		virtual int GetStringLen(unsigned int*) = 0;
		virtual unsigned int GetMemberUInt(const char*, unsigned int) = 0;
		virtual void SetMember(const char*, unsigned long long) = 0;
		virtual void SetReference(int) = 0;
		virtual void RemoveMember(const char*) = 0;
		virtual void RemoveMember(float) = 0;
		virtual bool MemberIsNil(const char*) = 0;
		virtual void SetMemberDouble(float, double) = 0;
		virtual double GetMemberDouble(const char*, double) = 0;
		virtual BaseEntity* GetMemberEntity(const char*, BaseEntity*) = 0;
		virtual void SetMemberEntity(float, BaseEntity*) = 0;
		virtual void SetMemberEntity(const char*, BaseEntity*) = 0;
		virtual bool isEntity() = 0;
		virtual BaseEntity* GetEntity() = 0;
		virtual void SetEntity(BaseEntity*) = 0;
		virtual void SetMemberVector(const char*, Vector*) = 0;
		virtual void SetMemberVector(const char*, Vector&) = 0;
		virtual void SetMemberVector(float, Vector*) = 0;
		virtual Vector* GetMemberVector(const char*, const Vector*) = 0;
		virtual Vector* GetMemberVector(int) = 0;
		virtual Vector* GetVector() = 0;
		virtual bool isVector() = 0;
		virtual void SetMemberAngle(const char*, QAngle*) = 0;
		virtual QAngle* GetMemberAngle(const char*, QAngle*) = 0;
		virtual QAngle* GetAngle() = 0;
		virtual bool isAngle() = 0;
		virtual void SetMemberPhysObject(const char*, IPhysicsObject*) = 0;
	};
	
	class ILuaInterface : public ILuaBase
	{
	public:
		virtual bool Init(ILuaGameCallback*, bool) = 0;
		virtual void Shutdown() = 0;
		virtual void Cycle() = 0;
		virtual ILuaObject* Global() = 0;
		virtual ILuaObject* GetObject_(int index) = 0;
		virtual void PushLuaObject(ILuaObject* obj) = 0;
		virtual void PushLuaFunction(CFunc func) = 0;
		virtual void LuaError(const char* err, int index) = 0;
		virtual void TypeError(const char* name, int index) = 0;
		virtual void CallInternal(int args, int rets) = 0;
		virtual void CallInternalNoReturns(int args) = 0;
		virtual bool CallInternalGetBool(int args) = 0;
		virtual const char* CallInternalGetString(int args) = 0;
		virtual bool CallInternalGet(int args, ILuaObject* obj) = 0;
		virtual void NewGlobalTable(const char* name) = 0;
		virtual ILuaObject* NewTemporaryObject() = 0;
		virtual bool isUserData(int index) = 0;
		virtual ILuaObject* GetMetaTableObject(const char* name, int type) = 0;
		virtual ILuaObject* GetMetaTableObject(int index) = 0;
		virtual ILuaObject* GetReturn(int index) = 0;
		virtual bool IsServer() = 0;
		virtual bool IsClient() = 0;
		virtual bool IsMenu() = 0;
		virtual void DestroyObject(ILuaObject* obj) = 0;
		virtual ILuaObject* CreateObject() = 0;
		virtual void SetMember(ILuaObject* table, ILuaObject* key, ILuaObject* value) = 0;
		virtual void GetNewTable() = 0;
		virtual void SetMember(ILuaObject* table, float key) = 0;
		virtual void SetMember(ILuaObject* table, float key, ILuaObject* value) = 0;
		virtual void SetMember(ILuaObject* table, const char* key) = 0;
		virtual void SetMember(ILuaObject* table, const char* key, ILuaObject* value) = 0;
		virtual void SetType(unsigned char) = 0;
		virtual void PushLong(long num) = 0;
		virtual int GetFlags(int index) = 0;
		virtual bool FindOnObjectsMetaTable(int objIndex, int keyIndex) = 0;
		virtual bool FindObjectOnTable(int tableIndex, int keyIndex) = 0;
		virtual void SetMemberFast(ILuaObject* table, int keyIndex, int valueIndex) = 0;
		virtual bool RunString(const char* filename, const char* path, const char* stringToRun, bool run, bool showErrors) = 0;
		virtual bool IsEqual(ILuaObject* objA, ILuaObject* objB) = 0;
		virtual void Error(const char* err) = 0;
		virtual const char* GetStringOrError(int index) = 0;
		virtual bool RunLuaModule(const char* name) = 0;
		virtual bool FindAndRunScript(const char* filename, bool run, bool showErrors, const char* stringToRun, bool noReturns) = 0;
		virtual void SetPathID(const char* pathID) = 0;
		virtual const char* GetPathID() = 0;
		virtual void ErrorNoHalt(const char* fmt, ...) = 0;
		virtual void Msg(const char* fmt, ...) = 0;
		virtual void PushPath(const char* path) = 0;
		virtual void PopPath() = 0;
		virtual const char* GetPath() = 0;
		virtual int GetColor(int index) = 0;
		virtual void PushColor(Color color) = 0;
		virtual int GetStack(int level, lua_Debug* dbg) = 0;
		virtual int GetInfo(const char* what, lua_Debug* dbg) = 0;
		virtual const char* GetLocal(lua_Debug* dbg, int n) = 0;
		virtual const char* GetUpvalue(int funcIndex, int n) = 0;
		virtual bool RunStringEx(const char* filename, const char* path, const char* stringToRun, bool run, bool printErrors, bool dontPushErrors, bool noReturns) = 0;
		virtual size_t GetDataString(int index, const char** str) = 0;
		virtual void ErrorFromLua(const char* fmt, ...) = 0;
		virtual const char* GetCurrentLocation() = 0;
		virtual void MsgColour(const Color& col, const char* fmt, ...) = 0;
		virtual void GetCurrentFile(std::string& outStr) = 0;
		virtual void CompileString(BBuffer& dumper, const std::string& stringToCompile) = 0;
		virtual bool CallFunctionProtected(int, int, bool) = 0;
		virtual void Require(const char* name) = 0;
		virtual const char* GetActualTypeName(int type) = 0;
		virtual void PreCreateTable(int arrelems, int nonarrelems) = 0;
		virtual void PushPooledString(int index) = 0;
		virtual const char* GetPooledString(int index) = 0;
		virtual void* AddThreadedCall(ILuaThreadedCall*) = 0;
		virtual void AppendStackTrace(char*, unsigned long) = 0;
		virtual void* CreateConVar(const char*, const char*, const char*, int) = 0;
		virtual void* CreateConCommand(const char*, const char*, int, void (*)(const CCommand&), int (*)(const char*, char(*)[128])) = 0;
	};

	class ILuaShared
	{
	public:
		virtual ~ILuaShared() = 0;
		virtual void Init(void* (*)(const char*, int*), bool, CSteamAPIContext*, IGet*) = 0;
		virtual void Shutdown() = 0;
		virtual void DumpStats() = 0;
		virtual ILuaInterface* CreateLuaInterface(unsigned char, bool) = 0;
		virtual void CloseLuaInterface(ILuaInterface*) = 0;
		virtual ILuaInterface* GetLuaInterface(unsigned char) = 0;
		virtual File* LoadFile(const std::string& path, const std::string& pathId, bool fromDatatable, bool fromFile) = 0;
		virtual File* GetCache(const std::string&) = 0;
		virtual void MountLua(const char*) = 0;
		virtual void MountLuaAdd(const char*, const char*) = 0;
		virtual void UnMountLua(const char*) = 0;
		virtual void SetFileContents(const char*, const char*) = 0;
		virtual void SetLuaFindHook(LuaClientDatatableHook*) = 0;
		virtual void FindScripts(const std::string&, const std::string&, std::vector<std::string>&) = 0;
		virtual const char* GetStackTraces() = 0;
		virtual void InvalidateCache(const std::string&) = 0;
		virtual void EmptyCache() = 0;
	};
#define LUASHARED_IFACESTR "LUASHARED003"

}

#endif