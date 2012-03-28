#ifndef _explosive_
#define _explosive_

#include <SFML/Graphics.hpp>
#include <chipmunk/chipmunk.h>

namespace fff{
    
    struct explosive{
        
        bool exists;
        
        sf::Sprite sprite;
        cpShape *shape;
        
        float impulse;
        
        explosive();
        ~explosive();
        void prepareShape(cpSpace *);
        void Configure(const char *);
        
    };
    
}

#endif
