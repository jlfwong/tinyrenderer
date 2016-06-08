#ifndef TINYRENDERER_SDL_CONTEXT_2D_H
#define TINYRENDERER_SDL_CONTEXT_2D_H


#include <SDL.h>
#include <algorithm>
#include <cmath>
#include <cassert>
#include "vec.h"

class SdlContext2D {
public:
    SdlContext2D(Uint32 width, Uint32 height) : width_(width), height_(height) {
        pixels_ = new Uint32[width * height];
        memset(pixels_, 0, width * height * sizeof(Uint32));
    };

    ~SdlContext2D() {
        delete[] pixels_;
    };


    void Clear() {
        memset(pixels_, 0, width_ * height_ * sizeof(Uint32));
    }

    void SetColor(int x, int y, Uint32 color) {
        if (x < 0 || x >= width_ || y < 0 || y >= height_) {
            return;
        }
        pixels_[y * width_ + x] = color;
    };

    // Draw a line from (x0, y0) to (x1, y1) in the specified color.
    void Line(int x0, int y0, int x1, int y1, Uint32 color);

    // Fill an axis aligned rectangle with opposing corners at (x0, y0) and
    // (x1, y1);
    void FillRect(float x0, float y0, float x1, float y1, Uint32 color);

    // Fill the triangle defined the three distinct points (x0, y0), (x1, y1),
    // (x2, y2);
    void FillTriangle(float x0, float y0,
                      float x1, float y1,
                      float x2, float y2,
                      Uint32 color);

    void Paint(SDL_Texture* texture) {
        SDL_UpdateTexture(texture, NULL, pixels_, width_ * sizeof(Uint32));
    };

private:
    Uint32 * pixels_;
    Uint32 width_;
    Uint32 height_;
};


#endif //TINYRENDERER_SDL_CONTEXT_2D_H
