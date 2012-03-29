#ifndef _explosive_
#define _explosive_

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <chipmunk/chipmunk.h>

namespace fff{
    
    struct explosive{
        
        bool exists;
        
        sf::Sprite sprite;
        sf::Sprite arrow;
        sf::Text meters;
        sf::SoundBuffer *soundbuffer;
        cpShape *shape;
        
        float impulse;
        
        explosive();
        ~explosive();
        void loadResources();
        void prepareShape(cpSpace *);
        void Configure(const char *);
        void setPosition(float, float);
        void setArrowAtBottom();
        void setArrowAtTop();
        void Update(float);
        
        static int Begin(cpArbiter *, cpSpace *, void *);
        static void postStep(cpSpace *, void *, void *);
        
    };
    
}

#endif
