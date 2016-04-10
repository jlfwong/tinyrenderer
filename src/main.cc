#include <SDL.h>

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

    Uint32 * pixels = new Uint32[width * height];

    // Clear all pixel values, setting all ARGB8 values for everything to 0x000000000
    memset(pixels, 0, width * height * sizeof(Uint32));

    for (Uint32 i = 0; i < height; i++) {
        for (Uint32 j = 0; j < width; j++) {
            if ((i / 10) % 2 == 0) {
                pixels[i * width + j] = 0xFFFF0000;
            } else {
                pixels[i * width + j] = 0xFF00FF00;
            }
        }
    }

    SDL_Event windowEvent;
    while (true)
    {
        SDL_UpdateTexture(texture, NULL, pixels, 640 * sizeof(Uint32));
        if (SDL_PollEvent(&windowEvent))
        {
            if (windowEvent.type == SDL_QUIT) break;
        }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    delete[] pixels;
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);

    return 0;
}