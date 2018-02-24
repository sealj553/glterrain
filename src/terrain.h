#ifndef TERRAIN_H
#define TERRAIN_H

#include <memory>
#include <mutex>

#include "chunk.h"

using std::mutex;
using std::unique_ptr;

class Terrain {
    public:
        Terrain();
        void render();
    private:
        void chunker();

        const static int size = 4;
        unique_ptr<Chunk> chunks[size * size];
        unique_ptr<Chunk> nextChunk;

        mutex mtx;
};

#endif
