#ifndef RENDERER_H
#define RENDERER_H
#include <SDL2/SDL.h>
#include <iostream>
class Renderer {
public:
    Renderer(SDL_Renderer* r) : renderer(r) { std::cout << "Renderer created\n"; }
    ~Renderer() { std::cout << "Renderer destroyed\n"; }
    SDL_Renderer* getRenderer() { return renderer; }
private:
    SDL_Renderer* renderer;
};
#endif
