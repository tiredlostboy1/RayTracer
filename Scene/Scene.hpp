#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <SDL2/SDL.h>
#include "../Image/Image.hpp"

class Scene{
    public:
        Scene();

        //function to perform the rendering
        bool Render(Image &outputImage);

    private:
        
};

#endif