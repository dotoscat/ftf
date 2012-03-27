#ifndef _engine_
#define _engine_

#include <chipmunk/chipmunk.h>
#include "scene.hpp"
#include "kitty.hpp"
#include "clock.hpp"

#define PIXELSTOMETERS(x) x/10.f
#define METERSTOPIXELS(x) x*10.f

namespace fff{
    
    class engine: public fff::scene{
        cpSpace *space;
        sf::View camera;
        sf::Sprite floor;
        cpShape *shapefloor, *shapeleftlimit, *shaperightlimit;
        fff::clock engineclock;
        sf::Text clock;
        sf::Text speed;
        sf::Text km_h;
        sf::Text height;
        sf::Text meters;
        
        sf::Uint32 time;
        
        fff::kitty kitty;
        
        public:
            engine();
            ~engine();
            void Reset();
            void loadResources();
            void Event(sf::Event &);
            void Run(sf::RenderTarget &);
        
        
    };
    
}

#endif
