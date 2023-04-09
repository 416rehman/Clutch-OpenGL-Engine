
#ifndef CLUTCH_GAMEOBJECT_H
#define CLUTCH_GAMEOBJECT_H

#include <vector>
#include "Transform.h"
#include "GL/glew.h"
class SceneComponent;

class Object {
protected:
    // Transform
    Transform transform;
    SceneComponent* rootComponent = nullptr;
public:
    Object() = default;
    explicit Object(Transform transform) : transform(transform) {}
    struct Transform getTransform();
    void setTransform(struct Transform transform);
    void addComponent(SceneComponent* component);
    void removeComponent(SceneComponent* component);
    void draw(glm::mat4& modelMatrix, GLint& modelMatrixUniformLocation);
    virtual void onTick(float deltaTime) = 0;
    virtual void tick(float deltaTime);
};


#endif //CLUTCH_GAMEOBJECT_H
