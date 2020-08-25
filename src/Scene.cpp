#include "Scene.hpp"

#include "ComponentScript.hpp"

Scene::Scene()
{

}

Scene::~Scene()
{
    
}

void Scene::load(LuaBinding* lua)
{
    auto entity = new Entity();

    auto componentScript = new ComponentScript();
    entity->addComponent(componentScript);
    componentScript->init(lua, entity->components);

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
