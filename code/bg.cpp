#include <iostream>
#include <cmath>
#include "bg.hpp"
#include "game.hpp"

fff::bg::bg(){
    ratioy = 1.f;
    this->setPositionY(0.f);
    this->setVelX(-32.f);
}

void fff::bg::loadResources(){
    for(int i = 0; i < 4; i += 1){
        sprites[i].SetTexture(*game.textures["bg"]);
    }
}

void fff::bg::setVelX(float velx){
    this->velx = velx;
    if (velx > 0){
        this->setPositionX(-640.f);
    }else{
        this->setPositionX(0.f);
    }
}

void fff::bg::setRatioY(float ratioy){
    this->ratioy = ratioy;
}

void fff::bg::Run(sf::RenderTarget &rendertarget, sf::Uint32 time, float height){
    float ftime = time/1000.f;
    height = fmod(height*ratioy, 480.f);
    this->setPositionY(-height);
    sf::Vector2f pos = sprites[0].GetPosition();
    //std::cout << "pos.x: " << pos.x << std::endl;
    if (velx > 0.f && pos.x > 0.f){
        this->setPositionX(-640.f);
    }else if (velx < 0.f && pos.x < -640.f){
        this->setPositionX(0.f);
    }
    rendertarget.SetView( rendertarget.GetDefaultView() );
    for(int i = 0; i < 4; i += 1){
        sprites[i].Move(ftime * velx, 0.f);
        rendertarget.Draw(sprites[i]);
    }
}

void fff::bg::setPositionX(float x){
    sprites[0].SetX(x);
    sprites[1].SetX(x+640.f);
    sprites[2].SetX(x);
    sprites[3].SetX(x+640.f);
}

void fff::bg::setPositionY(float y){
    sprites[0].SetY(y);
    sprites[1].SetY(y);
    sprites[2].SetY(y-480.f);
    sprites[3].SetY(y-480.f);
}
