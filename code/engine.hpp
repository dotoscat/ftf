#ifndef _engine_
#define _engine_

#include <chipmunk/chipmunk.h>
#include "scene.hpp"
#include "kitty.hpp"

namespace fff{
    
    class engine: public fff::scene{
        cpSpace *space;
        sf::View camera;
        fff::kitty kitty;
        sf::Sprite floor;
        cpShape *shapefloor;
        
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
