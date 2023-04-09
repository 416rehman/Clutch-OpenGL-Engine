
#ifndef CLUTCH_SCENECOMPONENT_H
#define CLUTCH_SCENECOMPONENT_H


#include "vgl.h"
#include <string>
#include "../Transform.h"
#include "glm/gtc/matrix_transform.hpp"
#include "GL/glew.h"
#include "../Object.h"
#include "ObjectComponent.h"
#include "../Types.h"

class SceneComponent : public ObjectComponent {
protected:
    // the object that owns this component
    Object* owner{};
    Transform transform; // Relative to the owner

    TextureResource* textureResource = new TextureResource();

    SceneComponent* attachParent{}; // the scene component that this component is attached to
    std::vector<SceneComponent*> attachChildren{};  // the scene components that are attached to this component

    virtual void draw(glm::mat4& modelMatrix, GLint& modelMatrixUniformLocation) = 0; // the logic to draw this component
public:
    SceneComponent() = default;
    SceneComponent(Object* compOwner, Transform relativeTransform, TextureResource* inTextureResource) :
            owner(compOwner), transform(relativeTransform), textureResource(inTextureResource) {}

    Object* getOwner();
    void setOwner(Object* inOwner);
    struct Transform* getTransform();                   // Relative to the owner
    void setTransform(struct Transform inTransform);    // Relative to the owner
    struct Transform getAbsoluteTransform();            // Calculated from the owner's transform
    TextureResource* getTextureResource();
    void setTextureResource(TextureResource* textureData);

    virtual void drawAll(glm::mat4& parentModelMatrix, GLint& modelMatrixUniformLocation);

    Transform getTransformConst() const;
    std::vector<SceneComponent*> getAttachChildren() const;
    void attachTo(SceneComponent* parent);
    void detachFromParent();
    void tick(float deltaTime) override;
};



#endif //CLUTCH_SCENECOMPONENT_H
