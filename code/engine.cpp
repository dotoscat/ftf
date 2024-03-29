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

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cfloat>
#include <SFML/Audio.hpp>
#include "engine.hpp"
#include "game.hpp"
#include "collisions.hpp"
#include "save.hpp"

using namespace fff::collisions;

fff::engine::engine(){
    space = cpSpaceNew();
    cpSpaceSetIterations(space, 100);
    cpSpaceSetGravity(space, (cpVect){0.f, METERSTOPIXELS(10.f)});
        
    cpSpaceAddCollisionHandler(space, types::explosive, types::kitty, fff::explosive::Begin, NULL, NULL, NULL, this);
    cpSpaceAddCollisionHandler(space, types::kitty, types::leftlimit, NULL, fff::engine::preSolve_kitty_leftlimit, NULL, NULL, this);
    cpSpaceAddCollisionHandler(space, types::kitty, types::rightlimit, NULL, fff::engine::preSolve_kitty_rightlimit, NULL, NULL, this);
    
    cpSpaceAddBody(space, kitty.body);
    
    shapeleftlimit = cpSegmentShapeNew(cpSpaceGetStaticBody(space), (cpVect){-4.f, 0.f}, (cpVect){-4.f, -FLT_MAX}, 4.f);
    cpShapeSetCollisionType(shapeleftlimit, types::leftlimit);
    cpShapeSetSensor(shapeleftlimit, cpTrue);
    cpSpaceAddShape(space, shapeleftlimit);
    
    shaperightlimit = cpSegmentShapeNew(cpSpaceGetStaticBody(space), (cpVect){640+4.f, 0.f}, (cpVect){640+4.f, -FLT_MAX}, 4.f);
    cpShapeSetCollisionType(shaperightlimit, types::rightlimit);
    cpShapeSetSensor(shaperightlimit, cpTrue);
    cpSpaceAddShape(space, shaperightlimit);
    
    floor.SetPosition(0, 0);
    camera.SetCenter(320, 240);
    camera.SetSize(640, 480);
    kitty.setPosition(320, -2500);
    speed.SetColor(sf::Color::Black);
    km_h.SetString("km/h");
    km_h.SetColor(sf::Color::Black);
    km_h.SetX(200);
    height.SetColor(sf::Color::Black);
    height.SetPosition(0, 30);
    meters.SetString("meters");
    meters.SetColor(sf::Color::Black);
    meters.SetPosition(200, 30);
    ascending.SetString("ascending");
    ascending.SetColor(sf::Color::Black);
    ascending.SetX(300);
    falling.SetString("falling");
    falling.SetColor(sf::Color::Black);
    falling.SetX(300);
    clock.SetColor(sf::Color::Black);
    clock.SetPosition(300, 32);
    
    flash = sf::Shape::Rectangle(0, 0, 640, 480, sf::Color::White);
    txtgameover.SetString("GAME OVER\nPress 'r' to try again");
    txtgameover.SetColor(sf::Color::Black);
    txtgameover.SetPosition(77, 77);
    
}

fff::engine::~engine(){
    cpShapeFree(shapeleftlimit);
    cpShapeFree(shaperightlimit);
    cpSpaceFree(space);
}

void fff::engine::Reset(){
    lua_getglobal(game.vm, "engine");
    lua_getfield(game.vm, -1, "startpos");
    kitty.setPosition(320, METERSTOPIXELS( lua_tonumber(game.vm, -1) ));
    kitty.burstinflames = false;
    lua_pop(game.vm, 1);//startpos
    lua_getfield(game.vm, -1, "startvel");
    kitty.setInitialFallingSpeed(lua_tonumber(game.vm, -1));
    lua_pop(game.vm, 1);//startvel
    lua_pop(game.vm, 1);//engine
    engineclock.Reset();
    status = running;
    for (int i = 0; i < MAXEXPLOSIVES; i += 1){
        if (!explosive[i].exists){
            continue;
        }
        explosive[i].exists = false;
        if ( cpSpaceContainsShape(space, explosive[i].shape) ){
            cpSpaceRemoveShape(space, explosive[i].shape);
        }
    }
    kitty.Reset();//reset kitty impulses
    emitter.Reset();
    menu.Reset();
}

