#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "globals.h"

using glm::mat4;
using glm::vec3;
using glm::perspective;

class Camera {
    public:
        Camera();
        void update();

        static vec3 cameraPos;
        static vec3 cameraFront;
    private:
        const vec3 cameraUp = { 0.0f, 1.0f, 0.0f };

        const float fovy = 45.0f;
        //const float zNear = 0.1f;
        const float zNear = 0.05f;
        const float zFar = 10000.0f;

        float cameraSpeed;
        const float moveSpeed = 30.0f;
        const float shiftSpeed = 5.0f;

        const mat4 projection = perspective(fovy, Screen::aspectRatio, zNear, zFar);
        mat4 view;
        mat4 viewProjection;

        GLuint viewProjectionLoc;
        GLuint cameraPosLoc;
        GLuint varsLoc;
};

#endif
