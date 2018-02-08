#ifndef ENGINE_H
#define ENGINE_H

#include <memory>

#include "terrain.h"
#include "camera.h"

using std::unique_ptr;

class Engine {
    public:
        Engine();
        void start();

    private:
        unique_ptr<Terrain> terrain;
        unique_ptr<Camera> camera;
};

#endif
