#ifndef _mainscene_
#define _mainscene_

#include "scene.hpp"

namespace fff{
    
    class mainscene: public fff::scene{
        
        sf::Text title;
        sf::Text instruction;
        
        public:
            mainscene();
            void Event(sf::Event &);
            void Run(sf::RenderTarget &);
            
    };
    
}

#endif
