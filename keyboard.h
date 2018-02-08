#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <GLFW/glfw3.h>

namespace Keys { enum { W, S, A, D, J, K, SHIFT, END }; };
namespace States { enum { WIREFRAME, CURSOR, END }; };

class Keyboard {
    public:
        Keyboard();

        static bool keys[Keys::END];
    private: 
        static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

        static bool states[States::END];
};

#endif
