
#ifndef CLUTCH_CAR_H
#define CLUTCH_CAR_H

#include "../../Engine/Object.h"
#include "../../Engine/Types.h"

class OCar : public Object {
    float maxSpeed = 0.001f;
public:
    TextureResource* bodyTexture = new TextureResource();
    TextureResource* wheelTexture = new TextureResource();

    OCar(Transform transform = Transform());
    void onTick(float deltaTime) override;
};


#endif //CLUTCH_CAR_H
