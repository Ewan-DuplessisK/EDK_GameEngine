#include "RendererOGL.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_events.h"
#include "Assets.h"


int WinMain(int, char**){

    RendererOGL Renderer = RendererOGL();
    Renderer.initialize();
    SDL_Window* window = Renderer.GetWindow();
    ImGuiIO& io = *Renderer.GetImGuiIO();


    //ConsoleSystem console = ConsoleSystem();

    Mesh bCube = Assets::loadMeshFromFile("Res/Meshes/Cube.gpmesh");
    Renderer.addMesh(&bCube);


    bool done = false;
    bool open = true;
    while (!done){

        SDL_Event event;
        while (SDL_PollEvent(&event)){
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT) done = true;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window)) done = true;
        }
        if (SDL_GetWindowFlags(window) & SDL_WINDOW_MINIMIZED){
            SDL_Delay(10);
            continue;
        }

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        // Any application code here
        //console.Draw("test console3",&open);
        //processInput
        //update(deltaTime)
            //update sounds -> update actors -> remove dead actors -> update UI
        //render
        Renderer.clearScreen();
        Renderer.draw();


        // Render dear imgui into screen
        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        //glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        Renderer.endDraw();

    }

    Renderer.stop();

    return 0;
}