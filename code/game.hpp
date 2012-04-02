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

#define KMH_TO_PXS(x) x*1000.f/3600.f*100.f  //x*1000.f/60.f/60.f*100.f
#define PXS_TO_KMH(x) x/100.f*3600.f/1000.f  //x/100.f*60.f*60.f/1000.f

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
        
        sf::Sound soundexplosion;
        
        fff::mainscene mainscene;
        fff::engine engine;
        fff::scene *currentscene;
        
        _game();
        ~_game();
        void loadResources();
        void startEngine();
        void returnToMainScene();
        void continueEngine();
        void Run();
        void playExplosion(sf::SoundBuffer *, sf::Vector2f);
        
    };

    extern fff::_game game;

}

#endif
