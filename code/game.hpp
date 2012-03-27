#ifndef _game_
#define _game_

#include <string>
#include <map>
#include <lua5.1/lua.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "scene.hpp"
#include "mainscene.hpp"
#include "engine.hpp"

namespace fff{

    struct _game{
        
        lua_State *vm;
        
        sf::Color clearcolor;
        
        bool lostfocus;
        
        sf::RenderWindow realwindow;
        sf::RenderTexture window;
        std::map<std::string, sf::Texture *> textures;
        std::map<std::string, sf::SoundBuffer *> soundbuffers;
        std::map<std::string, sf::Font *> fonts;
        
        fff::mainscene mainscene;
        fff::engine engine;
        fff::scene *currentscene;
        
        _game();
        ~_game();
        void loadResources();
        void Run();
        
    };

    extern fff::_game game;

}

#endif
