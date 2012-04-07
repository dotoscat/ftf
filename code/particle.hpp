#ifndef _particle_
#define _particle_

#include <SFML/Graphics.hpp>

namespace fff{
    
    class emitter{
        
        class particle{
            float alpha;
            sf::Vector2f scale;
            sf::Uint32 lifespan;
            sf::Uint32 storetime;
            
            public:
                mutable bool exists;
                mutable sf::Sprite sprite;
            
            public:
                particle();
                void loadResources();
                void Create(sf::Uint32, sf::Vector2f);
                void Update(sf::Uint32);
                void Reset();
            
        };
        
        particle *particles;
        int nparticles;
        sf::Uint32 parpersec;
        sf::Uint32 storetime;
        sf::Vector2f pos;
        sf::Uint32 lifespanparticle;
        
        public:
            emitter();
            ~emitter();
            void setParticles(int);
            void loadResources();
            void setParticlesPerSec(int);
            void setPos(float, float);
            void setLifespan(int);
            void Process(sf::RenderTarget &, sf::Uint32);
            void Reset();
                    
    };
    
}

#endif
