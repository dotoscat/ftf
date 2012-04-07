#include "particle.hpp"
#include "auxiliar.hpp"
#include "game.hpp"

void fff::emitter::particle::Create(sf::Uint32 lifespan, sf::Vector2f pos){
    exists = true;
    this->lifespan = lifespan;
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
    if (storetime > time){
        exists = false;
        return;
    }
    storetime += time;
    scale.x += 0.1f;
    scale.y += 0.1f;
    alpha -= 1.f;
    if (alpha < 0.f){
        alpha = 0.f;
    }
    sprite.SetScale(scale);
    sf::Color color = sprite.GetColor();
    color.a = alpha;
    sprite.SetColor(color);
    sprite.Move(1.f, 0.f);
}

fff::emitter::emitter(){
    particles = NULL;
    nparticles = 0;
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
        particles[i].sprite.SetTexture(*game.textures[""]);
        fff::SetOriginByLua(game.vm, particles[i].sprite, "smoke");
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
        if (particles[i].exists){
            continue;
        }
        particles[i].Update(time);
        rendertarget.Draw(particles[i].sprite);
    }
}
