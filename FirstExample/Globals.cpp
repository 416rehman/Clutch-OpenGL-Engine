#include "Globals.h"
#include "glm/detail/func_geometric.hpp"

namespace Globals {
    char* WINDOW_TITLE = "LAB 9";
    GLuint BufferIDs[MAX_BUFFERS];  // one for vertices, another for texCoords
    std::vector<TextureData> Textures = {
            { 0, "grass.png" },
            { 0, "apple.png" }
    };
    std::vector<Object*> SceneGraph;
    GLuint ShaderProgram;
    namespace Matrix {
        glm::mat4 Model;    // Model matrix - converts from local space to world space
        glm::mat4 View;     // View matrix - converts from world space to camera space
        glm::mat4 Projection;   // Projection matrix - converts from camera space to screen space
        namespace UniformLocation {
            GLint Model;   // Location of Model matrix in shader
            GLint View;    // Location of View matrix in shader
            GLint Projection;  // Location of Projection matrix in shader
        }
    }
    namespace Camera {
        glm::vec3 Position = glm::vec3(-30.0f, 0.0f, 20.0f);
        glm::vec3 ForwardVector = glm::vec3(1, 1, 0);
        glm::vec3 UpVector = glm::vec3(0, 0, 1);
        glm::vec3 RightVector = glm::cross(UpVector, ForwardVector);
        glm::vec3 Target = glm::vec3(1, 1, 0);
        GLfloat Speed = 300.0f;
    }
    namespace Time {
        int DeltaTime;
        int TimeSinceStart;
    }
    namespace Mouse {
        //vec2 for x and y;
        glm::vec2 Position = glm::vec2(0, 0);
        GLfloat Sensitivity = 0.01f;
    }

}