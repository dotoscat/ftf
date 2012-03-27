#ifndef _game_
#define _game_

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace fff{

    struct _game{
        
        sf::RenderWindow realwindow;
        sf::RenderTexture window;
        std::vector<sf::Texture *> textures;
        std::vector<sf::SoundBuffer *> soundbuffers;
        
        ~_game();
        
    };

    extern fff::_game game;

}

#endif