void fff::engine::loadResources(){
    kitty.Configure();
    cpSpaceAddShape(space, kitty.shape);
    floor.SetTexture(*game.textures["floor"]);
    kitty.sprite.SetTexture(*game.textures["kitty"]);
    kitty.Update();
    for (int i = 0; i < MAXEXPLOSIVES; i += 1){
        explosive[i].prepareShape(space);
        explosive[i].loadResources();
    }
    bg.setRatioY(0.01f);
    bg.loadResources();
    emitter.setParticles(12);
    emitter.setParticlesPerSec(3);
    emitter.setLifespan(4000);
    emitter.loadResources();
    menu.loadResources();
    txtgameover.SetFont(*game.fonts["baroque"]);
}

void fff::engine::Event(sf::Event &event){
    switch (status){
        case running:
            if (event.Type == sf::Event::KeyPressed){
                switch(event.Key.Code){
                    case sf::Keyboard::Left:
                        kitty.moveLeft();
                    break;
                    case sf::Keyboard::Right:
                        kitty.moveRight();
                    break;
                    case sf::Keyboard::Return:
                        status = pause;
                        game.pauseTheme();
                    break;
                }
            }else if(event.Type == sf::Event::KeyReleased){
                switch(event.Key.Code){
                    case sf::Keyboard::Left:
                        kitty.stopMovingLeft();
                    break;
                    case sf::Keyboard::Right:
                        kitty.stopMovingRight();
                    break;
                }
            }
        break;
        case pause:
            if (event.Type == sf::Event::KeyPressed){
                switch(event.Key.Code){
                    case sf::Keyboard::Left:
                        kitty.moveLeft();
                    break;
                    case sf::Keyboard::Right:
                        kitty.moveRight();
                    break;
                }
            }else if(event.Type == sf::Event::KeyReleased){
                switch(event.Key.Code){
                    case sf::Keyboard::Left:
                        kitty.stopMovingLeft();
                    break;
                    case sf::Keyboard::Right:
                        kitty.stopMovingRight();
                    break;
                }
            }
            menu.Event(event);
        break;
        case gameover:
            if (game.crash.GetStatus() == sf::SoundSource::Playing){
                break;
            }
            if (event.Type == sf::Event::KeyReleased && event.Key.Code == sf::Keyboard::R){
                game.startEngine();
            }
        break;
    }
    
}

