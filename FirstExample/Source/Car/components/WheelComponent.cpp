
#include "WheelComponent.h"


void WheelComponent::onTick(float deltaTime) {
    PrimitiveComponent::onTick(deltaTime);
    this->getTransform()->setRotation(this->getTransform()->getRotation() + glm::vec3(0., rotationSpeed, 0.) * deltaTime);
}
