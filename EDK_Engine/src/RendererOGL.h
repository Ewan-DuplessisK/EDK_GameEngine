#ifndef ORPG_GAMEENGINE_RENDEREROGL_H
#define ORPG_GAMEENGINE_RENDEREROGL_H

#include "GL/glew.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include <SDL.h>
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <SDL_opengles2.h>
#else
#include <SDL_opengl.h>
#endif

#ifdef __EMSCRIPTEN__
#include "../libs/emscripten/emscripten_mainloop_stub.h"
#endif
#include "Matrices.h"
#include "VertexArray.h"
#include "Shader.h"
#include <vector>

class RendererOGL {

public:
    RendererOGL();
    virtual ~RendererOGL();
    RendererOGL(const RendererOGL&) = delete;
    RendererOGL& operator=(const RendererOGL&) = delete;

    bool initialize();
    bool stop();

    void clearScreen();
    void draw();
    void endDraw();

    SDL_Window* GetWindow(){return SDLWindow;}
    ImGuiContext* GetImGuiContext(){return ImGuiContext;}
    ImGuiIO* GetImGuiIO(){return &io;}
    SDL_GLContext* GetGLContext(){return &gl_context;}

    void addMesh(class Mesh* newMesh){meshes.emplace_back(newMesh);}

private:
    SDL_Window* SDLWindow;
    ImGuiContext * ImGuiContext;
    ImGuiIO io;
    SDL_GLContext gl_context;

    std::vector<class Mesh*> meshes;
    std::vector<class Sprite*> sprites;



    void draw3D();

    void draw2D();

    //Single shader mode
    //TODO move all this to an asset manager class with a proper shader list/map/set
    Shader shader2D;
    GLuint shader2DProgram;
    GLuint shader2DVertex;
    GLuint shader2DFragment;

    GLuint shader3DMeshProgram;
    GLuint shader3DMeshVertex;
    GLuint shader3DMeshFragment;

    Shader shader3D;
    GLuint shader3DLightProgram;
    GLuint shader3DLightVertex;
    GLuint shader3DLightFragment;

    void loadShader(GLuint &shader,GLenum shaderType,std::string path);

    //TODO Redo, copy pasted from Gaetan
    VertexArray* spriteVertexArray;
    Matrix4 spriteViewProj;
    Matrix4 view;
    Matrix4 projection;
    void setLightUniforms();
    Vector3 ambientLight;
    struct DirectionalLight
    {
        Vector3 direction;
        Vector3 diffuseColor;
        Vector3 specColor;
    };
    DirectionalLight dirLight;

    void updateDrawOrder();
};


#endif //ORPG_GAMEENGINE_RENDEREROGL_H
