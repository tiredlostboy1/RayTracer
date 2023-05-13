#ifndef CAPP_H
#define CAPP_H

#include <SDL2/SDL.h>

#include "../Image/Image.hpp"
#include "../Scene/Scene.hpp"

class CApp
{
public:
    CApp();

    bool OnInit();
    void OnExecute();
    void OnEvent(SDL_Event *event);
    void OnLoop();
    void OnRender();
    void OnExit();

private:

    //image class instance
    Image m_image;

    //scene class instance
    Scene m_scene;

    bool isRunning;

    // SDL2
    SDL_Window *pWindow;
    SDL_Renderer *pRenderer;
};

#endif
