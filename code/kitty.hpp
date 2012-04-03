#ifndef _kitty_
#define _kitty_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <chipmunk/chipmunk.h>

namespace fff{

    struct kitty{
        cpBody *body;
        cpShape *shape;
        sf::Sprite sprite;
        sf::Sprite flames[2];
        int iflames;
        
        cpSpace *forecastspace;
        cpBody forecastbody;
        
        cpVect lastpos;
        
        sf::Sound burst;
        bool burstplayed;
        
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
        bool burstInFlames();
        void applyImpulse(float);
        void Update();
        float forecastYPositionTo(float);
        cpVect getCurrentPos();
        sf::Sprite getCurrentFrame();
        
    };
    
}

#endif