void fff::engine::Run(sf::RenderTarget &rendertarget){
    sf::FloatRect camerarect;
    sf::Vector3f listenerpos;
    sf::Vector2f camerapos;
    char buffer[13] = {0};
    sf::Uint32 currenttime = game.realwindow.GetFrameTime();
    switch(status){
        case running:
            if (kitty.getHeight() > -32.f){
                game.stopTheme();
                game.crash.Play();
                status = gameover;
                time = 0;//Will be used in gameover status
                emitter.setPos(kitty.getX(), -32);
                break;
            }
            
            cpSpaceStep(space, currenttime/1000.f);
                                                
            //avoid "tunneling"
            cpSegmentQueryInfo info;
            for (int i = 0; i < MAXEXPLOSIVES; i += 1){
                if ( explosive[i].isExploding() || !cpShapeSegmentQuery(explosive[i].shape, kitty.lastpos, kitty.getCurrentPos(), &info) ){
                    continue;}
                kitty.applyImpulse(explosive[i].impulse);
                explosive[i].setExploding();
                game.playExplosion(explosive[i].soundbuffer, explosive[i].sprite.GetPosition() );
                cpSpaceRemoveShape(space, explosive[i].shape);
                game.startTheme();
                break;
            }
            //---
                        
            snprintf(buffer, 13, "%g", fabs( kitty.getVerticalSpeed() ) );
            speed.SetString(buffer);
            
            snprintf(buffer, 13, "%g", PIXELSTOMETERS( fabsf( kitty.getHeight() ) ) );
            height.SetString(buffer);
            
            time += currenttime;
            engineclock.Update(currenttime);
            clock.SetString( engineclock.getString() );
            
            kitty.Update();
            
            if ( this->generateExplosive() ){
                
                if (kitty.isFalling() && this->generateExplosiveWhileFalling() ){
                    int i = this->createExplosive();
                    if (i < MAXEXPLOSIVES){
                        float x = 0.f;
                        while(x <= 80 || x > 580){
                            x = rand() % 580;}
                        float predictiony = kitty.forecastYPositionTo( 1.f+(rand()%2) ) ;
                        explosive[i].setPosition( x, predictiony );
                        cpSpaceAddShape(space, explosive[i].shape);
                    }
                }
                else if (kitty.isAscending() && this->generateExplosiveWhileAscending() ){
                    int i = this->createExplosive();
                    if (i < MAXEXPLOSIVES){
                        float x = 0.f;
                        while(x <= 80 || x > 580){
                            x = rand() % 580;}
                        float predictiony = kitty.forecastYPositionTo( 1.f ) ;
                        //std::cout << "Prediction climbing: " << predictiony << "; kitty height: " << kitty.getHeight() << std::endl;
                        explosive[i].setPosition( x, predictiony );
                        cpSpaceAddShape(space, explosive[i].shape);
                    }
                }
                
                time = 0;
            }
            
            //std::cout << "lua gettop: " << lua_gettop(game.vm) << std::endl;
            
            camerapos = camera.GetCenter();
            if (kitty.getHeight() < -240+32){
                camerapos.y = kitty.getHeight();
                
            }
            else{
                camerapos.y = -240+32;
            }
            
            bg.Run(rendertarget, currenttime, kitty.getHeight());
            
            camera.SetCenter(camerapos);
            
            listenerpos = sf::Listener::GetPosition();
            listenerpos.y = camerapos.y;
            listenerpos.x = camerapos.x;
            sf::Listener::SetPosition(listenerpos);
            
            rendertarget.SetView(camera);
            camerarect.Left = camerapos.x-320;
            camerarect.Top = camerapos.y-240;
            camerarect.Width = 640;
            camerarect.Height = 480;

            if ( kitty.burstInFlames() ){
                rendertarget.Draw( kitty.getCurrentFrame() );
            }
            rendertarget.Draw(kitty.sprite);
            for (int i = 0; i < MAXEXPLOSIVES; i += 1){
                if (!explosive[i].exists){
                    continue;}
                
                if (!explosive[i].isExploding()){
                    
                    explosive[i].acumlifespan += currenttime;
                    if (explosive[i].isOver() ){
                        explosive[i].exists = false;
                        cpSpaceRemoveShape(space, explosive[i].shape);
                        continue;
                    }
                    
                    if (explosive[i].sprite.GetPosition().y < camerarect.Top){
                        explosive[i].setSignalAtTop();
                    }else{
                        explosive[i].setSignalAtBottom();
                    }
                    explosive[i].Update( camerapos.y );
                    rendertarget.Draw(explosive[i].sprite);
                    continue;
                }
                //if is exploding....
                
                explosive[i].timeexploding += currenttime;
                
                if (explosive[i].isExploded() ){
                    explosive[i].exists = false;
                    continue;
                }
                
                rendertarget.Draw(explosive[i].explosion);
                
            }
            rendertarget.Draw(floor);
            //draw hud
            rendertarget.SetView( rendertarget.GetDefaultView() );
            this->drawHUD(rendertarget, camerarect);
            //
        break;
        case pause:
            bg.Run(rendertarget, currenttime, kitty.getHeight());
            rendertarget.SetView( rendertarget.GetDefaultView() );
            this->drawHUD(rendertarget, camerarect);
            menu.Run(rendertarget);
            //
        break;
        case gameover:
            time += currenttime;
            bg.Run(rendertarget, currenttime, kitty.getHeight());
            rendertarget.SetView(camera);
            rendertarget.Draw(floor);
            emitter.Process(rendertarget, currenttime);
            rendertarget.SetView( rendertarget.GetDefaultView() );
            if (time < 77){
                rendertarget.Draw(flash);
            }
            if (game.crash.GetStatus() != sf::SoundSource::Stopped){
                break;
            }
            rendertarget.Draw(txtgameover);
            //
        break;
    }
}

void fff::engine::Continue(){
    if (game.musics["theme"]->GetStatus() == sf::SoundSource::Paused){
        game.musics["theme"]->Play();
    }
    status = running;
}

