#include "luser.h"

#define luser_c
#define LUA_CORE

#include "lua.h"

#include "lmem.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>


typedef struct user_State {
	CRITICAL_SECTION* gcs;
} user_State;


#define fromstate(l)	(*cast(user_State**, (cast(lu_byte *, (l)) - LUAI_EXTRASPACE)))


void luaU_lock(lua_State* L)
{
	user_State* U = fromstate(L);
	EnterCriticalSection(U->gcs);
}
void luaU_unlock(lua_State* L)
{
	user_State* U = fromstate(L);
	LeaveCriticalSection(U->gcs);
}

void luaU_userstateopen(lua_State* L)
{
	user_State* U = fromstate(L) = luaM_new(L, user_State);
	U->gcs = luaM_new(L, CRITICAL_SECTION);
	InitializeCriticalSection(U->gcs);
}
void luaU_userstateclose(lua_State* L)
{
	user_State* U = fromstate(L);
	DeleteCriticalSection(U->gcs);
	luaM_free(L, U->gcs);
	luaM_free(L, U);
}
void luaU_userstatethread(lua_State* L, lua_State* L1)
{
	user_State* U = fromstate(L);
	user_State* U1 = fromstate(L1) = luaM_new(L1, user_State);
	U1->gcs = U->gcs;
}
void luaU_userstatefree(lua_State* L)
{
	user_State* U = fromstate(L);
	U->gcs = NULL;
	luaM_free(L, U);
}
void luaU_userstateresume(lua_State* L)
{}
void luaU_userstateyield(lua_State* L)
{}
