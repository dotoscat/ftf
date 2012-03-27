#include "game.hpp"

fff::_game::~_game(){

    for(int i = 0; i < textures.size(); i += 1){
        delete textures[i];
    }
    
    for(int i = 0; i < soundbuffers.size(); i += 1){
        delete soundbuffers[i];
    }
    
}

fff::_game fff::game;
