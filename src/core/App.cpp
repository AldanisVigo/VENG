#include "App.h"
#include <iostream>
#include <cstdlib>
#include <SDL2/SDL_image.h>
#include "Input.h"

App::App(const std::string& title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
        std::exit(1);
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "IMG_Init failed: " << IMG_GetError() << std::endl;
        std::exit(1);
    }

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << std::endl;
        std::exit(1);
    }

    SDL_Renderer* sdlRenderer = SDL_CreateRenderer(window, -1,
                                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!sdlRenderer) {
        std::cerr << "SDL_CreateRenderer failed: " << SDL_GetError() << std::endl;
        std::exit(1);
    }

    input = new Input();

    renderer = new Renderer(sdlRenderer);
    lastTick = SDL_GetTicks();
}

App::~App() {
    delete renderer;
    delete input;
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

Renderer* App::getRenderer() { return renderer; }
SDL_Window* App::getWindow() { return window; }

void App::loop() {
    while (running) {
        if (onReady && !readyCalled) {
            onReady();
            readyCalled = true;
        }

        Uint32 now = SDL_GetTicks();
        float dt = (now - lastTick) / 1000.0f;
        lastTick = now;

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;
        }

        SDL_RenderClear(renderer->getRenderer());

        if (update)
            update(dt);

        SDL_RenderPresent(renderer->getRenderer());
    }
}
