#include "RigidBodyComponent.hpp"

static int RigidBodyComponent_getCenterOfMassPosition(lua_State* L)
{
    btRigidBody* body = static_cast<btRigidBody*>(lua_touserdata(L, lua_upvalueindex(1)));
    auto position = body->getCenterOfMassPosition();

    // TODO Lua vectors
    lua_pushnumber(L, position.x());
    lua_pushnumber(L, position.y());
    lua_pushnumber(L, position.z());

    return 3;
}

RigidBodyComponent::RigidBodyComponent(BulletBinding* _bullet, rapidjson::Value& component)
{
    bullet = _bullet;

    mass = 1;
    shape = new btBoxShape(btVector3(1, 1, 1));

    btTransform startTransform;
    startTransform.setIdentity();

    btVector3 localInertia;
    shape->calculateLocalInertia(mass, localInertia);

    motionState = new btDefaultMotionState(startTransform);

    // Create body
    // TODO Bullet error checking
    btRigidBody::btRigidBodyConstructionInfo constructionInfo(mass, motionState, shape, localInertia);
    body = new btRigidBody(constructionInfo);
    bullet->world->addRigidBody(body);
}

RigidBodyComponent::~RigidBodyComponent()
{
    bullet->world->removeRigidBody(body);
    delete body;
    delete shape;
}

void RigidBodyComponent::update()
{
    auto bodyTransform = body->getCenterOfMassTransform();
    auto position = bodyTransform.getOrigin();
    auto rotation = bodyTransform.getRotation();

    transform->position = glm::vec3(position.x(), position.y(), position.z());
    transform->orientation = glm::quat(rotation.x(), rotation.y(), rotation.z(), rotation.w());
}

void RigidBodyComponent::finalize(ComponentSet&, EntityTransform& _transform)
{
    transform = &_transform;
}

void RigidBodyComponent::createBindings(lua_State* L)
{
    // RigidBody.getCenterOfMassPosition
    lua_pushstring(L, "getCenterOfMassPosition");
    lua_pushlightuserdata(L, body);
    lua_pushcclosure(L, RigidBodyComponent_getCenterOfMassPosition, 1);
    lua_settable(L, -3);
}
