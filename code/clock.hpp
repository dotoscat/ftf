#ifndef _clock_
#define _clock_

#include <cstdio>
#include <string>
#include <SFML/System.hpp>

namespace fff{
    
    class clock{
        sf::Uint32 ms;
        sf::Uint32 secs;
        sf::Uint32 min;
        sf::Uint32 hours;
        
        char buffer[12];//+\0
        
        public:
            void Reset();
            void Update(sf::Uint32);
            char *getString();
        
    };
    
}

#endif