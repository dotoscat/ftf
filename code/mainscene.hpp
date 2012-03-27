#ifndef _mainscene_
#define _mainscene_

#include "scene.hpp"

namespace fff{
    
    class mainscene: public fff::scene{
        
        
        
        public:
            void Event(sf::Event &);
            void Run(sf::RenderTarget &);
    };
    
}

#endif
