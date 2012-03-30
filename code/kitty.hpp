#ifndef _kitty_
#define _kitty_

#include <SFML/Graphics.hpp>
#include <chipmunk/chipmunk.h>

namespace fff{

    struct kitty{
        cpBody *body;
        cpShape *shape;
        sf::Sprite sprite;
        
        cpSpace *forecastspace;
        cpBody forecastbody;
        
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
        float getVerticalSpeedPxls();
        bool isFalling();
        bool isClimbing();
        void applyImpulse(float);
        void Update();
        float forecastYPositionTo(float);
         
    };
    
}

#endif
