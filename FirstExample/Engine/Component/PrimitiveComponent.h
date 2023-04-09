
#ifndef CLUTCH_PRIMITIVECOMPONENT_H
#define CLUTCH_PRIMITIVECOMPONENT_H


#include "SceneComponent.h"

enum class EPrimitiveType {
    PLANE
};

class PrimitiveComponent : public SceneComponent {
    EPrimitiveType type;
public:
    PrimitiveComponent(EPrimitiveType type, Object* compOwner, Transform relativeTransform, TextureResource* inTextureResource) : SceneComponent(compOwner, relativeTransform, inTextureResource) {
        this->type = type;
    }

    void draw(glm::mat4& modelMatrix, GLint& modelMatrixUniformLocation) override;
    void onTick(float deltaTime) override {}
};


#endif //CLUTCH_PRIMITIVECOMPONENT_H
