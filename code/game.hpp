//Copyright (C) 2012 Oscar Triano Garcia <teritriano@gmail.com>

//This file is part of Free To Fall.

//Free To Fall is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//Free To Fall is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with Free To Fall.  If not, see <http://www.gnu.org/licenses/>.

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
#include "clock.hpp"

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
        std::map<std::string, sf::Music *> musics;
        
        sf::Sound soundexplosion, crash;
        
        fff::mainscene mainscene;
        fff::engine engine;
        fff::scene *currentscene;
        
        float recordmeters;
        fff::clock recordclock;
        
        _game();
        ~_game();
        void loadResources();
        void startEngine();
        void returnToMainScene();
        void continueEngine();
        void Run();
        void playExplosion(sf::SoundBuffer *, sf::Vector2f);
        void startTheme();
        void stopTheme();
        void pauseTheme();
        
    };

    extern fff::_game game;

}

#endif
