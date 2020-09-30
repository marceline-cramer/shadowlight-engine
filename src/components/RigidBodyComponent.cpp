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

RigidBodyComponent::RigidBodyComponent(BulletInstance* _bti, RigidBodyConfig* config, AssetHandle<ShapeAsset>& _shapeAsset)
{
    bti = _bti;
    shapeAsset = _shapeAsset;

    btCollisionShape* shape = shapeAsset.getAsset()->shape;

    //// TODO RigidBody origin from config orientation
    btTransform startTransform;
    btVector3 startOrigin = {config->position.x, config->position.y, config->position.z};
    startTransform.setIdentity();
    startTransform.setOrigin(startOrigin);

    btVector3 localInertia;
    mass = config->mass;
    shape->calculateLocalInertia(mass, localInertia);

    motionState = new btDefaultMotionState(startTransform);

    // Create body
    // TODO Bullet error checking
    btRigidBody::btRigidBodyConstructionInfo constructionInfo(mass, motionState, shape, localInertia);
    body = new btRigidBody(constructionInfo);
    bti->world->addRigidBody(body);
}

RigidBodyComponent::~RigidBodyComponent()
{
    bti->world->removeRigidBody(body);
    delete body;
}

void RigidBodyComponent::createBindings(lua_State* L)
{
    // RigidBody.getCenterOfMassPosition
    lua_pushstring(L, "getCenterOfMassPosition");
    lua_pushlightuserdata(L, body);
    lua_pushcclosure(L, RigidBodyComponent_getCenterOfMassPosition, 1);
    lua_settable(L, -3);
}

void RigidBodyComponent::getTransform(EntityTransform* transform)
{
    auto bodyTransform = body->getCenterOfMassTransform();
    auto position = bodyTransform.getOrigin();
    auto rotation = bodyTransform.getRotation();

    transform->position = glm::vec3(position.x(), position.y(), position.z());
    transform->orientation = glm::quat(rotation.x(), rotation.y(), rotation.z(), rotation.w());
}
