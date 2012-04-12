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

#ifndef _engine_
#define _engine_

#include <chipmunk/chipmunk.h>
#include "scene.hpp"
#include "kitty.hpp"
#include "clock.hpp"
#include "explosive.hpp"
#include "engine_menu.hpp"
#include "bg.hpp"
#include "particle.hpp"

#define PIXELSTOMETERS(x) x/100.f
#define METERSTOPIXELS(x) x*100.f

#define MAXEXPLOSIVES 7

namespace fff{
    
    class engine: public fff::scene{
        cpSpace *space;
        sf::View camera;
        sf::Sprite floor;
        cpShape *shapeleftlimit, *shaperightlimit;
        fff::clock engineclock;
        sf::Text clock;
        sf::Text speed;
        sf::Text km_h;
        sf::Text height;
        sf::Text meters;
        
        sf::Text ascending, falling;
        
        sf::Uint32 time;
        
        fff::kitty kitty;
        fff::explosive explosive[MAXEXPLOSIVES];
        
        sf::Shape flash;
        sf::Text txtgameover;
        
        fff::bg bg;
        fff::emitter emitter;
        
        enum _status{
            running,
            pause,
            gameover
        }status;
        
        engine_menu menu;
                
        public:
            engine();
            ~engine();
            void Reset();
            void loadResources();
            void Event(sf::Event &);
            void Run(sf::RenderTarget &);
            void Continue();
            void saveScore();
            float getHeight();
            fff::clock getClock();
            
            static int preSolve_kitty_leftlimit(cpArbiter *, cpSpace * , void *);
            static int preSolve_kitty_rightlimit(cpArbiter *, cpSpace * , void *);
            
        protected:
            int createExplosive();
            bool generateExplosive();
            bool generateExplosiveWhileFalling();
            bool generateExplosiveWhileAscending();
            void drawHUD(sf::RenderTarget &, sf::FloatRect &);
            
    };
    
}

#endif
