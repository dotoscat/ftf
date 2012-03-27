#ifndef _engine_
#define _engine_

#include <chipmunk/chipmunk.h>
#include "scene.hpp"
#include "kitty.hpp"

#define PIXELSTOMETERS(x) x/10.f
#define METERSTOPIXELS(x) x*10.f

namespace fff{
    
    class engine: public fff::scene{
        cpSpace *space;
        sf::View camera;
        fff::kitty kitty;
        sf::Sprite floor;
        cpShape *shapefloor;
        sf::Text speed;
        sf::Text km_h;
        sf::Text height;
        sf::Text meters;
        
        sf::Uint32 time;
        
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
