#ifndef _explosive_
#define _explosive_

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <chipmunk/chipmunk.h>

namespace fff{
    
    struct explosive{
        
        enum _status{
            normal,
            exploding
        }status;
        
        sf::Uint32 timeexploding;
        sf::Uint32 lifespan;
        sf::Uint32 acumlifespan;
        
        bool exists;
        
        sf::Sprite explosion;
        sf::Sprite sprite;
        sf::Sprite signal;
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
        void setSignalAtBottom();
        void setSignalAtTop();
        void Update(float);
        void setExploding();
        bool isExploding();
        bool isExploded();
        bool isOver();
        
        static int Begin(cpArbiter *, cpSpace *, void *);
        static void postStep(cpSpace *, void *, void *);
        
    };
    
}

#endif
