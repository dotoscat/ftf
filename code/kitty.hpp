#ifndef _kitty_
#define _kitty_

#include <SFML/Graphics.hpp>
#include <chipmunk/chipmunk.h>

namespace fff{

    struct kitty{
        cpBody *body;
        cpShape *shape;
        sf::Sprite sprite;
        
        kitty();
        ~kitty();
        void Configure();
        void setInitialFallingSpeed(float);
        void setPosition(float, float);
        void moveLeft();
        void stopMovingLeft();
        void moveRight();
        void stopMovingRight();
        float getHeight();
        float getVerticalSpeed();
        bool isFalling();
        bool isClimbing();
        void Update();
         
    };
    
}

#endif
