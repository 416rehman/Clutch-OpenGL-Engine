
#include "Transform.h"

glm::vec3 Transform::getPosition() { return position; }

void Transform::setPosition(glm::vec3 inPosition) { position = inPosition; }

glm::vec3 Transform::getScale() { return scale; }

void Transform::setScale(glm::vec3 inScale) { scale = inScale; }

glm::vec3 Transform::getRotation() { return rotation; }

void Transform::setRotation(glm::vec3 inRotation) { rotation = inRotation; }

glm::vec3 Transform::getUnitVector(Axis axis) {
    switch (axis) {
        case X:
            return glm::vec3(1.0f, 0.0f, 0.0f);
        case Y:
            return glm::vec3(0.0f, 1.0f, 0.0f);
        case Z:
            return glm::vec3(0.0f, 0.0f, 1.0f);
    }
}

glm::vec3 Transform::getForwardVector() {
    return getUnitVector(X);
}

glm::vec3 Transform::getUpVector() {
    return getUnitVector(Y);
}

glm::vec3 Transform::getRightVector() {
    return getUnitVector(Z);
}
