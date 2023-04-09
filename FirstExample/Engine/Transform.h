
#ifndef CLUTCH_TRANSFORM_H
#define CLUTCH_TRANSFORM_H


#include "glm/vec3.hpp"
#include "glm/detail/func_geometric.hpp"

enum Axis {
    X,
    Y,
    Z
};

struct Transform {
private:
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);

public:
    Transform() = default;
    explicit Transform(glm::vec3 position, glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f)) : position(position), scale(scale), rotation(rotation) {}

    glm::vec3 getPosition();
    void setPosition(glm::vec3 inPosition);
    glm::vec3 getScale();
    void setScale(glm::vec3 inScale);
    glm::vec3 getRotation();
    void setRotation(glm::vec3 inRotation);

    glm::vec3 getForwardVector();
    glm::vec3 getUpVector();
    glm::vec3 getRightVector();
};


#endif //CLUTCH_TRANSFORM_H
