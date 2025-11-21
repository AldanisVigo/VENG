#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <map>
#include <string>
#include "Renderer.h"
#include "Transform.h"

struct Animation {
    std::string name;
    int startFrame;      // first frame index in spritesheet
    int frameCount;      // number of frames
    Uint32 frameDelay;   // milliseconds per frame
};

class AnimatedSprite {
public:
    AnimatedSprite(Transform* transform, Renderer* renderer,
                   const std::string& path, int frameWidth, int frameHeight)
        : transform(transform), renderer(renderer),
          frameWidth(frameWidth), frameHeight(frameHeight)
    {
        spriteTexture = IMG_LoadTexture(renderer->getRenderer(), path.c_str());
        if (!spriteTexture) {
            std::cerr << "Failed to load texture: " << IMG_GetError() << std::endl;
        }
        SDL_SetTextureBlendMode(spriteTexture, SDL_BLENDMODE_BLEND);
    }

    ~AnimatedSprite() {
        SDL_DestroyTexture(spriteTexture);
    }

    // Add a new animation
    void addAnimation(const std::string& name, int startFrame, int frameCount, Uint32 delay) {
        animations[name] = Animation{name, startFrame, frameCount, delay};
    }

    // Switch to a different animation
    void playAnimation(const std::string& name) {
        if (currentAnimName == name) return; // already playing
        auto it = animations.find(name);
        if (it != animations.end()) {
            currentAnim = &it->second;
            currentAnimName = name;
            currentFrame = 0;                  // <-- index within this animation
            lastTick = SDL_GetTicks();
        } else {
            std::cerr << "Animation not found: " << name << std::endl;
        }
    }

    void update() {
        if (!currentAnim) return;

        Uint32 now = SDL_GetTicks();
        if (now - lastTick > currentAnim->frameDelay) {
            currentFrame++;
            if (currentFrame >= currentAnim->frameCount)
                currentFrame = 0; // loop within animation
            lastTick = now;
        }

        render((int)transform->getPosition().getX(),
            (int)transform->getPosition().getY());
    }

    std::string getCurrentAnimName() const {
        return currentAnimName;
    }

    void setScale(float scale){
        this->scale = scale;
    }

    void setFlipH(bool flip){
        this->flip_h = flip;
    }

private:
    float scale = 1.0;
    bool flip_h = false;
    void render(int x, int y) {
        if (!spriteTexture || !currentAnim) return;

        int frameIndex = currentAnim->startFrame + currentFrame;

        SDL_Rect src{ frameIndex * frameWidth, 0, frameWidth, frameHeight };
        SDL_Rect dst{
            x,
            y,
            static_cast<int>(frameWidth * scale),
            static_cast<int>(frameHeight * scale)
        };

        SDL_RendererFlip flip = flip_h ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

        SDL_RenderCopyEx(
            renderer->getRenderer(),
            spriteTexture,
            &src,
            &dst,
            0.0,          // rotation angle
            nullptr,      // center of rotation (nullptr = center)
            flip
        );
    }


    SDL_Texture* spriteTexture = nullptr;
    Transform* transform = nullptr;
    Renderer* renderer = nullptr;

    int frameWidth, frameHeight;
    int currentFrame = 0;
    Uint32 lastTick = 0;

    std::map<std::string, Animation> animations;
    Animation* currentAnim = nullptr;
    std::string currentAnimName;
};

#endif
