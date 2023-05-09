#include "CApp.h"

// default constructor
CApp::CApp(){
    isRunning = true;
    pWindow = nullptr;
    pRenderer = nullptr;
}

bool CApp::OnInit(){
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        return false;
    }

    pWindow = SDL_CreateWindow(
                                "Ray Tracer", 
                                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                1280, 720, 
                                SDL_WINDOW_SHOWN
                              );

    if(pWindow != nullptr){
        pRenderer = SDL_CreateRenderer(pWindow, -1, 0);
    }
    else {
        return false;
    }
    return true;
}

int CApp::OnExecute(){
    SDL_Event event;
    if(OnInit() == false){
        return -1;
    }

    while(isRunning){
        while(SDL_PollEvent(&event) != 0){
            OnEvent(&event);
        }

       OnLoop();
       OnRender(); 
    }
}

void CApp::OnEvent(SDL_Event * event){
    if(event->type == SDL_QUIT){
        isRunning = false;
    }
}

void CApp::OnLoop(){

}

void CApp::OnRender(){
    // setting background to white
    SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
    SDL_RenderClear(pRenderer);

    //result
    SDL_RenderPresent(pRenderer);
}

void CApp::OnExit(){
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    pWindow = nullptr;
    SDL_Quit();
}
