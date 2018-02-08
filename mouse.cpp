#include "mouse.h"
#include "globals.h"

using namespace Screen;

Mouse::Mouse(){
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
}

void Mouse::updateMouse(){
    double oldX = x;
    double oldY = y;
    glfwGetCursorPos(window, &x, &y);

    float deltaX = static_cast<float>(x - oldX);
    float deltaY = -static_cast<float>(y - oldY);

    yaw += deltaX * mouseSensitivity;
    pitch += deltaY * mouseSensitivity;

    if (pitch > 89.5f){
        pitch = 89.5f;
    } else if (pitch < -89.5f){
        pitch = -89.5f;
    }

    if(yaw > 360.0f){
        yaw -= 360.0f * 2;
    } else if(yaw < -360.0f){
        yaw += 360.0f * 2;
    }
}

void Mouse::mouseButtonCallback(GLFWwindow *window, int button, int action, int mods){
    if(button == GLFW_MOUSE_BUTTON_MIDDLE){
        if(action == GLFW_PRESS){
            glViewport(-width / 2, -height / 2, width * 2, height * 2);
        } else {
            glViewport(0, 0, width, height);
        }
    }
}
