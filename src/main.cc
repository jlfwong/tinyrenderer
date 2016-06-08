#include <algorithm>
#include <iostream>

#include <SDL.h>

#include "sdl_context_2d.h"
#include "third_party/tiny_obj_loader.h"
#include "mesh.h"

int main(int argc, char* args[]) {
    SDL_Init(SDL_INIT_EVERYTHING);

    const Uint32 width = 1024;
    const Uint32 height = 768;

    SDL_Window* window = SDL_CreateWindow("Hello World",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,

                                          width, height,
                                          SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture * texture = SDL_CreateTexture(renderer,
                                              SDL_PIXELFORMAT_ARGB8888,
                                              SDL_TEXTUREACCESS_STATIC,
                                              width, height);

    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string err;

    tinyobj::LoadObj(shapes, materials, err, "data/bunny.obj");

    // TODO(jlfwong): Deal with multiple meshes in the same .obj file
    Mesh mesh = Mesh(shapes[0]);

    SdlContext2D context(width, height);

    SDL_Event windowEvent;

    Vec3f light_dir = Vec3f(1, 1, -1).normalized();
    Vec3f eye_dir = Vec3f(0, 0, -1).normalized();

    float light_angle = 0;

    while (true)
    {
        light_angle += M_PI / 100;
        if (light_angle > 2 * M_PI) {
            light_angle -= 2 * M_PI;
        }

        Vec3f light_dir = Vec3f(cos(light_angle),1,sin(light_angle)).normalized();

        context.Clear();

        for (auto& face : mesh.faces()) {
            // Lazily assume for now that all faces are triangularized.
            assert(face.size() == 3);
            auto scale = 4;

            auto x0 = scale * face[0].x() * width + width / 2;
            auto y0 = -scale * face[0].y() * height + height;

            auto x1 = scale * face[1].x() * width + width / 2;
            auto y1 = -scale * face[1].y() * height + height;

            auto x2 = scale * face[2].x() * width + width / 2;
            auto y2 = -scale * face[2].y() * height + height;

            // Backface culling
            if (face.normal().dot(eye_dir) <= 0){
                continue;
            }

            // TODO(jlfwong): Replace this will support for real materials
            float intensity = face.normal().dot(light_dir);
            if (intensity < 0) intensity = 0;

            // 20% light to everything (ambient), 80% from diffuse
            uint8_t intensity256 = 0xFF * (0.2 + 0.8*intensity);
            uint32_t color = (0xFF << 24) |
                             (intensity256 << 16) |
                             (intensity256 << 8) |
                             intensity256;
            context.FillTriangle(x0, y0, x1, y1, x2, y2, color);
            // context.Line(x0, y0, x1, y1, 0xFFFF0000);
        }
        context.Paint(texture);
        if (SDL_PollEvent(&windowEvent))
        {
            if (windowEvent.type == SDL_QUIT) break;
        }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);

    return 0;
}