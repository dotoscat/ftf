#ifndef _kitty_
#define _kitty_

#include <SFML/Graphics.hpp>
#include <chipmunk/chipmunk.h>

namespace fff{
    //free for fall body
    struct kitty{
        cpBody *body;
        sf::Sprite sprite;
        
        kitty();
        ~kitty();
        void setPosition(float, float);
        float getHeight();
        void Update();
         
    };
    
}

#endif
