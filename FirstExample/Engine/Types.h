
#ifndef CLUTCH_TYPES_H
#define CLUTCH_TYPES_H

#include "GL/glew.h"

struct TextureData {
    GLuint textureID;
    const char* texturePath;
};

struct TextureResource {
    TextureData* textureData;

    GLuint getTextureID() const {
        if (textureData == nullptr) {
            return 0;
        }
        return textureData->textureID;
    }
};

#endif //CLUTCH_TYPES_H
