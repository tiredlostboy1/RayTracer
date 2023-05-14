#include "CApp.hpp"
#include "../Math/vector.h"
#include <stdexcept>

// default constructor
CApp::CApp()
    : isRunning(true), pWindow(nullptr), pRenderer(nullptr)
{
}

bool CApp::OnInit()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return false;
    }

    pWindow = SDL_CreateWindow(
        "Ray Tracer",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        1280, 720,
        SDL_WINDOW_SHOWN);

    if (pWindow)
    {
        pRenderer = SDL_CreateRenderer(pWindow, -1, 0);

        // initialize the Image instance
        m_image.Initialize(1280, 720, pRenderer);

        //Set background to white
        SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
        SDL_RenderClear(pRenderer);

        //render the scene
        m_scene.Render(m_image);

        //display the image
        m_image.Display();

        //Show the result
        SDL_RenderPresent(pRenderer);

        // // Test the camera class
        // Camera testCamera;
        // testCamera.SetPosition(qbVector<double>(std::vector<double>{0.0, 0.0, 0.0}));
        // testCamera.SetLookAt(qbVector<double>(std::vector<double>{0.0, 2.0, 0.0}));
        // testCamera.SetUp(qbVector<double>(std::vector<double>{0.0, 0.0, 1.0}));
        // testCamera.SetLength(1.0);
        // testCamera.SetAspect(1.0);
        // testCamera.SetHorizontalSize(1.0);
        // testCamera.UpdateCameraGeometry();

        // //Get the screen centre and U, V vectors and display
        // auto screenCentre = testCamera.GetScreenCentre();
        // auto screenU = testCamera.GetU();
        // auto screenV = testCamera.GetV();

        // //display to the ternimal
        // std::cout << "Camera screen centre: " << std::endl;
        // PrintVector(screenCentre);
        // std::cout << "\nCamera U vector: " << std::endl;
        // PrintVector(screenU);
        // std::cout << "\nCamera V vector: " << std::endl;
        // PrintVector(screenV);
    }

    else
    {
        return false;
    }

    return true;
}

void CApp::OnExecute()
{
    SDL_Event event;
    if (!OnInit())
    {
        throw std::runtime_error("bye-bye!");
    }

    while (isRunning)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            OnEvent(&event);
        }

        OnLoop();
        OnRender();
    }
}

void CApp::OnEvent(SDL_Event *event)
{
    if (event->type == SDL_QUIT)
    {
        isRunning = false;
    }
}

void CApp::OnLoop()
{
}

void CApp::OnRender()
{
    // // setting background to white
    // SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
    // SDL_RenderClear(pRenderer);

    // // render the scene
    // m_scene.Render(m_image);

    // // displaty the image
    // m_image.Display();

    // // result
    // SDL_RenderPresent(pRenderer);
}

void CApp::OnExit()
{
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    pWindow = nullptr;
    SDL_Quit();
}

// PRIVATE FUNCTIONS

void CApp::PrintVector(const qbVector<double> &inputVector)
{
    int nRows = inputVector.GetNumDims();
    for (int row = 0; row < nRows; ++row)
    {
        std::cout << std::fixed << std::setprecision(3) << inputVector.GetElement(row) << std::endl;
    }
}