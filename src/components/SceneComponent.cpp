#include "components/SceneComponent.hpp"

#include "global/Scene.hpp"

static int SceneComponent_changeScene(lua_State* L)
{
    Scene* scene = static_cast<Scene*>(lua_touserdata(L, lua_upvalueindex(1)));
    const char* sceneName = luaL_checkstring(L, 1);

    scene->loadScene(sceneName);

    return 0;
}

SceneComponent::SceneComponent(Scene* _scene)
{
    scene = _scene;
}

void SceneComponent::createBindings(lua_State* L)
{
    // scene.changeScene
    lua_pushstring(L, "changeScene");
    lua_pushlightuserdata(L, scene);
    lua_pushcclosure(L, SceneComponent_changeScene, 1);
    lua_settable(L, -3);
}
