
#ifndef CLUTCH_GLOBALS_H
#define CLUTCH_GLOBALS_H

#include <vector>
#include "glm/detail/type_mat4x4.hpp"
#include "glm/vec3.hpp"
#include "GL/glew.h"
#include "Engine/Types.h"

/**
 * This file contains all global variables and constants marked as extern.
 */
class Object;

namespace Globals {
    const int MAX_BUFFERS = 2;
    extern char* WINDOW_TITLE;
    extern GLuint BufferIDs[MAX_BUFFERS];  // one for vertices, another for texCoords
    extern std::vector<TextureData> Textures;
    extern std::vector<Object*> SceneGraph;
    extern GLuint ShaderProgram;
    namespace Matrix {
        extern glm::mat4 Model;    // Model matrix - converts from local space to world space
        extern glm::mat4 View;     // View matrix - converts from world space to camera space
        extern glm::mat4 Projection;   // Projection matrix - converts from camera space to screen space
        namespace UniformLocation {
            extern GLint Model;   // Location of Model matrix in shader
            extern GLint View;    // Location of View matrix in shader
            extern GLint Projection;  // Location of Projection matrix in shader
        }
    }
    namespace Camera {
        extern glm::vec3 Position;
        extern glm::vec3 ForwardVector;
        extern glm::vec3 UpVector;
        extern glm::vec3 RightVector;
        extern glm::vec3 Target;
        extern GLfloat Speed;
    }
    namespace Time {
        extern int DeltaTime;
        extern int TimeSinceStart;
    }
    namespace Mouse {
        //vec2 for x and y;
        extern glm::vec2 Position;
        extern GLfloat Sensitivity;
    }
}

#endif //CLUTCH_GLOBALS_H
