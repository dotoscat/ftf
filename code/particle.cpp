#include <iostream>
#include "particle.hpp"
#include "auxiliar.hpp"
#include "game.hpp"

fff::emitter::particle::particle(){
    exists = false;
}

void fff::emitter::particle::loadResources(){
    sprite.SetTexture(*game.textures["smoke"]);
    fff::SetOriginByLua(game.vm, sprite, "smoke");
}

void fff::emitter::particle::Create(sf::Uint32 lifespan, sf::Vector2f pos){
    exists = true;
    this->lifespan = lifespan;
    storetime = 0;
    scale.x = 1.f;
    scale.y = 1.f;
    alpha = 255.f;
    sprite.SetPosition(pos);
    sprite.SetScale(scale);
    sf::Color color = sprite.GetColor();
    color.a = alpha;
    sprite.SetColor(color);
}

void fff::emitter::particle::Update(sf::Uint32 time){
    if (storetime > lifespan){
        exists = false;
        return;
    }
    storetime += time;
    scale.x += 0.01f;
    scale.y += 0.01f;
    alpha -= 1.f;
    if (alpha < 0.f){
        alpha = 0.f;
    }
    if (alpha > 255.f){
        alpha = 255.f;
    }
    sprite.SetScale(scale);
    sf::Color color = sprite.GetColor();
    color.a = alpha;
    sprite.SetColor(color);
    sprite.Move(0.f, -128.f*(time/1000.f));
    sf::Vector2f pos = sprite.GetPosition();
}

fff::emitter::emitter(){
    particles = NULL;
    nparticles = 0;
    storetime = 0;
}

fff::emitter::~emitter(){
    if (particles != NULL){
        delete [] particles;
    }
}

void fff::emitter::setParticles(int n){
    if (particles != NULL){
        delete [] particles;
    }
    particles = new particle[n];
    nparticles = n;
}

void fff::emitter::loadResources(){
    if (particles == NULL){
        return;
    }
    for (int i = 0; i < nparticles; i += 1){
        particles[i].loadResources();
    }
}

void fff::emitter::setParticlesPerSec(int n){
    parpersec = 1000 / n;//ms
}

void fff::emitter::setPos(float x, float y){
    pos.x = x;
    pos.y = y;
}

void fff::emitter::setLifespan(int lifespan){
    this->lifespanparticle = lifespan;
}

void fff::emitter::Process(sf::RenderTarget &rendertarget, sf::Uint32 time){
    if (particles == NULL){
        return;}
    storetime += time;
    if (storetime > parpersec){
        for (int i = 0; i < nparticles; i += 1){
            if (particles[i].exists){
                continue;
            }
            particles[i].Create(lifespanparticle, pos);
            break;
        }
        storetime = 0;
    }
    for (int i = 0; i < nparticles; i += 1){
        if (!particles[i].exists){
            continue;
        }
        particles[i].Update(time);
        rendertarget.Draw(particles[i].sprite);
    }
}
