#include "sdl_context_2d.h"

// TODO(jlfwong): Add simple tests for this using Google Mock and subclassing
// SdlContext2D to over-ride SetColor.
void SdlContext2D::Line(int x0, int y0, int x1, int y1, Uint32 color) {
    bool is_steep = std::abs(1.0 * y1 - y0) > std::abs(1.0 * x1 - x0);

    // Simplify code below by always iterating over x
    if (is_steep) {
        std::swap(x0, y0);
        std::swap(x1, y1);
    }

    // Make our line always left-to-right
    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    const float delta_err = std::abs(1.0f * y1 - y0) / (x1 - x0);
    float err = 0.0;

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

void SdlContext2D::FillRect(float x0, float y0, float x1, float y1,
                            Uint32 color) {
    if (x1 < x0) {
        std::swap(x1, x0);
    }
    if (y1 < y0) {
        std::swap(y1, y0);
    }

    int y_low = static_cast<int>(std::ceil(y0));
    int y_high = static_cast<int>(std::floor(y1));

    int x_low = static_cast<int>(std::ceil(x0));
    int x_high = static_cast<int>(std::floor(x1));

    for (int y = y_low; y <= y_high; y++) {
        for (int x = x_low; x <= x_high; x++) {
            SetColor(x, y, color);
        }
    }
}

void SdlContext2D::FillTriangle(float x0, float y0,
                                float x1, float y1,
                                float x2, float y2,
                                Uint32 color) {
    // Line sweeping algorithm.

    // We assume the triangle coordinates are not all co-linear.
    assert(!(x0 == x1 && x1 == x2) && !(y0 == y1 && y1 == y2) &&
           "Coordinates must not be colinear");

    // First, sort the coordinates so that they're top to bottom.
    if (y1 < y0) {
        std::swap(x1, x0);
        std::swap(y1, y0);
    }

    if (y2 < y1) {
        std::swap(y2, y1);
        std::swap(x2, x1);

        if (y1 < y0) {
            std::swap(x1, x0);
            std::swap(y1, y0);
        }
    }

    int y_low = static_cast<int>(std::ceil(y0));
    int y_mid = static_cast<int>(std::ceil(y1));
    int y_high = static_cast<int>(std::floor(y2));

    // Fill the top part of the triangle, where y0 <= y < y1
    if (std::abs(y0 - y1) < 1e-4) {
        FillRect(x0, y0, x1, y1, color);
    } else {
        for (int y = y_low; y < y_mid; y++) {
            // Linearly interpolate the x coordinate for each side of the line
            // segment
            float x_a = x0 + (x1 - x0) * (y - y0) / (y1 - y0);
            float x_b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
            FillRect(x_a, y, x_b, y, color);
        }
    }

    // Fill the bottom part of the triangle, where y1 <= y <= y2
    if (y1 == y2) {
        FillRect(x1, y1, x2, y2, color);
    } else {
        for (int y = y_mid; y <= y_high; y++) {
            float x_a = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
            float x_b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
            FillRect(x_a, y, x_b, y, color);
        }
    }
}
