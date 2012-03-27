#ifndef _game_
#define _game_

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "scene.hpp"

namespace fff{

    struct _game{
        
        sf::Color clearcolor;
        
        bool lostfocus;
        
        sf::RenderWindow realwindow;
        sf::RenderTexture window;
        std::vector<sf::Texture *> textures;
        std::vector<sf::SoundBuffer *> soundbuffers;
        
        fff::scene *currentscene;
        
        _game();
        ~_game();
        void Run();
        
    };

    extern fff::_game game;

}

#endif
