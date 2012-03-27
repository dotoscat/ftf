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
        void setInitialFallingSpeed(float);
        void setPosition(float, float);
        float getHeight();
        float getVerticalSpeed();
        void Update();
         
    };
    
}

#endif
