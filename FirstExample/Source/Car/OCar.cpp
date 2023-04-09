#include "OCar.h"
#include "../../Engine/Component/PrimitiveComponent.h"
#include "components/WheelComponent.h"

OCar::OCar(Transform transform) : Object(transform) {
    // Center plane
    addComponent(new PrimitiveComponent (EPrimitiveType::PLANE, this, Transform(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(10.0f, 4.0f, 1.f)), this->bodyTexture));

    // Wheels
    addComponent(new WheelComponent(this, Transform(glm::vec3(1.f, 1.f, -0.1f), glm::vec3(1.f)), this->wheelTexture));
    addComponent(new WheelComponent(this, Transform(glm::vec3(1.f, -1.f, -0.1f), glm::vec3(1.f) ), this->wheelTexture));
    addComponent(new WheelComponent(this, Transform(glm::vec3(-1.f, 1.f, -0.1f), glm::vec3(1.f) ), this->wheelTexture));
    addComponent(new WheelComponent(this, Transform(glm::vec3(-1.f, -1.f, -0.1f), glm::vec3(1.f)), this->wheelTexture));
}

void OCar::onTick(float deltaTime) {
    // Randomly move the car towards its forward vector
    transform.setPosition(transform.getPosition() + transform.getForwardVector() * (float)rand() / (float)RAND_MAX * maxSpeed * deltaTime);
    // Rotate
    transform.setRotation(transform.getRotation() + glm::vec3(0.f, 0.f, 0.01f) * (float)rand() / (float)RAND_MAX * maxSpeed * deltaTime);
}
