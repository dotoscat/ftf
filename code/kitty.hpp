//Copyright (C) 2012 Oscar Triano Garcia <teritriano@gmail.com>

//This file is part of Free To Fall.

//Free To Fall is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//Free To Fall is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with Free To Fall.  If not, see <http://www.gnu.org/licenses/>.

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
        bool burstinflames;
        bool leftimpulse;
        bool rightimpulse;
        
        kitty();
        ~kitty();
        void Reset();
        void Configure();
        void setInitialFallingSpeed(float);
        void setPosition(float, float);
        void moveLeft();
        void stopMovingLeft();
        void moveRight();
        void stopMovingRight();
        float getHeight();
        float getX();
        float getVerticalSpeed();
        float getVerticalSpeedPxls();
        bool isFalling();
        bool isAscending();
        bool burstInFlames();
        void applyImpulse(float);
        void Update();
        float forecastYPositionTo(float);
        cpVect getCurrentPos();
        sf::Sprite getCurrentFrame();
        
    };
    
}

#endif
