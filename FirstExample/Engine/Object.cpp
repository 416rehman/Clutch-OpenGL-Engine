
#include "Object.h"
#include "Component/SceneComponent.h"

struct Transform Object::getTransform() { return transform; }

void Object::setTransform(struct Transform inTransform) { transform = inTransform; }

void Object::addComponent(SceneComponent* component) {
    if (rootComponent == nullptr) {
        rootComponent = component;
    } else{
        component->attachTo(rootComponent);
    }
}

void Object::removeComponent(SceneComponent* component) {
    if (rootComponent == component) {
        rootComponent = nullptr;
    } else {
        component->detachFromParent();
    }
}

// starting from root component, recursively draw all children
void Object::draw(glm::mat4 &modelMatrix, GLint &modelMatrixUniformLocation) {
    auto objectModelMatrix = glm::mat4(1.0f);
    objectModelMatrix = glm::translate(objectModelMatrix, transform.getPosition());
    objectModelMatrix = glm::scale(objectModelMatrix, transform.getScale());
    objectModelMatrix = glm::rotate(objectModelMatrix, transform.getRotation().x, glm::vec3(1, 0, 0));
    objectModelMatrix = glm::rotate(objectModelMatrix, transform.getRotation().y, glm::vec3(0, 1, 0));
    objectModelMatrix = glm::rotate(objectModelMatrix, transform.getRotation().z, glm::vec3(0, 0, 1));

    modelMatrix = modelMatrix * objectModelMatrix;

    if (rootComponent != nullptr) {
        rootComponent->drawAll(modelMatrix, modelMatrixUniformLocation);
    }

    modelMatrix = glm::mat4(1.0f);  // reset model matrix
}

void Object::tick(float deltaTime) {
    onTick(deltaTime);
    if (rootComponent != nullptr) {
        rootComponent->tick(deltaTime);
    }
}
