#ifndef CAPP_H
#define CAPP_H

#include <SDL2/SDL.h>

#include "Image.hpp"

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
    Image m_image;

    bool isRunning;

    // SDL2
    SDL_Window *pWindow;
    SDL_Renderer *pRenderer;
};

#endif
