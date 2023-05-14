#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <SDL2/SDL.h>
#include "../Image/Image.hpp"
#include "../Camera/Camera.hpp"
#include "../Objects/ObjSphere.hpp"

class Scene{
    public:
        Scene();

        //function to perform the rendering
        bool Render(Image &outputImage);

    private:
        //the camera that we will use
        Camera m_camera;

        //a unit sphere on the origin, for testing
        ObjSphere m_testSphere;
};

#endif