#include "OCar.h"
#include "../../Engine/Component/PrimitiveComponent.h"
#include "components/WheelComponent.h"

OCar::OCar(Transform transform) : Object(transform) {
    // Center plane
    addComponent(new PrimitiveComponent (EPrimitiveType::PLANE, this, Transform(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(10.0f, 4.0f, 0.f)), this->bodyTexture));

    // Wheels
    addComponent(new WheelComponent(this, Transform(glm::vec3(1.f, 1.f, 10.f), glm::vec3(0.20f)), this->wheelTexture));
    addComponent(new WheelComponent(this, Transform(glm::vec3(1.f, -1.f, 10.f), glm::vec3(0.20f) ), this->wheelTexture));
    addComponent(new WheelComponent(this, Transform(glm::vec3(-1.f, 1.f, 10.f), glm::vec3(0.20f) ), this->wheelTexture));
    addComponent(new WheelComponent(this, Transform(glm::vec3(-1.f, -1.f, 10.f), glm::vec3(0.20f)), this->wheelTexture));
}

void OCar::onTick(float deltaTime) {
//    // Randomly move the car towards its direction
//    transform.setPosition(transform.getPosition() + transform.getForwardVector() * maxSpeed * deltaTime);
//    // Randomly rotate the car
//    transform.setRotation(transform.getRotation() + glm::vec3(0.f, 0.f, 1.f) * (float)rand() / (float)RAND_MAX * maxSpeed * deltaTime);
}
