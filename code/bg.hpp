#ifndef _bg_
#define _bg_

#include <SFML/Graphics.hpp>

namespace fff{
    
    class bg{
        
        sf::Sprite sprites[4];
        float ratioy;
        float velx;
        
        public:
            bg();
            void loadResources();
            void setVelX(float);
            void setRatioY(float);
            void Run(sf::RenderTarget &, sf::Uint32, float);
        
        protected:
            void setPositionX(float);
            void setPositionY(float);
        
    };
    
}

#endif
