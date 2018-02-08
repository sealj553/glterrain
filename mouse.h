#ifndef MOUSE_H
#define MOUSE_H

#include <GLFW/glfw3.h>

class Mouse {
    public:
        Mouse();
        void updateMouse();

        double x = 0, y = 0;
        float yaw = 0, pitch = 0;

    private:
        static void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);

        const float mouseSensitivity = 0.2f;
};

#endif
