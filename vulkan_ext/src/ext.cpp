#define LIB_NAME "VulkanExt"

#include <dmsdk/sdk.h>

static uint64_t renderTime1;
static uint64_t renderTime2;

static int RenderTime(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 1);

    lua_pushnumber(L, (lua_Number)(((double)renderTime2 - (double)renderTime1) / 1000.0));

    return 1;
}

// Functions exposed to Lua
static const luaL_reg Module_methods[] =
{
    {"render_time", RenderTime},
    {0, 0}
};

static dmExtension::Result OnPreRender(dmExtension::Params *params)
{
    renderTime1 = dmTime::GetTime();
    return dmExtension::RESULT_OK;
}

static dmExtension::Result OnPostRender(dmExtension::Params *params)
{
    renderTime2 = dmTime::GetTime();
    return dmExtension::RESULT_OK;
}

static void LuaInit(lua_State* L)
{
    int top = lua_gettop(L);

    // Register lua names
    luaL_register(L, "vulkan_ext", Module_methods);

    lua_pop(L, 1);
    assert(top == lua_gettop(L));
}

extern "C" {
    void GraphicsAdapterVulkan();
}

static dmExtension::Result AppInitializeVulkanExt(dmExtension::AppParams* params)
{
    dmExtension::RegisterCallback(dmExtension::CALLBACK_PRE_RENDER, OnPreRender);
    dmExtension::RegisterCallback(dmExtension::CALLBACK_POST_RENDER, OnPostRender);
    return dmExtension::RESULT_OK;
}

static dmExtension::Result InitializeVulkanExt(dmExtension::Params* params)
{
    LuaInit(params->m_L);
    return dmExtension::RESULT_OK;
}

static dmExtension::Result AppFinalizeVulkanExt(dmExtension::AppParams* params)
{
    return dmExtension::RESULT_OK;
}

static dmExtension::Result FinalizeVulkanExt(dmExtension::Params* params)
{
    return dmExtension::RESULT_OK;
}

DM_DECLARE_EXTENSION(VulkanExt, LIB_NAME, AppInitializeVulkanExt, AppFinalizeVulkanExt, InitializeVulkanExt, NULL, NULL, FinalizeVulkanExt)

