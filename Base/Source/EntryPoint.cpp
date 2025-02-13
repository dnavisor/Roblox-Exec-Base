#include <Windows.h>

#include <RBX.hpp>
#include <ThreadPool.hpp>
#include <Environment/Environment.hpp>
#include <thread>  


void func() {}

extern "C" __declspec(dllexport) LRESULT Hook(int Code, WPARAM WParam, LPARAM LParam) {
    std::thread(func).detach();

    return CallNextHookEx(nullptr, Code, WParam, LParam);
}

void initluastate() {
    RBX::Scheduler->Initialize();

    auto ScriptContext = RBX::Scheduler->GetScriptContext();

    uintptr_t StateIndex[] = { 0 };
    uintptr_t ActorIndex[] = { 0, 0 };

    uint64_t encState = RBX::GetGlobalStateForInstance(ScriptContext + Update::ScriptContext::GlobalState, StateIndex, ActorIndex);
    lua_State* L = RBX::DecryptState(encState + Update::ScriptContext::DecryptState);
    lua_State* ExploitThread = Execution->NewThread(L);
    luaL_sandboxthread(ExploitThread);

    Manager->SetLuaState(ExploitThread);
    RBX::Scheduler->HookJob("Heartbeat");

    Environment->Initialize(Manager->GetLuaState());
}

void MainThread(HMODULE Module) {
#define offset_to_0(x)  x  + (uintptr_t)GetModuleHandle(NULL)

    initluastate();

    bool reinit = false;

    while (true) {

     

        Sleep(50);
    } // run
}

bool __stdcall DllMain(HMODULE Module, uintptr_t Reason, void*) {
    if (Reason == DLL_PROCESS_ATTACH)
        ThreadPool->Run(MainThread, Module);

    return true;
}