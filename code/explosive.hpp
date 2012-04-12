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

#ifndef _explosive_
#define _explosive_

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <chipmunk/chipmunk.h>

namespace fff{
    
    struct explosive{
        
        enum _status{
            normal,
            exploding
        }status;
        
        sf::Uint32 timeexploding;
        sf::Uint32 lifespan;
        sf::Uint32 acumlifespan;
        
        bool exists;
        
        sf::Sprite explosion;
        sf::Sprite sprite;
        sf::Sprite signal;
        sf::Text meters;
        sf::SoundBuffer *soundbuffer;
        cpShape *shape;
        
        float impulse;
        
        explosive();
        ~explosive();
        void loadResources();
        void prepareShape(cpSpace *);
        void Configure(const char *);
        void setPosition(float, float);
        void setSignalAtBottom();
        void setSignalAtTop();
        void Update(float);
        void setExploding();
        bool isExploding();
        bool isExploded();
        bool isOver();
        
        static int Begin(cpArbiter *, cpSpace *, void *);
        static void postStep(cpSpace *, void *, void *);
        
    };
    
}

#endif
