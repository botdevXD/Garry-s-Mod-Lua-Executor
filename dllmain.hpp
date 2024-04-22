#include "pch.h"
#include <windows.h>
#include <iostream>
#include <psapi.h>
#include <functional>
#include <fstream>
#include <string>
#include <vector>

typedef struct lua_State lua_State;

#define LUA_GLOBALSINDEX	(-10002)
#define LUA_TBOOLEAN		1

const HMODULE lua_sharedModule = GetModuleHandleA("lua_shared.dll");
const uintptr_t lua_sharedBase = (uintptr_t)GetModuleHandleA("lua_shared.dll");

typedef int(__thiscall* MAYBE_GMOD_RUNTIME_SETUP_PROTO)(int arg1, int arg2);
MAYBE_GMOD_RUNTIME_SETUP_PROTO MAYBE_GMOD_RUNTIME_SETUP = (MAYBE_GMOD_RUNTIME_SETUP_PROTO)(lua_sharedBase + 0xAEE0);

typedef int(__fastcall* lua_pcallProto)(lua_State* luaState, int a2, int a3, int a4);
lua_pcallProto lua_pcall = (lua_pcallProto)(GetProcAddress(lua_sharedModule, "lua_pcall"));

typedef lua_State* (__fastcall* lua_newthreadProto)(lua_State* luaState);
lua_newthreadProto lua_newthread = (lua_newthreadProto)(GetProcAddress(lua_sharedModule, "lua_newthread"));

typedef int(__fastcall* luaL_loadbufferProto)(lua_State* luaState, const char* buffer, size_t size, const char* name);
luaL_loadbufferProto luaL_loadbuffer = (luaL_loadbufferProto)(GetProcAddress(lua_sharedModule, "luaL_loadbuffer"));

typedef void(__fastcall* lua_settopProto)(lua_State* luaState, int a2);
lua_settopProto lua_settop = (lua_settopProto)(GetProcAddress(lua_sharedModule, "lua_settop"));

typedef int(__fastcall* lua_closeProto)(lua_State* luaState);
lua_closeProto lua_close = (lua_closeProto)(GetProcAddress(lua_sharedModule, "lua_close"));

typedef int(__fastcall* lua_getfieldProto)(lua_State* luaState, int index, const char* k);
lua_getfieldProto lua_getfield = (lua_getfieldProto)(GetProcAddress(lua_sharedModule, "lua_getfield"));

typedef int(__fastcall* lua_typeProto)(lua_State* luaState, int index);
lua_typeProto lua_type = (lua_typeProto)(GetProcAddress(lua_sharedModule, "lua_type"));

typedef int(__fastcall* lua_tobooleanProto)(lua_State* luaState, int index);
lua_tobooleanProto lua_toboolean = (lua_tobooleanProto)(GetProcAddress(lua_sharedModule, "lua_toboolean"));

typedef void(__fastcall* lua_createtableProto)(lua_State* luaState, int narray, int nrec);
lua_createtableProto lua_createtable = (lua_createtableProto)(GetProcAddress(lua_sharedModule, "lua_createtable"));

typedef void(__fastcall* lua_pushlstringProto)(lua_State* luaState, const char* s, size_t len);
lua_pushlstringProto lua_pushlstring = (lua_pushlstringProto)(GetProcAddress(lua_sharedModule, "lua_pushlstring"));

typedef void(__fastcall* lua_settableProto)(lua_State* luaState, int index);
lua_settableProto lua_settable = (lua_settableProto)(GetProcAddress(lua_sharedModule, "lua_settable"));

typedef void(__fastcall* lua_setmetatableProto)(lua_State* luaState, int index);
lua_setmetatableProto lua_setmetatable = (lua_setmetatableProto)(GetProcAddress(lua_sharedModule, "lua_setmetatable"));

typedef void(__fastcall* lua_replaceProto)(lua_State* luaState, int index);
lua_replaceProto lua_replace = (lua_replaceProto)(GetProcAddress(lua_sharedModule, "lua_replace"));

typedef void(__fastcall* lua_pushvalueProto)(lua_State* luaState, int index);
lua_pushvalueProto lua_pushvalue = (lua_pushvalueProto)(GetProcAddress(lua_sharedModule, "lua_pushvalue"));

MAYBE_GMOD_RUNTIME_SETUP_PROTO MAYBE_GMOD_RUNTIME_SETUP_PTR = nullptr;

typedef void(__fastcall* GMOD_LUA_STACK_CHECK_PROTO)(int a1);
GMOD_LUA_STACK_CHECK_PROTO GMOD_LUA_STACK_CHECK = (GMOD_LUA_STACK_CHECK_PROTO)(lua_sharedBase + 0x93F0);
GMOD_LUA_STACK_CHECK_PROTO GMOD_LUA_STACK_CHECK_PTR = nullptr;

lua_closeProto lua_close_PTR = nullptr;
lua_pcallProto lua_pcall_PTR = nullptr;

lua_State* currentLuaState = nullptr;

#define lua_getglobal(L,s)	lua_getfield(L, LUA_GLOBALSINDEX, (s))
#define lua_pop(L,n)		lua_settop(L, -(n)-1)
#define lua_isboolean(L,n)	(lua_type(L, (n)) == LUA_TBOOLEAN)
#define lua_newtable(L)lua_createtable(L,0,0)
#define lua_pushliteral(L,s)lua_pushlstring(L,s,(sizeof(s)/sizeof(char))-1)

int MAYBE_GMOD_RUNTIME_SETUP_HOOK(int arg1, int arg2)
{
    int result = MAYBE_GMOD_RUNTIME_SETUP_PTR(arg1, arg2);

    //DWORD state = (DWORD)(arg1 + 8);

    //currentLuaState = *(lua_State**)state;

    return result;
}

int lua_close_HOOK(lua_State* luaState)
{
    if (currentLuaState == luaState){
        currentLuaState = nullptr;
    };

	return lua_close_PTR(luaState);
}

bool isLuaStateActive() {
	return currentLuaState != nullptr;
}

void GMOD_LUA_STACK_CHECK_HOOK(int a1)
{
}

void lua_sandbox_thread(lua_State* luaState) {
    lua_newtable(luaState);
    lua_newtable(luaState);

    lua_pushliteral(luaState, "__index");
    lua_pushvalue(luaState, LUA_GLOBALSINDEX);

    lua_settable(luaState, -3);
    lua_setmetatable(luaState, -2);

    lua_replace(luaState, LUA_GLOBALSINDEX);
}

std::string currentScript = "";

int lua_pcall_HOOK(lua_State* luaState, int a2, int a3, int a4)
{

    if (currentLuaState != luaState) {
        currentLuaState = luaState;
    }

    int result = lua_pcall_PTR(luaState, a2, a3, a4);

    lua_getfield(luaState, LUA_GLOBALSINDEX, "CLIENT");
    if (lua_isboolean(luaState, -1)) {
        bool isClient = lua_toboolean(luaState, -1);

        if (currentScript != "" && isClient) {
            lua_State* customLuaState = lua_newthread(luaState);
            lua_sandbox_thread(customLuaState);

            int result = luaL_loadbuffer(customLuaState, currentScript.c_str(), currentScript.size(), "@gmod");
            int pcallResult = lua_pcall_PTR(customLuaState, 0, 0, 0);

            currentScript = "";
        }
    }

    lua_pop(luaState, 1);

    return result;
}

namespace executor{
    void executeLua(std::string scriptToExecute) {
        if (isLuaStateActive()) {
            currentScript = scriptToExecute;
        }
    }
}