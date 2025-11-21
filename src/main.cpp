#include <iostream>
#include "core/App.h"
#include "core/AnimatedSprite.h"
#include "core/Transform.h"

int main() {
    // Create game things
    Transform* playerTransform = new Transform(100, 100); // In the stack does not need to be deleted.
    AnimatedSprite* sprite = nullptr;

    // Create a game
    App game("Engine Demo", 800, 600);

    // Add your onReady function
    game.setOnReady([&]() {
        sprite = new AnimatedSprite(playerTransform, game.getRenderer(),
                                            "assets/sprite.png", 18, 35);

        // Set the scale of the animated sprite
        sprite->setScale(2);

        // Wether the sprite is flipped horizontally or not
        sprite->setFlipH(true);

        // Add animation
        sprite->addAnimation("walk",0,4, 200);
        sprite->addAnimation("attack",5,6, 200);

        // Play an animation
        sprite->playAnimation("attack");

    });

    // Add your update function
    game.setUpdate([&](float dt) {
        game.getInput()->update();

        if (!sprite) return;

        if(game.getInput()->getAction() == Action::left){
            std::cout << "Current Sprite Animation: " << sprite->getCurrentAnimName() << std::endl;
            sprite->setFlipH(true);
            if(sprite->getCurrentAnimName() != "walk"){
                sprite->playAnimation("walk");
            }
            playerTransform->getPosition().x -= 1;
        }else if(game.getInput()->getAction() == Action::right){
            sprite->setFlipH(false);

             if(sprite->getCurrentAnimName() != "walk"){
                sprite->playAnimation("walk");
            }
            playerTransform->getPosition().x += 1;
        }else{
            std::cout << "Switching back to attack\n"; 
            if(sprite->getCurrentAnimName() != "attack"){
                sprite->playAnimation("attack");
            }
        }

        sprite->update();
    });

    // begin the game loop
    game.loop();

    // Delete game things
    delete sprite;
    delete playerTransform;

    // Exit the program
    return 0;
}
