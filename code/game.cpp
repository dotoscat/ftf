#include <string>
#include <cstdlib>
#include <iostream>
#include "game.hpp"

fff::_game::_game(){
    
    realwindow.Create(sf::VideoMode(640, 480), "Free For Fall", sf::Style::Titlebar | sf::Style::Close);
    realwindow.SetFramerateLimit(120);
    realwindow.EnableKeyRepeat(false);
    clearcolor = sf::Color(135, 206, 255);
    lostfocus = false;
    soundexplosion.SetAttenuation(0.001);
    
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
    
    std::map<std::string, sf::Music *>::iterator amusic;
    for(amusic = musics.begin(); amusic != musics.end(); amusic++){
        delete amusic->second;
    }
    
    lua_close(vm);

}

void fff::_game::loadResources(){

    if (luaL_dofile(vm, "code/fff.lua")){
        std::cout << lua_tostring(vm, -1) << std::endl;
        exit(EXIT_FAILURE);
    }
    
    std::string game("game/");
    std::string file;
    
    //load textures
    lua_getglobal(vm, "textures");
    lua_pushnil(vm);
    while(lua_next(vm, -2)){
        textures[lua_tostring(vm, -2)] = new sf::Texture();
        file = lua_tostring(vm, -1);
        if (!textures[lua_tostring(vm, -2)]->LoadFromFile( game+file )){
            std::cout << "Error loding textures: " << file << std::endl;}

        lua_pop(vm, 1);//next
    }
    lua_pop(vm, 1);//textures
    //
    
    //load fonts
    lua_getglobal(vm, "fonts");
    lua_pushnil(vm);
    while(lua_next(vm, -2)){
        fonts[lua_tostring(vm, -2)] = new sf::Font();
        file = lua_tostring(vm, -1);
        if (!fonts[lua_tostring(vm, -2)]->LoadFromFile( game+file )){
            std::cout << "Error loding font: " << file << std::endl;}
        lua_pop(vm, 1);//next
    }
    lua_pop(vm, 1);//fonts
    //
    
    //load sounds
    lua_getglobal(vm, "sounds");
    lua_pushnil(vm);
    while(lua_next(vm, -2)){
        soundbuffers[lua_tostring(vm, -2)] = new sf::SoundBuffer();
        file = lua_tostring(vm, -1);
        if (!soundbuffers[lua_tostring(vm, -2)]->LoadFromFile( game+file )){
            std::cout << "Error loding sound: " << file << std::endl;}
        lua_pop(vm, 1);//next
    }
    lua_pop(vm, 1);//soundbuffers
    //
    
    //load musics
    lua_getglobal(vm, "musics");
    lua_pushnil(vm);
    while(lua_next(vm, -2)){
        musics[lua_tostring(vm, -2)] = new sf::Music();
        file = lua_tostring(vm, -1);
        if (!musics[lua_tostring(vm, -2)]->OpenFromFile( game+file )){
            std::cout << "Error loding music: " << file << std::endl;}
        lua_pop(vm, 1);//next
    }
    lua_pop(vm, 1);//musics
    //
    
    musics["theme"]->SetLoop(true);
    crash.SetBuffer(*soundbuffers["crash"]);
    crash.SetRelativeToListener(true);
    mainscene.loadResources();
    engine.loadResources();
    
}

void fff::_game::startEngine(){
    currentscene = &engine;
    engine.Reset();
}

void fff::_game::returnToMainScene(){
    currentscene = &mainscene;
    this->stopTheme();
}

void fff::_game::continueEngine(){
    engine.Continue();
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

void fff::_game::playExplosion(sf::SoundBuffer *soundbuffer, sf::Vector2f position){
    soundexplosion.Stop();
    soundexplosion.SetPosition( sf::Vector3f(position.x, position.y, 0) );
    soundexplosion.SetBuffer( *soundbuffer );
    soundexplosion.SetPitch( 1.f - (rand()%3) / 10.f );
    soundexplosion.Play();
}

void fff::_game::startTheme(){
    if (musics["theme"]->GetStatus() == sf::SoundSource::Playing){
        return;}
    musics["theme"]->Play();
}

void fff::_game::stopTheme(){
    musics["theme"]->Stop();
}

void fff::_game::pauseTheme(){
    musics["theme"]->Pause();
}

fff::_game fff::game;
