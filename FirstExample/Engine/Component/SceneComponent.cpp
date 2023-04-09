
#include "SceneComponent.h"

Object *SceneComponent::getOwner() { return owner; }

void SceneComponent::setOwner(Object *inOwner) { owner = inOwner; }

struct Transform *SceneComponent::getTransform() { return &transform; }
struct Transform SceneComponent::getTransformConst() const { return transform; }

void SceneComponent::setTransform(struct Transform inTransform) { transform = inTransform;}

struct Transform SceneComponent::getAbsoluteTransform() {
    auto ownerTransform = owner->getTransform();
    return Transform{
            ownerTransform.getPosition() + transform.getPosition(),
            ownerTransform.getScale() * transform.getScale(),
            ownerTransform.getRotation() + transform.getRotation()
    };
}

void SceneComponent::setTextureResource(TextureResource *textureData) {
    this->textureResource = textureData;
}

TextureResource *SceneComponent::getTextureResource() {
    return textureResource;
}

std::vector<SceneComponent *> SceneComponent::getAttachChildren() const {
    return std::vector<SceneComponent *>();
}

void SceneComponent::attachTo(SceneComponent *parent) {
    attachParent = parent;
    parent->attachChildren.push_back(this);
}


void SceneComponent::detachFromParent() {
    if (attachParent != nullptr) {
        attachParent->attachChildren.erase(std::remove(attachParent->attachChildren.begin(), attachParent->attachChildren.end(), this), attachParent->attachChildren.end());
        attachParent = nullptr;
    }
}

void SceneComponent::drawAll(glm::mat4& parentModelMatrix, GLint &modelMatrixUniformLocation) {
    auto modelMatrix = glm::mat4(1.0f);

    modelMatrix = glm::translate(modelMatrix, transform.getPosition());
    if (attachParent == nullptr) {  // only scale the root component. This scale is multiplied by the parent's scale.
        if (getOwner()) {
            modelMatrix = glm::scale(modelMatrix, transform.getScale());
        }
    }
    else {
        // do not scale other components by their parent's scale. We divide this scale by the parent's scale so when we multiply the parent's scale, it will cancel out.
        modelMatrix = glm::scale(modelMatrix, transform.getScale() / attachParent->transform.getScale());
    }

    modelMatrix = glm::rotate(modelMatrix, transform.getRotation().x, glm::vec3(1, 0, 0));
    modelMatrix = glm::rotate(modelMatrix, transform.getRotation().y, glm::vec3(0, 1, 0));
    modelMatrix = glm::rotate(modelMatrix, transform.getRotation().z, glm::vec3(0, 0, 1));

    modelMatrix = parentModelMatrix * modelMatrix;  // apply parent model matrix to this component

    // draw this component
    this->draw(modelMatrix, modelMatrixUniformLocation);

    // draw all children
    if (!attachChildren.empty()) {
        for (auto child : attachChildren) {
            child->drawAll(modelMatrix, modelMatrixUniformLocation);
        }
    }
}

void SceneComponent::tick(float deltaTime) {
    ObjectComponent::tick(deltaTime);

    this->onTick(deltaTime);
    if (!attachChildren.empty()) {
        for (auto child : attachChildren) {
            child->tick(deltaTime);
        }
    }
}