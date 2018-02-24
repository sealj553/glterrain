#ifndef GUI_H
#define GUI_H

//#include <iostream>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"
#include "globals.h"
#include "chunk.h"

//using std::cout;
//using std::endl;
using namespace ImGui;
//using std::unique_lock;

namespace Gui {
    void init(){
        ImGui_ImplGlfwGL3_Init(false);
        StyleColorsClassic();
        GetStyle().WindowRounding = 0.0f;
    }

    void render(){
        ImGui_ImplGlfwGL3_NewFrame();
        SetNextWindowPos(ImVec2(3, 3), ImGuiCond_Once);
        //SetNextWindowSize(ImVec2(250, 85), ImGuiCond_Once);

        ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoTitleBar|ImGuiWindowFlags_NoSavedSettings;
        Begin("window", NULL, flags);

        const vec3 &cam = Camera::cameraPos;
        Text("X: %8.3f Y: %8.3f Z: %8.3f", cam.x, cam.y, cam.z);

        const vec3 &front= Camera::cameraFront;
        Text("X: %6.3f Y: %6.3f Z: %6.3f", front.x, front.y, front.z);

        Text("FPS: %.0lf (%.0lf ms)", 1.0 / Time::deltaTime, Time::deltaTime * 1000);
        Text("Chunks: %d", Chunk::numChunks);
        //float viewDistance = 5;
        //Text("Detail: %.0f", viewDistance);

        //SliderFloat("X", &Shaders::vars[0].x, -1.f, 1.f, "%f", 1.f);
        //SliderFloat("Y", &Shaders::vars[0].y, -1.f, 1.f, "%f", 1.f);
        //SliderFloat("Z", &Shaders::vars[0].z, -1.f, 1.f, "%f", 1.f);

        SliderFloat("a", &Shaders::vars[1].x, 0.1f, 0.9f, "%f");
        SliderFloat("b", &Shaders::vars[1].y, 0.1f, 0.9f, "%f");
        //SliderFloat("c", &Shaders::vars[1].z, 0.02f, 0.04f, "%f");

        End();
        Render();
    }

    void exit(){
        ImGui_ImplGlfwGL3_Shutdown();
    }
};

#endif
