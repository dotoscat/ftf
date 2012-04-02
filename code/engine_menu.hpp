#ifndef _engine_menu_
#define _engine_menu_

#include <SFML/Graphics.hpp>

namespace fff{
    
    class engine_menu{
        
        sf::Shape bg;
        sf::Text selection[2];
        int iselection;
        
        public:
        
            engine_menu();
            void Event(sf::Event &);
            void Run(sf::RenderTarget &);
        
    };
    
}

#endif
