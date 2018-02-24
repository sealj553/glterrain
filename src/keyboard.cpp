#include "keyboard.h"
#include "globals.h"

using namespace Keys;
using namespace States;

bool Keyboard::keys[] = { false };
bool Keyboard::states[] = { false };

Keyboard::Keyboard(){
    glfwSetKeyCallback(window, keyCallback);
}

void Keyboard::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods){
    bool pressed = action != GLFW_RELEASE;

    switch(key){
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, GL_TRUE);
            break;
        case GLFW_KEY_W:
            keys[W] = pressed;
            break;
        case GLFW_KEY_S:
            keys[S] = pressed;
            break;
        case GLFW_KEY_A:
            keys[A] = pressed;
            break;
        case GLFW_KEY_D:
            keys[D] = pressed;
            break;
        case GLFW_KEY_J:
            keys[J] = pressed;
            break;
        case GLFW_KEY_K:
            keys[K] = pressed;
            break;
        case GLFW_KEY_LEFT_SHIFT:
            keys[SHIFT] = pressed;
            break;
        case GLFW_KEY_Q:
            if(pressed){
                states[WIREFRAME] = !states[WIREFRAME];
                if (states[WIREFRAME]){
                    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                } else {
                    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                }
            }
            break;
        case GLFW_KEY_T:
            if(pressed){
                states[CURSOR] = !states[CURSOR];
                if (states[CURSOR]){
                    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                } else {
                    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                }
            }
            break;
    }
}
