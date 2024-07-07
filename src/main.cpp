#include <SDL2/SDL.h>

#include "sandbox.h"

SDL_Window *window;
SDL_Renderer *renderer;

bool running = true;
int WIN_W = 640, WIN_H = 480;
int scale = 4;

const int FPS = 60;
const float frameDelay = 1000.0 / FPS;
Uint32 frameStart;
Uint32 frameTime;


sandbox *engine;

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Sandbox", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_W, WIN_H, 0);
    renderer = SDL_CreateRenderer(window, 0, 0);

    elements placeType = empty;
    int xPos, yPos;

    engine = new sandbox(WIN_W, WIN_H, scale, window, renderer);

    while (running) {
        frameStart = SDL_GetTicks();

        SDL_PumpEvents();
        const Uint8* keyStates = SDL_GetKeyboardState(NULL);

        if (SDL_QuitRequested()) {
            running = false;
            break;
        }

        if (keyStates[SDL_SCANCODE_4]) placeType = empty;
        if (keyStates[SDL_SCANCODE_1]) placeType = water;
        if (keyStates[SDL_SCANCODE_2]) placeType = sand;
        if (keyStates[SDL_SCANCODE_3]) placeType = wood;

        if (SDL_GetMouseState(&xPos, &yPos) & SDL_BUTTON_LMASK) {
            engine->placeElement(xPos, yPos, placeType);
        }

        engine->update();
        engine->render();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
            SDL_Delay(frameDelay - frameTime);
    }

    delete engine;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
