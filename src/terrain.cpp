#include "terrain.h"

#include <iostream>
#include <thread>
#include <chrono>

#include <SOIL/SOIL.h>

#include "globals.h"

using std::cerr;
using std::endl;
using std::thread;

Terrain::Terrain(){
    thread t([=]{ chunker(); });
    t.detach();

    //load textures
    int texWidth, texHeight;
    unsigned char* image;
    const int numTextures = 5;
    const char* filenames[] {"textures/grass2.png", "textures/mossrock.png", "textures/stone2.png", "textures/snow.png", "textures/noise3.png" };
    const char* uniformNames[] {"grass", "grassstone", "stone", "snow", "noise"};
    Shaders::terrain->use();
    for(int i = 0; i < numTextures; ++i){
        image = SOIL_load_image(filenames[i], &texWidth, &texHeight, 0, SOIL_LOAD_RGBA);
        if(!image){
            cerr << "Unable to open " << filenames[i] << endl;
            return;
        }

        glGenTextures(1, &Shaders::texture[i]);
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, Shaders::texture[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        SOIL_free_image_data(image);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glGenerateMipmap(GL_TEXTURE_2D);

        Shaders::textureLoc[i] = glGetUniformLocation(Shaders::terrain->getLocation(), uniformNames[i]);
        glUniform1i(Shaders::textureLoc[i], i);
    }
}

/*
 * Data structure to hold chunks that:
 *  -doesn't allow duplicates
 *  -fast insertion/deletion
 *  linked list = good because iterator is constant, fast removal
 *  map?, key could be pair<x, y>
 */

void Terrain::chunker(){
    const int half = size / 2;
    for(int x = -half; x < half; ++x){
        for(int z = -half; z < half;){
            while(!mtx.try_lock()){
                std::this_thread::sleep_for(std::chrono::milliseconds(3));
            }
            //now locked
            if(!nextChunk){
                nextChunk = unique_ptr<Chunk>(new Chunk(x, z++));
            }
            mtx.unlock();
        }
    }
}

void Terrain::render(){
    mtx.lock();
    if(nextChunk){
        nextChunk->upload();
        chunks[Chunk::numChunks++] = move(nextChunk);
    }
    mtx.unlock();

    Shaders::terrain->use();
    for(int i = 0; i < Chunk::numChunks; ++i){
        chunks[i]->render();
    }
}
