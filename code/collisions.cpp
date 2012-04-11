#include "collisions.hpp"

namespace fff{
    
    namespace collisions{
        
        namespace types{
            cpCollisionType kitty = 1;
            cpCollisionType explosive = 2;
            cpCollisionType leftlimit = 3;
            cpCollisionType rightlimit = 4;
        }
        
        namespace groups{
            cpGroup explosive = 1;
        }
        
    }
    
}
