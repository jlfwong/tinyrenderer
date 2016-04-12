#include <SDL.h>
#include <iostream>
#include "sdl_context_2d.h"
#include "third_party/tiny_obj_loader.h"
#include "polygon3D.h"

int main(int argc, char* args[]) {
    SDL_Init(SDL_INIT_EVERYTHING);

    const Uint32 width = 640;
    const Uint32 height = 480;

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

    std::vector<Polygon3D> faces;

    for (auto const& shape : shapes) {
        Uint32 index_offset = 0;
        for (auto const& n_vertices_in_face : shape.mesh.num_vertices) {

            std::vector<Point3D> points_in_face;

            for (auto index_in_face = 0;
                     index_in_face < n_vertices_in_face;
                     index_in_face++) {

                auto vertex_index = index_offset + index_in_face;
                auto position_index = shape.mesh.indices[vertex_index];

                points_in_face.push_back(Point3D(
                    shape.mesh.positions[3 * position_index + 0],
                    shape.mesh.positions[3 * position_index + 1],
                    shape.mesh.positions[3 * position_index + 2]));
            }

            // TODO(jlfwong): Lots of avoidable superfluous copying happening here
            faces.push_back(Polygon3D(points_in_face));

            index_offset += n_vertices_in_face;
        }
    }

    SdlContext2D context(width, height);

    for (auto& face : faces) {
        auto points = face.points();
        for (auto i = 0; i < points.size(); i++) {
            auto from = points[i];
            auto to = points[i % points.size()];
            context.Line(
                (from.x() + 0.5) * width, (-from.y() + 0.5) * height,
                (to.x() + 0.5) * width, (-from.y() + 0.5) * height,
                0xFFFF0000);
        }

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