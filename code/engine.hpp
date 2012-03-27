#infdef _engine_
#define _engine_

#include <chipmunk/chipmunk.h>
#include "scene.hpp"

namespace fff{
    
    class engine: public fff::scene{
        cpSpace *space;
        
        engine();
        ~engine();
        
    };
    
}

#endif
