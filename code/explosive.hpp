#ifndef _explosive_
#define _explosive_

#include <SFML/Graphics.hpp>
#include <chipmunk/chimpunk.h>
#include "auxiliar.hpp"
#include "game.hpp"

namespace fff{
    
    struct explosive{
        
        bool exists;
        
        sf::Sprite sprite;
        cpShape *shape;
        
        float impulse;
        
        explosive();
        ~explosive();
        
    };
    
}

#endif
