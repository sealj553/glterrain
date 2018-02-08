#include "chunk.h"

#include <glm/gtc/matrix_transform.hpp>

#include "globals.h"
#include "camera.h"

#include <iostream>

using std::cout;
using std::endl;
using std::ostream;

using namespace Noise;

int Chunk::numChunks = 0;

ostream& operator<<(ostream &os, const vec3 &vec){
    os << vec.x << " " << vec.y << " " << vec.z;
    return os;
}

inline float noise1(float x, float z){
    ///////
    // probably not thread safe
    // fix if making multiple chunkers
    //////
    float y = 0;
    noise.SetFrequency(0.01f);//0.01
    noise.SetFractalOctaves(6);//3
    noise.SetFractalLacunarity(2.0f);//2.0
    noise.SetFractalGain(0.3f);//0.2
    y +=  1.5f * noise.GetSimplexFractal(1 * x, 1 * z);
    y +=  0.5f * noise.GetSimplexFractal(2 * x, 2 * z);
    noise.SetFractalLacunarity(3.0f);//2.0
    noise.SetFractalGain(0.3f);//0.4
    y += 0.25f * noise.GetSimplexFractal(4 * x, 4 * z);
    return y;
}

inline float noise2(float x, float z){
    noise.SetFrequency(0.005f);//0.01
    noise.SetFractalOctaves(3);//3
    noise.SetFractalLacunarity(1.0f);//2.0
    //noise.SetFractalLacunarity(2.0f);//2.0
    noise.SetFractalGain(10.f);//0.2
    return noise.GetSimplexFractal(x, z) + 1.f;
}

float Chunk::getHeight(float x, float z){
    float y = 1-pow(noise1(x, z), 2);
    y *= noise2(x, z);
    //float y = noise2(x, z);

    //y = abs(pow(y, 2));
    //y = pow(y, 2.0f); //great for islands
    //y = 1.f - abs(pow(y, 2));
    return y * maxHeight;
}

Chunk::Chunk(int chunkX_, int chunkZ_):
    chunkX(chunkX_), chunkZ(chunkZ_)
{
    data      = new vec3[sizeof(vec3) * size * size];
    indices   = new GLushort[sizeof(GLushort) * numIndices];
    normals   = new vec3[sizeof(vec3) * numIndices];

    {
        int index = 0;
        int offsetX = chunkX * (size - 1);
        int offsetZ = chunkZ * (size - 1);
        for(int j = 0; j < size; ++j){
            for(int i = 0; i < size; ++i){
                float x = i + offsetX;
                float z = j + offsetZ;

                data[index].x = x;
                data[index].y = getHeight(x * scale, z * scale);
                data[index].z = z;
                ++index;
            }
        }
    }

    {
        int index = -1;
        //int newSize = size / skip;
        for(int z = 0; z < size - 1; ++z){
            for(int x = 0; x < size - 1; ++x){
                //for(int z = 0; z < size - 1; z += skip){
                //    for(int x = 0; x < size - 1; x += skip){

                //int start = z * size + x;
                //int TL = start;
                //int TR = start + skip;
                //int BL = start + size;
                //int BR = start + skip + size;

                int start = z * size + x;
                int TL = start;
                int TR = start + 1;
                int BL = start + size;
                int BR = start + 1 + size;

                //indices[index++] = BL;
                //indices[index++] = BR;
                //indices[index++] = TR;
                //indices[index++] = BL;
                //indices[index++] = TR;
                //indices[index++] = TL;

                if(abs(data[TR].y - data[BL].y) < abs(data[TL].y - data[BR].y)){
                    indices[++index] = TR;
                    indices[++index] = BL;
                    indices[++index] = BR;

                    indices[++index] = TR;
                    indices[++index] = TL;
                    indices[++index] = BL;
                } else {
                    indices[++index] = TL;
                    indices[++index] = BL;
                    indices[++index] = BR;

                    indices[++index] = TR;
                    indices[++index] = TL;
                    indices[++index] = BR;
                }

                /*if(abs(data[TR].y - data[BL].y) < abs(data[TL].y - data[BR].y)){
                  indices[index += skip] = TR;
                  indices[index += skip] = BL;
                  indices[index += skip] = BR;

                  indices[index += skip] = TR;
                  indices[index += skip] = TL;
                  indices[index += skip] = BL;
                  } else {
                  indices[index += skip] = TL;
                  indices[index += skip] = BL;
                  indices[index += skip] = BR;

                  indices[index += skip] = TR;
                  indices[index += skip] = TL;
                  indices[index += skip] = BR;
                  }
                  */
            }
            }
            }

            {
                for(int i = 0; i < numIndices; i += 3){
                    vec3 &v0 = data[indices[i + 0]];
                    vec3 &v1 = data[indices[i + 1]];
                    vec3 &v2 = data[indices[i + 2]];

                    vec3 normal = normalize(cross(v1 - v0, v2 - v0));

                    normals[indices[i + 0]] += normal;
                    normals[indices[i + 1]] += normal;
                    normals[indices[i + 2]] += normal;
                }
                for(unsigned int i = 0; i < numIndices; ++i){
                    normals[i] = normalize(normals[i]);
                }
            }

        }

        void Chunk::upload(){
            //remove?
            glBindVertexArray(0);
            glGenVertexArrays(1, &vao);
            glBindVertexArray(vao);

            glGenBuffers(1, &vbo);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, size * size * sizeof(vec3), data, GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), 0);
            glEnableVertexAttribArray(0);

            glGenBuffers(1, &normalBuffer);
            glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
            glBufferData(GL_ARRAY_BUFFER, numIndices * sizeof(vec3), normals, GL_STATIC_DRAW);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), 0);
            glEnableVertexAttribArray(1);

            glGenBuffers(1, &ebo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(GLushort), indices, GL_STATIC_DRAW);

            delete[] data;
            delete[] normals;
            delete[] indices;
        }

        Chunk::~Chunk(){
            --numChunks;
            glDeleteBuffers(1, &vbo);
            glDeleteBuffers(1, &ebo);
            glDeleteVertexArrays(1, &vao);
        }

        void Chunk::render() const {
            glBindVertexArray(vao);
            glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0);
            glBindVertexArray(0);
        }
