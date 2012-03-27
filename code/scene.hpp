#ifndef _scene_
#define _scene_

#include <SFML/Graphics.hpp>

namespace fff{
    
    class scene{
        public:
            virtual void Event(sf::Event &) = 0;
            virtual void Run(sf::RenderTarget &) = 0;
    };
    
}

#endif
