//Copyright (C) 2012 Oscar Triano Garcia <teritriano@gmail.com>

//This file is part of Free To Fall.

//Free To Fall is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//Free To Fall is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with Free To Fall.  If not, see <http://www.gnu.org/licenses/>.

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