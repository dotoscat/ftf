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

#ifndef _collisions_
#define _collisions_

#include <chipmunk/chipmunk.h>

namespace fff{
    
    namespace collisions{
        
        namespace types{
            extern cpCollisionType kitty;
            extern cpCollisionType explosive;
            extern cpCollisionType leftlimit;
            extern cpCollisionType rightlimit;
        }
        
        namespace groups{
            extern cpGroup explosive;
        }
        
    }
    
}

#endif
