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

    void Line(Uint32 x0, Uint32 y0, Uint32 x1, Uint32 y1, Uint32 color) {
        bool is_steep = std::abs(1.0 * y1 - y0) > std::abs(1.0 * x1 - x0);

        // Make our line always left-to-right
        if (x0 > x1) {
            std::swap(x0, x1);
            std::swap(y0, y1);
        }

        if (is_steep) {
            std::swap(x0, y0);
            std::swap(x1, y1);
        }
        const double derr = std::abs(1.0 * y1 - y0) / (x1 - x0);
        double err = 0.0;

        Uint32 y = y0;
        for (Uint32 x = x0; x <= x1; x++) {
            if (is_steep) {
                SetColor(y, x, color);
            } else {
                SetColor(x, y, color);
            }
            err += derr;
            if (err > 0.5) {
                y += (y1 > y0 ? 1 : -1);
                err -= 1.0;
            }
        }
    };

    void Paint(SDL_Texture* texture) {
        SDL_UpdateTexture(texture, NULL, pixels_, width_ * sizeof(Uint32));
    };

private:
    Uint32 * pixels_;
    Uint32 width_;
    Uint32 height_;
};


#endif //TINYRENDERER_SDL_CONTEXT_2D_H
