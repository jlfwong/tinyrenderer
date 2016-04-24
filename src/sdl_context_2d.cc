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

void SdlContext2D::FillRect(float x0, float y0, float x1, float y1,
                            Uint32 color) {
    if (x1 < x0) {
        std::swap(x1, x0);
    }
    if (y1 < y0) {
        std::swap(y1, y0);
    }
    for (float y = y0; y <= y1; y++) {
        for (float x = x0; x <= x1; x++) {
            SetColor(static_cast<int>(x + 0.5f), static_cast<int>(y + 0.5f),
                     color);
        }
    }
}

void SdlContext2D::FillTriangle(float x0, float y0, float x1, float y1,
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

    // Now, we fill the triangle for the scan lines where y0 <= i <= y1.
    // TODO(jlfwong): This should probably be an epsilon check?
    if (y0 == y1) {
        FillRect(x0, y0, x1, y1, color);
    } else {
        // For each scan-line, we find the left and right edges by examining
        // the intersections of the line y = i with the line segments
        // (x0, y0)<->(x1, y1) and (x0, y0)<->(x2, y2).

        // The equation of line 1 is:
        // x = a*y + b
        //
        // (1)                x0 = a*y0 + b
        // (2)                x1 = a*y1 + b
        //
        // (3) = (2) - (1)    x1 - x0 = a*(y1 - y0)
        //                          a = (x1 - x0) / (y1 - y0), y1 != y0
        //
        // (3) -> (1)         x0 = a*y0 + b
        //                     b = x0 - a*y0
        auto a01 = 1.0 * (x1 - x0) / (y1 - y0);
        auto b01 = x0 - a01 * y0;

        auto a02 = 1.0 * (x2 - x0) / (y2 - y0);
        auto b02 = x0 - a02 * y0;

        for (float y = y0; y < y1; y++) {
            auto left = a01*y + b01;
            auto right = a02*y + b02;
            if (right < left) {
                std::swap(left, right);
            }

            FillRect(left, y, right, y, color);
        }
    }

    // Finally, we fill the rest of the triangles by drawing the scan-lines
    // where y1 < i <= y2.
    //
    // TODO(jlfwong): De-duplicate this code with above by making a method to
    // fill between two rays from a single point between a range of y
    // coordinates.
    if (y1 == y2) {
        FillRect(x1, y1, x2, y2, color);
    } else {
        auto a02 = 1.0f * (x2 - x0) / (y2 - y0);
        auto b02 = x0 - a02 * y0;

        auto a12 = 1.0f * (x2 - x1) / (y2 - y1);
        auto b12 = x1 - a12 * y1;

        for (float y = y1; y <= y2; y++) {
            auto left = a02*y + b02;
            auto right = a12*y + b12;
            if (right < left) {
                std::swap(left, right);
            }

            FillRect(left, y, right, y, color);
        }
    }
}
