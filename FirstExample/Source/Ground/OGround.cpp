
#include "OGround.h"
#include "../../Engine/Component/PrimitiveComponent.h"

OGround::OGround(Transform transform) : Object(transform) {
    addComponent(new PrimitiveComponent (EPrimitiveType::PLANE, this, Transform(), this->GroundTexture));
}