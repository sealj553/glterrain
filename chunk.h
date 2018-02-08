#ifndef CHUNK_H
#define CHUNK_H

#include <array>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

using std::array;

using glm::mat4;
using glm::vec3;
using glm::vec2;

static constexpr float maxHeight = 100.0f;
//static constexpr int size = 128;//good
static constexpr int size = 256;
//static constexpr float scale = size / 512.f;
//static constexpr float scale = size / 256.f;
static constexpr float scale = 0.25f;//good

//static constexpr int numIndices = (size - 1) * (size - 1) * 6;
static constexpr int skip = 1;
static constexpr int numIndices = ((size / skip) - 1) * ((size / skip) - 1) * 6;

typedef array<GLushort, numIndices> array_;

class Chunk {
    public:
        Chunk(int chunkX_, int chunkZ_);
        ~Chunk();
        void upload();
        void render() const;

        int chunkX, chunkZ;
        static int numChunks;
    private:
        inline static float getHeight(float x, float z);

        GLuint vao, vbo, ebo, normalBuffer;

        vec3 *data;
        GLushort *indices;
        vec3 *normals;
};

#endif
