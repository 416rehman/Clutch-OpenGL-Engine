
#ifndef CLUTCH_WHEEL_H
#define CLUTCH_WHEEL_H


#include "../../../Engine/Component/PrimitiveComponent.h"

class WheelComponent : public PrimitiveComponent {
    float rotationSpeed = 0.001;
public:
    WheelComponent(Object* compOwner, Transform relativeTransform, TextureResource* inTextureResource) : PrimitiveComponent(EPrimitiveType::PLANE, compOwner, relativeTransform, inTextureResource) {}
    void onTick(float deltaTime) override;
};


#endif //CLUTCH_WHEEL_H
