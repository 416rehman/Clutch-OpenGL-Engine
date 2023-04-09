/////////////////////////////////////////////////////////////////////////////////////
//
// Developed By Hayaturehman Ahmadzai
// LoadShaders provided by Alireza Moghadem.
//
////////////////////////////////////////////////////////////////////////////////////

using namespace std;

#include "vgl.h"
#include "LoadShaders.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtx\rotate_vector.hpp"
#include "..\SOIL\src\SOIL.h"
#include <iostream>
#include <vector>
#include "Globals.h"
#include "Source/Ground/OGround.h"
#include "Source/Car/OCar.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Code
///////////////////////////////////////////////////////////////////////////////////////////////////////
void InitVerticesBuffer() {// Vertices
    GLfloat vertices[4][3] = {
            { -1.0, -1.0, 0.0 }, //Plane to walk on and a sky
            { 1.0, -1.0, 0.0 },
            { 1.0, 1.0, 0.0 },
            { -1.0, 1.0, 0.0 },
    };

    glBindBuffer(GL_ARRAY_BUFFER, Globals::BufferIDs[0]);  // Bind buffer to GL_ARRAY_BUFFER - All operations from now on will be on this buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);  // Initialize the data store

    GLuint vPositionLoc = glGetAttribLocation(Globals::ShaderProgram, "vPosition");  // Get the location of the attribute
    glBindAttribLocation(Globals::ShaderProgram, vPositionLoc, "vPosition");  // Bind the attribute to the location
    glVertexAttribPointer(vPositionLoc, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));  // Set the attribute from the currently bound buffer
    glEnableVertexAttribArray(vPositionLoc);  // Enable the attribute so that it can be used in the shader
}

void InitTexCoordBuffer() {// Textures
    GLfloat texCoords[4][2] = {
            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,
    };

    glBindBuffer(GL_ARRAY_BUFFER, Globals::BufferIDs[1]);  // Bind buffer to GL_ARRAY_BUFFER - All operations from now on will be on this buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);  // Initialize the data store

    GLuint vTexCoordLoc = glGetAttribLocation(Globals::ShaderProgram, "vTexCoord");  // Get the location of the attribute
    glBindAttribLocation(Globals::ShaderProgram, vTexCoordLoc, "vTexCoord");  // Bind the attribute to the location
    glVertexAttribPointer(vTexCoordLoc, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));  // Set the attribute from the currently bound buffer
    glEnableVertexAttribArray(vTexCoordLoc);  // Enable the attribute so that it can be used in the shader
}

void loadTextures() {// Load textures
    auto size = Globals::Textures.size();
    auto textureIDs = new GLuint[size]; // Create an array of texture IDs
    glGenTextures(GLsizei(Globals::Textures.size()), textureIDs); // Generate texture IDs

    for (int i = 0; i < Globals::Textures.size(); i++) {
        Globals::Textures[i].textureID = textureIDs[i];

        GLint width, height;
        unsigned char* textureData = SOIL_load_image(Globals::Textures[i].texturePath, &width, &height, nullptr, SOIL_LOAD_RGB); // Load the texture data
        if (textureData == nullptr) {
            cout << "Error loading texture: " << Globals::Textures[i].texturePath << endl;
            cout << "Reason: " << SOIL_last_result() << endl;
            exit(1);
        }

        glBindTexture(GL_TEXTURE_2D, textureIDs[i]); // Bind the first texture
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData); // Load the texture data into the currently bound texture
        glGenerateMipmap(GL_TEXTURE_2D);    // Generate mipmaps for the currently bound texture so it looks better when it's far away

        // Set texture parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Horizontal wrapping
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);   // Vertical wrapping
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // Use mipmaps when downscaled with linear sampling
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Use linear interpolation (average of neighbor pixels) when the texture is upscaled.
    }

    delete[] textureIDs;
}

void createWindow(int &argc, char **argv, int width, int height, const char *title) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);

    glutInitWindowSize(width, height);
    glutCreateWindow(title);
}

