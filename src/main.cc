#include <SDL2/SDL.h>

int main(int argc, char* args[]) {
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* screen = SDL_CreateWindow("Hello World",
                                           SDL_WINDOWPOS_UNDEFINED,
                                           SDL_WINDOWPOS_UNDEFINED,
                                           640, 480,
                                           SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    SDL_Delay(2000);

    SDL_Quit();
    return 0;
}
