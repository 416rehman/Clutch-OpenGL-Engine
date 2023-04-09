cmake_minimum_required(VERSION 3.24)
project(Lab)

set(CMAKE_CXX_STANDARD 14)


# Copy all the .frag, .vert, .png, .jpg, .jpeg files from FirstExample to the build directory
file(GLOB_RECURSE SHADER_FILES FirstExample/*.frag FirstExample/*.vert FirstExample/*.png FirstExample/*.jpg FirstExample/*.jpeg)
foreach(SHADER_FILE ${SHADER_FILES})
    file(COPY ${SHADER_FILE} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endforeach()

# Header files used by the project
include_directories(include)
include_directories(glm)

# Libraries (.lib) directories
link_directories(lib)
link_directories(SOIL/lib)

# Create executable
add_executable(Lab
        FirstExample/Globals.h
        FirstExample/Globals.cpp
        FirstExample/main.cpp
        FirstExample/LoadShaders.cpp
        FirstExample/Engine/Object.cpp
        FirstExample/Engine/Object.h
        FirstExample/Engine/Transform.cpp
        FirstExample/Engine/Transform.h
        FirstExample/Engine/Types.h
        FirstExample/Engine/Component/ObjectComponent.cpp
        FirstExample/Engine/Component/ObjectComponent.h
        FirstExample/Engine/Component/SceneComponent.cpp
        FirstExample/Engine/Component/SceneComponent.h
        FirstExample/Engine/Component/PrimitiveComponent.cpp
        FirstExample/Engine/Component/PrimitiveComponent.h
        FirstExample/Source/Car/OCar.cpp
        FirstExample/Source/Car/OCar.h
        FirstExample/Source/Car/components/WheelComponent.cpp
        FirstExample/Source/Car/components/WheelComponent.h
        FirstExample/Source/Ground/OGround.cpp
        FirstExample/Source/Ground/OGround.h
        )


target_link_libraries(Lab freeglut_static glew32s vermilion32)

# Link the libraries from the libraries directories
# Download the SOIL "include" and "lib" folders from https://github.com/Friduric/simple-opengl-image-library/tree/master
# Move the folders to the "SOIL" folder in the projects root directory, then rename "libs" folder to "lib" and "include" folder to "src"
target_link_libraries(Lab SOIL)

# Set linker flags for the executable, removing the default libraries and adding the legacy_stdio_definitions.lib
set_target_properties(Lab PROPERTIES LINK_FLAGS "/NODEFAULTLIB:LIBCMTD /NODEFAULTLIB:LIBCMT /DEFAULTLIB:legacy_stdio_definitions.lib")