void Display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Globals::Matrix::Model = glm::mat4(1.0f);   // Reset the model matrix on every frame
    glUniformMatrix4fv(Globals::Matrix::UniformLocation::Model, 1, GL_FALSE, &Globals::Matrix::Model[0][0]); // Send the model matrix to the shader

    //The 3D point in space that the camera is looking
    glm::vec3 look_at = Globals::Camera::Position + Globals::Camera::Target;

    Globals::Matrix::View = glm::lookAt(Globals::Camera::Position, look_at, Globals::Camera::UpVector); // Reset the view matrix on every frame
    glUniformMatrix4fv(Globals::Matrix::UniformLocation::View, 1, GL_FALSE, &Globals::Matrix::View[0][0]); // Send the view matrix to the shader

    // Set the projection matrix
    Globals::Matrix::Projection = glm::perspective(90.0f, (float)glutGet(GLUT_WINDOW_WIDTH) / (float)glutGet(GLUT_WINDOW_HEIGHT), 0.1f, 100000.0f);
    glUniformMatrix4fv(Globals::Matrix::UniformLocation::Projection, 1, GL_FALSE, &Globals::Matrix::Projection[0][0]); // Send the projection matrix to the shader

    for (auto & i : Globals::SceneGraph) {
        i->draw(Globals::Matrix::Model, Globals::Matrix::UniformLocation::Model);
    }

    glFlush();
}

void tick()
{
    auto newTimeSinceStart = glutGet(GLUT_ELAPSED_TIME);
    Globals::Time::DeltaTime = newTimeSinceStart - Globals::Time::TimeSinceStart;   // Calculate the time since the last frame
    Globals::Time::TimeSinceStart = newTimeSinceStart;  // Update the time since the start of the program

    glutPostRedisplay();    // Redraw the screen

    //tick all objects
    for (auto i : Globals::SceneGraph) {
        i->tick(float(Globals::Time::DeltaTime));
    }
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
        case 'W':
            Globals::Camera::Position += Globals::Camera::ForwardVector * Globals::Camera::Speed * ((float) Globals::Time::DeltaTime / 1000.0f);
            break;
        case 's':
        case 'S':
            Globals::Camera::Position -= Globals::Camera::ForwardVector * Globals::Camera::Speed * ((float) Globals::Time::DeltaTime / 1000.0f);
            break;
        case 'a':
        case 'A':
            Globals::Camera::Position += Globals::Camera::RightVector * Globals::Camera::Speed * ((float) Globals::Time::DeltaTime / 1000.0f);
            break;
        case 'd':
        case 'D':
            Globals::Camera::Position -= Globals::Camera::RightVector * Globals::Camera::Speed * ((float) Globals::Time::DeltaTime / 1000.0f);
            break;
        case 'q':
        case 'Q':
            Globals::Camera::Position.z += Globals::Camera::Speed * ((float) Globals::Time::DeltaTime / 1000.0f);
            break;
        case 'e':
        case 'E':
            Globals::Camera::Position.z -= Globals::Camera::Speed * ((float) Globals::Time::DeltaTime / 1000.0f);
            break;
        case 'r':
        case 'R':

            Globals::Camera::Position = glm::vec3(-30.0f, 0.0f, 20.0f);
            Globals::Camera::ForwardVector = glm::vec3(1, 1, 0);
            Globals::Camera::UpVector = glm::vec3(0, 0, 1);
            Globals::Camera::RightVector = glm::cross(Globals::Camera::UpVector, Globals::Camera::ForwardVector);
            Globals::Camera::Target = glm::vec3(1, 1, 0);
            Globals::Camera::Speed = 1000.0f;
            break;
        case 27:
            exit(0);
            break;
    }
}

void mouseButtons(int button, int state, int x, int y) {
    switch (button) {
        case 3: // Scroll up
            Globals::Camera::Speed += 50.f;
            break;
        case 4: // Scroll down
            Globals::Camera::Speed = std::max(10.f, Globals::Camera::Speed - 50.f);
            break;
        default:
            break;
    }
}

