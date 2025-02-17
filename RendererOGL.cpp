#include "RendererOGL.h"
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <algorithm>
#include "Mesh.h"
#include "Sprite.h"
#include "Assets.h"
#define WIDTH 1280
#define HEIGHT 720


bool RendererOGL::initialize() {


    //Setup context and window
    // Setup SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0){
        printf("Error: %s\n", SDL_GetError());
        return -1;
    }

    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100 (WebGL 1.0)
    const char* glsl_version = "#version 100";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#elif defined(IMGUI_IMPL_OPENGL_ES3)
    // GL ES 3.0 + GLSL 300 es (WebGL 2.0)
    const char* glsl_version = "#version 300 es";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#elif defined(__APPLE__)
    // GL 3.2 Core + GLSL 150
    const char* glsl_version = "#version 150";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#endif

    // From 2.0.18: Enable native IME.
#ifdef SDL_HINT_IME_SHOW_UI
    SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
#endif

    // Create window with graphics context
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Window* window = SDL_CreateWindow("Dear ImGui SDL2+OpenGL3 example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
    if (window == nullptr){
        printf("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
        return -1;
    }

    gl_context = SDL_GL_CreateContext(window);
    if (gl_context == nullptr){
        printf("Error: SDL_GL_CreateContext(): %s\n", SDL_GetError());
        return -1;
    }
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(SDLWindow, gl_context);
    ImGui_ImplOpenGL3_Init(glsl_version);

    return true;
}

bool RendererOGL::stop() {
#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_MAINLOOP_END;
#endif

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(SDLWindow);
    SDL_Quit();
    return true;
}

RendererOGL::RendererOGL():SDLWindow(nullptr),gl_context(nullptr),spriteVertexArray(nullptr),ambientLight(Vector3(1.0f, 1.0f, 1.0f)),dirLight({ Vector3(), Vector3(), Vector3() }) {
    Matrix4 mViewProj, mView, mProj;
    mViewProj = mView = mProj = Matrix4();

    mViewProj.setRow(0,{2.f/WIDTH,0,0,0});
    mViewProj.setRow(1,{0,2.f/HEIGHT,0,0});
    spriteViewProj=mViewProj;

    view = mView.lookAt({1,0,0},{0,0,1});

    projection = mProj.createPerspectiveFOV(DEG2RAD*70.f,WIDTH,HEIGHT,10.f,10000.f);

    //Broken: Data Execution Prevention
    //shader2D = Assets::loadShaderFromFile("Res/Shaders/Sprite.vert","Res/Shaders/Sprite.frag");

    //Broken: Data Execution Prevention
    GLuint testProg = glCreateProgram();
    shader2DProgram = glCreateProgram();
    loadShader(shader2DFragment,GL_FRAGMENT_SHADER,"Res/Shaders/Sprite.vert");
    loadShader(shader2DVertex,GL_VERTEX_SHADER,"Res/Shaders/Sprite.vert");
    glAttachShader(shader2DProgram,shader2DVertex);
    glAttachShader(shader2DProgram,shader2DFragment);
    glLinkProgram(shader2DProgram);
    glDeleteShader(shader2DVertex);
    glDeleteShader(shader2DFragment);

    //Broken: Data Execution Prevention
    shader3D = Assets::loadShaderFromFile("Res/Shaders/Phong.vert","Res/Shaders/Phong.frag");

    //Broken: Data Execution Prevention
    /*shader3DLightProgram = glCreateProgram();
    loadShader(shader3DLightFragment,GL_FRAGMENT_SHADER,"Res/Shaders/Phong.frag");
    loadShader(shader3DLightVertex,GL_VERTEX_SHADER,"Res/Shaders/Phong.vert");
    glAttachShader(shader3DLightProgram,shader3DLightVertex);
    glAttachShader(shader3DLightProgram,shader3DLightFragment);
    glLinkProgram(shader3DLightProgram);
    glDeleteShader(shader3DLightVertex);
    glDeleteShader(shader3DLightFragment);*/


}

RendererOGL::~RendererOGL() {}

void RendererOGL::clearScreen() {
    glClearColor(1.f,0.f,.9f,1.f);
    //glClearColor(1.f,0.f,.9f,1.f); //Missing texture purple
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

void RendererOGL::draw() {
    draw3D();
    //draw2D
    //drawUI
}

void RendererOGL::endDraw() {SDL_GL_SwapWindow(SDLWindow);}

void RendererOGL::draw3D(){
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);

    /*glUseProgram(shader3DLightProgram);
    Matrix4 viewProj = view*projection;
    glUniformMatrix4fv(glGetUniformLocation(shader3DLightProgram, "uViewProj"), 1, GL_TRUE, (&viewProj.matrix[0][0]));
    glBindVertexArray(spriteVertexArray->vertexArray); //TODO do away with vertex array class*/

    shader3D.use();
    shader3D.setMatrix4("uViewProj",view*projection);

    setLightUniforms();

    for(Mesh* mesh : meshes){
        Matrix4 wt = mesh->getWorldTransform();
        /*glUniformMatrix4fv(glGetUniformLocation(shader3DLightProgram, "uWorldTransform"), 1, GL_TRUE, (&wt.matrix[0][0]));
        glUniform1f(glGetUniformLocation(shader3DLightProgram,"uSpecPower"),mesh->getSpecularPower());*/

        shader3D.setMatrix4("uWorldTransform",wt);
        shader3D.setFloat("uSpecPower",mesh->getSpecularPower());

        if(Texture* text = mesh->getTexture(0))text->setActive();

        VertexArray* vertArray = mesh->getVertexArray();
        vertArray->setActive();

        glDrawElements(GL_TRIANGLES,vertArray->getNbIndices(),GL_UNSIGNED_INT, nullptr);
    }
}

//TODO move function to an asset manager class
void RendererOGL::loadShader(GLuint &shader,GLenum shaderType, std::string path) {
    shader = glCreateShader(shaderType);

    std::ifstream shaderFile(path);
    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    shaderFile.close();
    std::string shaderCode = shaderStream.str();
    const GLchar* glShaderCode = shaderCode.c_str();

    glShaderSource(shader, 1, &glShaderCode, NULL);
    glCompileShader(shader);
}

void RendererOGL::draw2D(){
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

    glUseProgram(shader2DProgram);
    glUniformMatrix4fv(glGetUniformLocation(shader2DProgram, "uViewProj"), 1, GL_TRUE, (&spriteViewProj.matrix[0][0]));
    glBindVertexArray(spriteVertexArray->vertexArray); //TODO do away with vertex array class

    for(Sprite* sprite : sprites){
        Matrix4 wt = sprite->getTransform();
        glUniformMatrix4fv(glGetUniformLocation(shader2DProgram, "uWorldTransform"), 1, GL_TRUE, (&wt.matrix[0][0]));

        if(Texture* text = sprite->getTexture())text->setActive();

        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT, nullptr);
    }
}

void RendererOGL::updateDrawOrder(){
    std::sort(sprites.begin(),sprites.end());
}

void RendererOGL::setLightUniforms(){
    // Camera position is from inverted view
    Matrix4 invertedView = view;
    invertedView.invert();

    glUniform3f(glGetUniformLocation(shader3DLightProgram,"uCameraPos"),invertedView.getTranslation().x,invertedView.getTranslation().y,invertedView.getTranslation().z);
    glUniform3f(glGetUniformLocation(shader3DLightProgram,"uAmbientLight"),ambientLight.x,ambientLight.y,ambientLight.z);
    glUniform3f(glGetUniformLocation(shader3DLightProgram,"uDirLight.direction"),dirLight.direction.x,dirLight.direction.y,dirLight.direction.z);
    glUniform3f(glGetUniformLocation(shader3DLightProgram,"uDirLight.diffuseColor"),dirLight.diffuseColor.x,dirLight.diffuseColor.y,dirLight.diffuseColor.z);
    glUniform3f(glGetUniformLocation(shader3DLightProgram,"uDirLight.specColor"),dirLight.specColor.x,dirLight.specColor.y,dirLight.specColor.z);

}