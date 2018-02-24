#include "globals.h"

GLFWwindow *window;

namespace Screen {
    //const int width = 1280;
    //const int height = 720;
    const int width = 1600;
    const int height = 900 - 32;

    int displayW;
    int displayH;
    float aspectRatio;
}

namespace Noise {
    FastNoise noise;
}

namespace Input {
    unique_ptr<Keyboard> keyboard;
    unique_ptr<Mouse> mouse;
}

namespace Shaders {
    unique_ptr<Shader> terrain;
    mat3 vars;
    GLuint texture[];
    GLuint textureLoc[];
}

namespace Globals {
    void init(){
        Input::keyboard = unique_ptr<Keyboard>(new Keyboard());
        Input::mouse = unique_ptr<Mouse>(new Mouse());
        Shaders::terrain = unique_ptr<Shader>(new Shader("shaders/shader.vert", "shaders/shader.frag"));
        //Shaders::terrainNorm = unique_ptr<Shader>(new Shader("shaders/normshader.vert", "shaders/normshader.frag", "shaders/normshader.geo"));

        glfwGetFramebufferSize(window, &Screen::displayW, &Screen::displayH);
        Screen::aspectRatio = static_cast<float>(Screen::displayW) / Screen::displayH;
        //Screen::aspectRatio = static_cast<float>(Screen::width) / Screen::height;

        //Noise::noise.SetSeed(1337);//1337

        //Noise::noise.SetFractalLacunarity(2.0f);//2.0
        //Noise::noise.SetFractalGain(0.2f);//0.5
        //Noise::noise.SetFractalGain(0.4f);//0.5

        //noise.SetNoiseType(FastNoise::SimplexFractal); 
        //noise.SetNoiseType(FastNoise::PerlinFractal); 
        //noise.SetNoiseType(FastNoise::CubicFractal); 

        //noise.SetFractalType(FastNoise::FractalType::FBM);
        //noise.SetFractalType(FastNoise::FractalType::RigidMulti);
        //noise.SetFractalType(FastNoise::FractalType::Billow);

        Shaders::vars[1].x = 0.2f;
        Shaders::vars[1].y = 0.5f;

    }
}

namespace Time {
    double oldTime;
    double deltaTime;

    void updateTime(){
        double time = glfwGetTime();
        deltaTime = time - oldTime;
        oldTime = time;
    }
}
