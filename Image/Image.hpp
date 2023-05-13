#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <SDL2/SDL.h>

class Image
{
public:
    Image();

    ~Image();

    // initialise
    void Initialize(const int xSize, const int ySize, SDL_Renderer *pRenderer);

    // set color of a pixel
    void SetPixel(const int x, const int y, const double red, const double green, const double blue);

    // image to display
    void Display();

    //functions to return dimensions of the image
    int GetXSize();
    int GetYSize();
    
private:
    // arrays to store the data
    std::vector<std::vector<double>> m_rChannel;
    std::vector<std::vector<double>> m_gChannel;
    std::vector<std::vector<double>> m_bChannel;

    // dimensions of the image
    int m_xSize, m_ySize;

    // SDL2
    SDL_Renderer *m_pRenderer;
    SDL_Texture *m_pTexture;

private:
    uint32_t ConvertColor(const double red, const double green, const double blue);
    void InitTexture();
};

#endif