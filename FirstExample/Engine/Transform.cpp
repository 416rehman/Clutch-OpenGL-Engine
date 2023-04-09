
#include "Transform.h"
#include "glm/gtc/quaternion.hpp"

glm::vec3 Transform::getPosition() { return position; }

void Transform::setPosition(glm::vec3 inPosition) { position = inPosition; }

glm::vec3 Transform::getScale() { return scale; }

void Transform::setScale(glm::vec3 inScale) { scale = inScale; }

glm::vec3 Transform::getRotation() { return rotation; }

void Transform::setRotation(glm::vec3 inRotation) { rotation = inRotation; }

glm::vec3 Transform::getForwardVector() {
    // if rotation is 0,0,0, then forward vector is 1, 0, 0, otherwise use rotation to calculate forward vector
    if (rotation == glm::vec3(0.0f, 0.0f, 0.0f)) {
        return glm::vec3(1.0f, 0.0f, 0.0f);
    } else {
        auto rotationMatrix  = glm::mat4_cast(glm::quat(rotation));
        return glm::vec3(rotationMatrix * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    }
}

glm::vec3 Transform::getUpVector() {
    if (rotation == glm::vec3(0.0f, 0.0f, 0.0f)) {
        return glm::vec3(0.0f, 1.0f, 0.0f);
    } else {
        auto rotationMatrix  = glm::mat4_cast(glm::quat(rotation));
        return glm::vec3(rotationMatrix * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
    }
}

glm::vec3 Transform::getRightVector() {
    // cross product of forward and up vectors
    return glm::cross(getForwardVector(), getUpVector());
}
