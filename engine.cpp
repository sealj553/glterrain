#include "engine.h"

#include <iostream>

#include "globals.h"
#include "gui.h"

using std::cout;
using std::cerr;
using std::endl;
using std::unique_ptr;
using namespace Screen;

Engine::Engine(){
    //glewExperimental = GL_TRUE;
    if (!glfwInit()){
        cerr << "Could not init glfw" << endl;
        exit(1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(width, height, " ", NULL, NULL);
    if (!window) {
        cerr << "Couldn't create window" << endl; 
        glfwTerminate();
        exit(1);
    }

    glfwMakeContextCurrent(window);
    //glfwSetWindowSizeCallback(window, window_resize_callback);
    glfwSwapInterval(0); //vsync

    glClearDepth(1.0f);		   // Set background depth to farthest
    glClearColor(0.694f, 0.796f, 0.929f, 0.0f);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections

    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
    glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (glewInit()){
        cerr << "glew failed to init\n";
        exit(1);
    }

    Globals::init();
    Gui::init();
    terrain = unique_ptr<Terrain>(new Terrain());
    camera = unique_ptr<Camera>(new Camera());
}

void Engine::start(){
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //do things

        Time::updateTime();
        Input::mouse->updateMouse();
        camera->update();
        terrain->render();
        Gui::render();

        //now display
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    Gui::exit();
    glfwDestroyWindow(window);
    glfwTerminate();
}
