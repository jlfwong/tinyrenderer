#include "sdl_context_2d.h"

void SdlContext2D::Line(int x0, int y0, int x1, int y1, Uint32 color) {
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
    const double delta_err = std::abs(1.0 * y1 - y0) / (x1 - x0);
    double err = 0.0;

    int y = y0;
    for (int x = x0; x <= x1; x++) {
        if (is_steep) {
            SetColor(y, x, color);
        } else {
            SetColor(x, y, color);
        }
        err += delta_err;
        if (err > 0.5) {
            y += (y1 > y0 ? 1 : -1);
            err -= 1.0;
        }
    }
};
