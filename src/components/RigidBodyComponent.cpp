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

RigidBodyComponent::RigidBodyComponent(BulletInstance* _bti)
{
    bti = _bti;
}

RigidBodyComponent::~RigidBodyComponent()
{
    bti->world->removeRigidBody(body);
    delete body;
    delete shape;
}

void RigidBodyComponent::finalize(ComponentSet&)
{
    mass = 1;
    shape = new btBoxShape(btVector3(1, 1, 1));

    btTransform startTransform;
    //btVector3 startOrigin = {transform->position.x, transform->position.y, transform->position.z};
    btVector3 startOrigin = {0.0, 0.0, 0.0};
    startTransform.setIdentity();
    startTransform.setOrigin(startOrigin);

    btVector3 localInertia;
    shape->calculateLocalInertia(mass, localInertia);

    motionState = new btDefaultMotionState(startTransform);

    // Create body
    // TODO Bullet error checking
    btRigidBody::btRigidBodyConstructionInfo constructionInfo(mass, motionState, shape, localInertia);
    body = new btRigidBody(constructionInfo);
    bti->world->addRigidBody(body);
}

void RigidBodyComponent::createBindings(lua_State* L)
{
    // RigidBody.getCenterOfMassPosition
    lua_pushstring(L, "getCenterOfMassPosition");
    lua_pushlightuserdata(L, body);
    lua_pushcclosure(L, RigidBodyComponent_getCenterOfMassPosition, 1);
    lua_settable(L, -3);
}

void RigidBodyComponent::setTransform(EntityTransform)
{
    // TODO RigidBody position from EntityTransform
}

void RigidBodyComponent::getTransform(EntityTransform* transform)
{
    auto bodyTransform = body->getCenterOfMassTransform();
    auto position = bodyTransform.getOrigin();
    auto rotation = bodyTransform.getRotation();

    transform->position = glm::vec3(position.x(), position.y(), position.z());
    transform->orientation = glm::quat(rotation.x(), rotation.y(), rotation.z(), rotation.w());
}
