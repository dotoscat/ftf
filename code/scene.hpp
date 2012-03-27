#infdef _scene_
#define _scene_

#include <SFML/Graphics.hpp>

namespace fff{
    
    class scene{
        virtual void Run(sf::RenderTarget &) = 0;
    };
    
}

#endif
