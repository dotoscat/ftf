#include "game.hpp"

fff::_game::_game(){
    
    realwindow.Create(sf::VideoMode(640, 480), "Free For Fall");
    clearcolor = sf::Color::White;
    lostfocus = false;
    
}

fff::_game::~_game(){

    for(int i = 0; i < textures.size(); i += 1){
        delete textures[i];
    }
    
    for(int i = 0; i < soundbuffers.size(); i += 1){
        delete soundbuffers[i];
    }
    
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
