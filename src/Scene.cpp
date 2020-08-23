#include "Scene.hpp"

void Scene::load()
{

}

void Scene::update()
{
    for(auto it = entities.begin(); it != entities.end(); it++) {
        (*it)->update();
    }
}
