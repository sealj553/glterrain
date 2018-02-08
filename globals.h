#ifndef GLOBALS_H
#define GLOBALS_H

#include <memory>
#include <glm/glm.hpp>

#include "FastNoise/FastNoise.h"
#include "keyboard.h"
#include "mouse.h"
#include "shader.h"

using std::unique_ptr;
using glm::mat3;

extern GLFWwindow *window;

namespace Screen {
    extern const int width;
    extern const int height;

    extern int displayW;
    extern int displayH;
    extern float aspectRatio;
}

namespace Noise {
    extern FastNoise noise;
}

namespace Input {
    extern unique_ptr<Keyboard> keyboard;
    extern unique_ptr<Mouse> mouse;
}

namespace Shaders {
    extern unique_ptr<Shader> terrain;
    extern mat3 vars;
    extern GLuint texture[5];
    extern GLuint textureLoc[5];
}

namespace Globals {
    void init();
}

namespace Time {
    extern double oldTime;
    extern double deltaTime;

    void updateTime();
}

#endif
