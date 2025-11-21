#ifndef APP_H
#define APP_H

#include <SDL2/SDL.h>
#include <string>
#include <functional>
#include "Renderer.h"
#include "Input.h"

class App {
public:
    App(const std::string& title, int width, int height);
    ~App();

    void loop();
    Renderer* getRenderer();
    SDL_Window* getWindow();

    void setUpdate(std::function<void(float)> cb) { update = cb; }
    void setOnReady(std::function<void(void)> cb) { onReady = cb; }

    Input* getInput() {
        return this->input;
    }

private:
    bool running = true;
    bool readyCalled = false;
    Uint32 lastTick = 0;

    SDL_Window* window = nullptr;
    Renderer* renderer = nullptr;

    std::function<void(float)> update;
    std::function<void(void)> onReady;

    Input* input = nullptr;
};

#endif
