#include <algorithm>
#include <iostream>

#include <SDL.h>

#include "sdl_context_2d.h"
#include "third_party/tiny_obj_loader.h"
#include "vec.h"
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

        context.FillTriangle(x0, y0, x1, y1, x2, y2,
                             (rand() | 0xFF000000));
        // context.Line(x0, y0, x1, y1, 0xFFFF0000);
    }

    SDL_Event windowEvent;
    while (true)
    {
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