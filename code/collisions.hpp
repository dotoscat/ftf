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
