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

#ifndef _particle_
#define _particle_

#include <SFML/Graphics.hpp>

namespace fff{
    
    class emitter{
        
        class particle{
            float alpha;
            sf::Vector2f scale;
            sf::Uint32 lifespan;
            sf::Uint32 storetime;
            
            public:
                mutable bool exists;
                mutable sf::Sprite sprite;
            
            public:
                particle();
                void loadResources();
                void Create(sf::Uint32, sf::Vector2f);
                void Update(sf::Uint32);
                void Reset();
            
        };
        
        particle *particles;
        int nparticles;
        sf::Uint32 parpersec;
        sf::Uint32 storetime;
        sf::Vector2f pos;
        sf::Uint32 lifespanparticle;
        
        public:
            emitter();
            ~emitter();
            void setParticles(int);
            void loadResources();
            void setParticlesPerSec(int);
            void setPos(float, float);
            void setLifespan(int);
            void Process(sf::RenderTarget &, sf::Uint32);
            void Reset();
                    
    };
    
}

#endif