void fff::engine::saveScore(){
    save.saveNewScore( PIXELSTOMETERS( fabsf( kitty.getHeight() ) ), engineclock);
}

int fff::engine::createExplosive(){
    
    int i = 0;
    
    for(; i < MAXEXPLOSIVES; i += 1){
        if (explosive[i].exists){
            continue;}
        
        lua_getglobal(game.vm, "explosives");
        lua_pushnil(game.vm);
        while( lua_next(game.vm, -2) ){
            //key
            //The top is a table
            lua_getfield(game.vm, -1, "appareance");
            if ( (rand()%101) <= lua_tonumber(game.vm, -1) ){
                lua_pop(game.vm, 1);//appareance
                explosive[i].Configure(lua_tostring(game.vm, -2));//-1 is table, -2 key
                lua_pop(game.vm, 3);//table(next), key and explosives
                return i;
            }
            lua_pop(game.vm, 2);//apparance and next
        }
        lua_pop(game.vm, 1);//explosives
        
    }
    return MAXEXPLOSIVES;//no return a explosive index
}

bool fff::engine::generateExplosive(){
    lua_getglobal(game.vm, "engine");
    lua_getfield(game.vm, -1, "explosiveeach");
    bool generate = false;
    if ( time > lua_tonumber(game.vm, -1)){
        generate = true;}
    lua_pop(game.vm, 2);//engine and explosiveeach
    return generate;
}

bool fff::engine::generateExplosiveWhileFalling(){
    bool generate = false;
    lua_getglobal(game.vm, "engine");
    lua_getfield(game.vm, -1, "explosivefalling");
    if ( (rand() % 101) <= lua_tonumber(game.vm, -1)){
        generate = true;}
    lua_pop(game.vm, 2);//explosivefalling and engine
    return generate;
}

bool fff::engine::generateExplosiveWhileAscending(){
    bool generate = false;
    lua_getglobal(game.vm, "engine");
    lua_getfield(game.vm, -1, "explosiveascending");
    if ( (rand() % 101) <= lua_tonumber(game.vm, -1)){
        generate = true;}
    lua_pop(game.vm, 2);//explosiveascending and engine
    return generate;
}

void fff::engine::drawHUD(sf::RenderTarget &rendertarget, sf::FloatRect &camerarect){
    for(int i = 0; i < MAXEXPLOSIVES; i += 1){
        if (!explosive[i].exists){
            continue;}
        if ( !camerarect.Contains(explosive[i].sprite.GetPosition() ) && !explosive[i].isExploding() ){
            rendertarget.Draw(explosive[i].signal);
            rendertarget.Draw(explosive[i].meters);
        }
    }
    rendertarget.Draw(speed);
    rendertarget.Draw(km_h);
    rendertarget.Draw(height);
    rendertarget.Draw(meters);
    if (kitty.isFalling()){
        rendertarget.Draw(falling);
    }else{
        rendertarget.Draw(ascending);
    }
    rendertarget.Draw(clock);
}

float fff::engine::getHeight(){
    return PIXELSTOMETERS( fabsf( kitty.getHeight() ) );
}

fff::clock fff::engine::getClock(){
    return engineclock;
}

int fff::engine::preSolve_kitty_leftlimit(cpArbiter *arb, cpSpace *space, void *data){
    CP_ARBITER_GET_BODIES(arb, kittybody, spacebody);
    fff::kitty *kitty = static_cast<fff::kitty *>( cpBodyGetUserData(kittybody) );
    cpVect vel = cpBodyGetVel(kittybody);
    if (vel.x < 0.f){
        kitty->stopMovingLeft();
    }
    return 0;
}

int fff::engine::preSolve_kitty_rightlimit(cpArbiter *arb, cpSpace *space, void *data){
    CP_ARBITER_GET_BODIES(arb, kittybody, spacebody);
    fff::kitty *kitty = static_cast<fff::kitty *>( cpBodyGetUserData(kittybody) );
    cpVect vel = cpBodyGetVel(kittybody);
    if (vel.x > 0.f){
        kitty->stopMovingRight();
    }
    return 0;
}
