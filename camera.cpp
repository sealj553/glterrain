#include "camera.h"

#include <glm/gtc/type_ptr.hpp>

#include "mouse.h"

using glm::radians;
using namespace Input;
using namespace Keys;
using namespace Screen;

vec3 Camera::cameraPos = { 0.0f, 0.0f, 0.0f };
vec3 Camera::cameraFront = { 0.0f, 0.0f, -1.0f };

Camera::Camera():
    viewProjectionLoc(glGetUniformLocation(Shaders::terrain->getLocation(), "viewProjection")),
    //cameraPosLoc(glGetUniformLocation(Shaders::terrain->getLocation(), "camPos")),
    varsLoc(glGetUniformLocation(Shaders::terrain->getLocation(), "vars"))
{
    glViewport(0, 0, width, height);
}

void Camera::update(){
    if(glfwGetInputMode(window, GLFW_CURSOR) != GLFW_CURSOR_DISABLED){
        glUniformMatrix3fv(varsLoc, 1, GL_FALSE, value_ptr(Shaders::vars));
        return;
    }

    if(!keyboard->keys[SHIFT]){
        cameraSpeed = moveSpeed * static_cast<float>(Time::deltaTime);
    } else {
        cameraSpeed = moveSpeed * shiftSpeed * static_cast<float>(Time::deltaTime);
    }

    float pitch = radians(mouse->pitch);
    float yaw = radians(mouse->yaw);
    cameraFront.x = cosf(pitch) * cosf(yaw);
    cameraFront.y = sinf(pitch);
    cameraFront.z = cosf(pitch) * sinf(yaw);
    cameraFront = normalize(cameraFront);

    if (keyboard->keys[W]){
        cameraPos += cameraSpeed * cameraFront;
    } else if (keyboard->keys[S]){
        cameraPos -= cameraSpeed * cameraFront;
    }

    if (keyboard->keys[A]){
        cameraPos -= normalize(cross(cameraFront, cameraUp)) * cameraSpeed;
    } else if (keyboard->keys[D]){
        cameraPos += normalize(cross(cameraFront, cameraUp)) * cameraSpeed;
    }

    if (keyboard->keys[K]){
        cameraPos += cameraSpeed * cameraUp;
    } else if (keyboard->keys[J]){
        cameraPos -= cameraSpeed * cameraUp;
    }

    view = lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    viewProjection = projection * view;

    Shaders::terrain->use();
    glUniformMatrix4fv(viewProjectionLoc, 1, GL_FALSE, value_ptr(viewProjection));
    //glUniform3fv(cameraPosLoc, 1, value_ptr(cameraPos));
    glUniformMatrix3fv(varsLoc, 1, GL_FALSE, value_ptr(Shaders::vars));
}
