#include "Image.hpp"

Image::Image()
    : m_xSize(0), m_ySize(0), m_pTexture(nullptr)
{
}

Image::~Image()
{
    if (m_pTexture)
    {
        SDL_DestroyTexture(m_pTexture);
    }
}

void Image::Initialize(const int xSize, const int ySize, SDL_Renderer *pRenderer)
{
    m_rChannel.resize(xSize, std::vector<double>(ySize, 0.));
    m_gChannel.resize(xSize, std::vector<double>(ySize, 0.));
    m_bChannel.resize(xSize, std::vector<double>(ySize, 0.));

    m_xSize = xSize;
    m_ySize = ySize;

    m_pRenderer = pRenderer;

    InitTexture();
}

void Image::SetPixel(const int x, const int y, const double red, const double green, const double blue)
{
    m_rChannel.at(x).at(y) = red;
    m_gChannel.at(x).at(y) = green;
    m_bChannel.at(x).at(y) = blue;
}

int Image::GetXSize()
{
    return m_xSize;
}

int Image::GetYSize()
{
    return m_ySize;
}

void Image::Display()
{
    uint32_t *tempPixels = new uint32_t[m_xSize * m_ySize];

    memset(tempPixels, 0, m_xSize * m_ySize * sizeof(uint32_t));

    for (int x = 0; x < m_xSize; ++x)
    {
        for (int y = 0; y < m_ySize; ++y)
        {
            tempPixels[y * m_xSize + x] = ConvertColor(m_rChannel.at(x).at(y), m_gChannel.at(x).at(y), m_bChannel.at(x).at(y));
        }
    }

    SDL_UpdateTexture(m_pTexture, nullptr, tempPixels, m_xSize * sizeof(uint32_t));

    delete[] tempPixels;

    SDL_Rect srcRect, bounds;
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = m_xSize;
    srcRect.h = m_ySize;
    bounds = srcRect;
    SDL_RenderCopy(m_pRenderer, m_pTexture, &srcRect, &bounds);
}

void Image::InitTexture()
{
    uint32_t rmask = 0x000000ff, gmask = 0x0000ff00, bmask = 0x00ff0000, amask = 0xff000000;

    if (m_pTexture)
    {
        SDL_DestroyTexture(m_pTexture);
    }

    SDL_Surface *tempSurface = SDL_CreateRGBSurface(0, m_xSize, m_ySize, 32, rmask, gmask, bmask, amask);
    m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, tempSurface);
    SDL_FreeSurface(tempSurface);
}

uint32_t Image::ConvertColor(const double red, const double green, const double blue)
{
    unsigned char r = static_cast<unsigned char>(red);
    unsigned char g = static_cast<unsigned char>(green);
    unsigned char b = static_cast<unsigned char>(blue);

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    uint32_t pixelColor = (r << 24) + (g << 16) + (b << 8) + 255;
#else
    uint32_t pixelColor = (255 << 24) + (b << 16) + (g << 16) + r;
#endif

    return pixelColor;
}