#ifndef _game_
#define _game_

#include <string>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "scene.hpp"

namespace fff{

    struct _game{
        
        sf::Color clearcolor;
        
        bool lostfocus;
        
        sf::RenderWindow realwindow;
        sf::RenderTexture window;
        std::map<std::string, sf::Texture *> textures;
        std::map<std::string, sf::SoundBuffer *> soundbuffers;
        std::map<std::string, sf::Font *> fonts;
        
        fff::scene *currentscene;
        
        _game();
        ~_game();
        void LoadResources();
        void Run();
        
    };

    extern fff::_game game;

}

#endif
