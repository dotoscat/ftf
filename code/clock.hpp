#ifndef _clock_
#define _clock_

#include <cstdio>
#include <string>
#include <SFML/System.hpp>

namespace fff{
    
    class clock{
        
        char buffer[12];//+\0

        public:

            sf::Uint32 ms;
            sf::Uint32 seconds;
            sf::Uint32 minutes;
            sf::Uint32 hours;
        
        public:
            bool operator<(fff::clock &);
            clock(){};
            clock(const fff::clock &);//copy constructor
            void Reset();
            void Update(sf::Uint32);
            char *getString();
        
    };
    
}

#endif