void mouseMove(int x, int y) {
    glm::vec2 deltaMousePos = glm::vec2(x, y) - Globals::Mouse::Position; // Calculate the difference between the current and last mouse position
    // Handle X axis
    // Update camera vectors
    Globals::Camera::ForwardVector = glm::rotate(Globals::Camera::ForwardVector, -deltaMousePos.x * Globals::Mouse::Sensitivity, glm::vec3(0, 0, 1));
    Globals::Camera::Target = glm::rotate(Globals::Camera::Target, -deltaMousePos.x * Globals::Mouse::Sensitivity, glm::vec3(0, 0, 1));
    Globals::Camera::RightVector = glm::rotate(Globals::Camera::RightVector, -deltaMousePos.x * Globals::Mouse::Sensitivity, glm::vec3(0, 0, 1));
    Globals::Camera::UpVector = glm::rotate(Globals::Camera::UpVector, -deltaMousePos.x * Globals::Mouse::Sensitivity, glm::vec3(0, 0, 1));

    Globals::Mouse::Position.x = x;
    Globals::Mouse::Position.y = y;

    // Handle Y axis
    glm::vec3 cam_up_vector_temp = glm::rotate(Globals::Camera::UpVector, deltaMousePos.y * Globals::Mouse::Sensitivity, Globals::Camera::RightVector);
    glm::vec3 cam_target_temp = glm::rotate(Globals::Camera::Target, deltaMousePos.y * Globals::Mouse::Sensitivity, Globals::Camera::RightVector);

    GLfloat dot_product = glm::dot(cam_target_temp, Globals::Camera::ForwardVector);
    if (dot_product > 0.0f) {
        Globals::Camera::UpVector = glm::rotate(Globals::Camera::UpVector, deltaMousePos.y * Globals::Mouse::Sensitivity, Globals::Camera::RightVector);
        Globals::Camera::Target = glm::rotate(Globals::Camera::Target, deltaMousePos.y * Globals::Mouse::Sensitivity, Globals::Camera::RightVector);
    }
}

int main(int argc, char** argv) {
    createWindow(argc, argv, 1024, 1024, Globals::WINDOW_TITLE);

    glewInit();

    glEnable(GL_DEPTH_TEST);

    // Normalize Camera Vectors
    Globals::Camera::ForwardVector = glm::normalize(Globals::Camera::ForwardVector);
    Globals::Camera::RightVector = glm::normalize(Globals::Camera::RightVector);
    Globals::Camera::UpVector = glm::normalize(Globals::Camera::UpVector);

    ShaderInfo shaders[] = {
            {GL_VERTEX_SHADER, "triangles.vert"},
            {GL_FRAGMENT_SHADER, "triangles.frag"},
            {GL_NONE, NULL}
    };

    Globals::ShaderProgram = LoadShaders(shaders);
    glUseProgram(Globals::ShaderProgram);

    // Generate buffers
    glGenBuffers(Globals::MAX_BUFFERS, Globals::BufferIDs);

    InitVerticesBuffer();
    InitTexCoordBuffer();

    // Get the location of the uniform variables
    Globals::Matrix::UniformLocation::Model = glGetUniformLocation(Globals::ShaderProgram, "model_matrix");
    Globals::Matrix::UniformLocation::View = glGetUniformLocation(Globals::ShaderProgram, "camera_matrix");
    Globals::Matrix::UniformLocation::Projection = glGetUniformLocation(Globals::ShaderProgram, "projection_matrix");

    // Load textures
    loadTextures();

    // Ground GameObject with a huge scale
    auto ground = new OGround(Transform(glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(1000, 1000, 0)));
    ground->GroundTexture->textureData = &Globals::Textures[0];
    Globals::SceneGraph.push_back(ground);

    // Car GameObject
    auto car = new OCar(Transform(glm::vec3(0.0f, 0.0f, 0.0f)));
    car->bodyTexture->textureData = &Globals::Textures[0];
    car->wheelTexture->textureData = &Globals::Textures[1];
    Globals::SceneGraph.push_back(car);

    glutDisplayFunc(Display);

    glutKeyboardFunc(keyboard);

    glutIdleFunc(tick);

    glutMouseFunc(mouseButtons);
    glutPassiveMotionFunc(mouseMove);

    glutMainLoop();

    // Cleanup
    glDeleteBuffers(Globals::MAX_BUFFERS, Globals::BufferIDs);
    glDeleteProgram(Globals::ShaderProgram);
}






