// Example #include "Libs/Closure/Closure.hpp"
// Define C Env in wtvr this is the closure env
void CEnvironment::Initialize(lua_State* L) {
    //NameSpace::Environment::closures::Initialize(L);


    lua_newtable(L);
    lua_setglobal(L, "_G");

    lua_newtable(L);
    lua_setglobal(L, "shared");
}