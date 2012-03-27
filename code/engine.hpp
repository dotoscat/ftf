#ifndef _engine_
#define _engine_

#include <chipmunk/chipmunk.h>
#include "scene.hpp"

namespace fff{
    
    class engine: public fff::scene{
        cpSpace *space;
        sf::View camera;
                
        public:
            engine();
            ~engine();
            void Event(sf::Event &);
            void Run(sf::RenderTarget &);
        
        
    };
    
}

#endif
