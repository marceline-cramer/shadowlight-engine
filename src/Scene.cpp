#include "Scene.hpp"

#include "ComponentScript.hpp"

void Scene::load(LuaBinding* lua)
{
    auto entity = new Entity();

    auto componentScript = new ComponentScript();
    componentScript->init(lua);
    entity->addComponent(componentScript);

    addEntity(entity);
}

void Scene::update()
{
    for(auto it : entities) {
        it->update();
    }
}

void Scene::addEntity(Entity* e)
{
    entities.insert(e);
}
