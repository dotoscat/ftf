#include <string>
#include <iostream>
#include "game.hpp"

fff::_game::_game(){
    
    realwindow.Create(sf::VideoMode(640, 480), "Free For Fall");
    clearcolor = sf::Color::White;
    lostfocus = false;
    
    currentscene = &mainscene;
    
    vm = luaL_newstate();
}

fff::_game::~_game(){

    std::map<std::string, sf::Texture *>::iterator atexture;
    for(atexture = textures.begin(); atexture != textures.end(); atexture++){
        delete atexture->second;
    }
    
    std::map<std::string, sf::SoundBuffer *>::iterator asoundbuffer;
    for(asoundbuffer = soundbuffers.begin(); asoundbuffer != soundbuffers.end(); asoundbuffer++){
        delete asoundbuffer->second;
    }
    
    std::map<std::string, sf::Font *>::iterator afont;
    for(afont = fonts.begin(); afont != fonts.end(); afont++){
        delete afont->second;
    }

    lua_close(vm);

}

void fff::_game::loadResources(){

    if (luaL_dofile(vm, "code/fff.lua")){
        std::cout << lua_tostring(vm, -1) << std::endl;
        exit(EXIT_FAILURE);
    }
    
    lua_getglobal(vm, "fonts");
    lua_pushnil(vm);
    while(lua_next(vm, -2)){
        fonts[lua_tostring(vm, -2)] = new sf::Font();
        std::string game("game/");
        std::string file(lua_tostring(vm, -1));
        if (!fonts[lua_tostring(vm, -2)]->LoadFromFile( game+file )){
            std::cout << "Error loding font: " << lua_tostring(vm, -1) << std::endl;;}
        lua_pop(vm, 1);//next
    }
    lua_pop(vm, 1);//fonts
    
}

void fff::_game::Run(){
    sf::Event event;
    while(realwindow.IsOpened()){
        
        while(realwindow.PollEvent(event)){
            switch(event.Type){
                case sf::Event::Closed:
                    realwindow.Close();
                break;
                case sf::Event::KeyPressed:
                    if (event.Key.Code == sf::Keyboard::Escape){
                        realwindow.Close();
                    }
                break;
                case sf::Event::LostFocus:
                    lostfocus = true;
                break;
                case sf::Event::GainedFocus:
                    lostfocus = false;
                break;
            }
            if (currentscene != NULL){
                currentscene->Event(event);
            }
        }
        
        if (lostfocus){
            realwindow.Display();
            continue;
        }
        
        realwindow.Clear(clearcolor);
        if (currentscene != NULL){
            currentscene->Run(realwindow);
        }
        realwindow.Display();
        
    }
}

fff::_game fff::game;
