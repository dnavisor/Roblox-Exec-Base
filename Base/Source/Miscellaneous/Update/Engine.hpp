#pragma once

#include <Windows.h>
#include <iostream>
#include <vector>

#define REBASE(x) x + (uintptr_t)GetModuleHandle(nullptr)
#define MAX_CAPABILITIES (uintptr_t)(0x200000000000003FLL | 0x3FFFFFF00LL)

struct lua_State;
struct Proto;

namespace Update {
    const uintptr_t GetTaskScheduler = REBASE(0x2DE45A0); // Updated 2.7.25

    const uintptr_t GetGlobalStateForInstance = REBASE(0xD46D10); // Updated 2.7.25
    const uintptr_t DecryptState = REBASE(0xB36630); // Updated 2.7.25

    const uintptr_t GetContextObject = REBASE(0xD622A0); // Updated 2.7.25 0xC3B6C0
    const uintptr_t SetProtoCapabilities = REBASE(0xC3B6C0); // Updated 2.7.25

    const uintptr_t LuaVM__Load = REBASE(0xB39620); // Updated 2.7.25
    const uintptr_t Task__Defer = REBASE(0xF0ADE0); // Updated 2.7.25

    const uintptr_t ContextObject = 0x648; // Updated 2.7.25
    namespace ExtraSpace {
        const uintptr_t Identity = 0x30; // NEVER
        const uintptr_t Capabilities = 0x48; // NEVER
        const uintptr_t Script = 0x50; // NEVER
        const uintptr_t Actor = 0x58; // NEVER
    }

    namespace TaskScheduler {
        const uintptr_t JobsStart = 0x1c8; // Updated 2.7.25
        const uintptr_t JobName = 0x90; // Updated 2.7.25

        const uintptr_t ScriptContextJob = 0x1F8;
        const uintptr_t RenderView = 0x218; // Updated 2.7.25 .. RenderJobToRenderView
    }

    namespace ScriptContext {
        const uintptr_t GlobalState = 0x120; // Updated 2.7.25
        const uintptr_t DecryptState = 0x88; // Updated 2.7.25
    }

    namespace DataModel {
        const uintptr_t Padding = 0x118; // NEVER
        const uintptr_t Instance = 0x1A8; // NEVER

        const uintptr_t PlaceId = 0x170; // Updated 2.7.25
        const uintptr_t ScriptContext = 0x3C0; // Updated 2.7.25

        namespace Information {
            const uintptr_t ClassDescriptor = 0x18; // Updated 2.7.25
            const uintptr_t ClassName = 0x8; // NEVER

            const uintptr_t Children = 0x70; // Updated 2.7.25
            const uintptr_t Parent = 0x50; // Updated 2.7.25
        }
    }
}

namespace RBX {
    using TGetTaskScheduler = uintptr_t(__fastcall*)();
    inline auto GetTaskScheduler = (TGetTaskScheduler)Update::GetTaskScheduler;

    using TGetGlobalStateForInstance = uintptr_t(__fastcall*)(uintptr_t, uintptr_t*, uintptr_t*);
    inline auto GetGlobalStateForInstance = (TGetGlobalStateForInstance)Update::GetGlobalStateForInstance;

    using TDecryptState = lua_State * (__fastcall*)(uintptr_t);
    inline auto DecryptState = (TDecryptState)Update::DecryptState;

    using TGetContextObject = uintptr_t(__fastcall*)(uintptr_t, uintptr_t);
    inline auto GetContextObject = (TGetContextObject)Update::GetContextObject;

    using TSetProtoCapabilities = void(__fastcall*)(Proto*, uintptr_t);
    inline auto SetProtoCapabilities = (TSetProtoCapabilities)Update::SetProtoCapabilities;

    using TLuaVM__Load = int(__fastcall*)(lua_State*, void*, const char*, int);
    inline auto LuaVM__Load = (TLuaVM__Load)Update::LuaVM__Load;

    using TTask__Defer = int(__fastcall*)(lua_State*);
    inline auto Task__Defer = (TTask__Defer)Update::Task__Defer;
    __forceinline static void pushint(lua_State* L, double num) {
        TValue* Top = (TValue*)(L->top);
        Top->tt = LUA_TNUMBER;
        Top->value.n = num;
        L->top++;
    }

    // maybe?
    //inline __int64 GetThreadIdentity(lua_State* L) {
    //    uintptr_t Userdata = *(uintptr_t*)(L + 0x78);
    //    uintptr_t* identitycap = reinterpret_cast<uintptr_t*>(Userdata + 0x30);
    //    *identitycap = 8;
    //    pushint(L, (double)(*identitycap));
    //    return 1;
    //}

    inline void SetThreadIdentity(uintptr_t L, uintptr_t Identity) {
        uintptr_t Userdata = *(uintptr_t*)(L + 0x78);

        uintptr_t* identitycap = reinterpret_cast<uintptr_t*>(Userdata + 0x30);
        *identitycap = 8;
    }

    inline void SetThreadCapabilities(uintptr_t L, uintptr_t Capabilities) {
        uintptr_t Userdata = *(uintptr_t*)(L + 0x78);
        *reinterpret_cast<std::int64_t*>(Userdata + 0x48) = Capabilities;
    }
}