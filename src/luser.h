#pragma once


typedef struct lua_State lua_State;
typedef struct user_State user_State;

#undef LUAI_EXTRASPACE
#define LUAI_EXTRASPACE sizeof(user_State*)

void luaU_lock(lua_State* L);
void luaU_unlock(lua_State* L);

#define lua_lock(L) luaU_lock(L)
#define lua_unlock(L) luaU_unlock(L)

void luaU_userstateopen(lua_State* L);
void luaU_userstateclose(lua_State* L);
void luaU_userstatethread(lua_State* L, lua_State* L1);
void luaU_userstatefree(lua_State* L);
void luaU_userstateresume(lua_State* L);
void luaU_userstateyield(lua_State* L);


#undef luai_userstateopen
#undef luai_userstateclose
#undef luai_userstatethread
#undef luai_userstatefree
#undef luai_userstateresume
#undef luai_userstateyield

#define luai_userstateopen(L)		luaU_userstateopen(L)
#define luai_userstateclose(L)		luaU_userstateclose(L)
#define luai_userstatethread(L,L1)	luaU_userstatethread(L, L1)
#define luai_userstatefree(L)		luaU_userstatefree(L)
#define luai_userstateresume(L,n)	luaU_userstateresume(L)
#define luai_userstateyield(L,n)	luaU_userstateyield(L)
