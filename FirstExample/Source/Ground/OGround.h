
#ifndef CLUTCH_OGROUND_H
#define CLUTCH_OGROUND_H

#include "../../Engine/Object.h"
#include "../../Engine/Types.h"

class OGround : public Object {
public:
    TextureResource* GroundTexture = new TextureResource();

    OGround(Transform transform = Transform());
    void onTick(float deltaTime) override {}
};

#endif //CLUTCH_OGROUND_H
