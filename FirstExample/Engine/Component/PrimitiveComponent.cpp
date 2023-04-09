
#include "PrimitiveComponent.h"

void PrimitiveComponent::draw(glm::mat4 &modelMatrix, GLint &modelMatrixUniformLocation) {
    switch (type) {
        case EPrimitiveType::PLANE:
            glUniformMatrix4fv(modelMatrixUniformLocation, 1, GL_FALSE, &modelMatrix[0][0]);

            // Set the texture
            glBindTexture(GL_TEXTURE_2D, textureResource->getTextureID());
            glDrawArrays(GL_QUADS, 0, 4);

            // Unbind the texture
            break;
    }

}
