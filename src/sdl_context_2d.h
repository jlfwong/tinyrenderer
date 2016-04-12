#ifndef TINYRENDERER_SDL_CONTEXT_2D_H
#define TINYRENDERER_SDL_CONTEXT_2D_H


#include <SDL.h>
#include <algorithm>
#include <cmath>

class SdlContext2D {
public:
    SdlContext2D(Uint32 width, Uint32 height) : width_(width), height_(height) {
        pixels_ = new Uint32[width * height];
        memset(pixels_, 0, width * height * sizeof(Uint32));
    };

    ~SdlContext2D() {
        delete[] pixels_;
    };

    void SetColor(Uint32 x, Uint32 y, Uint32 color) {
        pixels_[y * width_ + x] = color;
    };

    void Line(Uint32 x0, Uint32 y0, Uint32 x1, Uint32 y1, Uint32 color);

    void Paint(SDL_Texture* texture) {
        SDL_UpdateTexture(texture, NULL, pixels_, width_ * sizeof(Uint32));
    };

private:
    Uint32 * pixels_;
    Uint32 width_;
    Uint32 height_;
};


#endif //TINYRENDERER_SDL_CONTEXT_2D_H
