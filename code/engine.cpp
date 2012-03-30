#include <iostream>
#include <cstdio>
#include <cfloat>
#include <SFML/Audio.hpp>
#include "engine.hpp"
#include "game.hpp"
#include "collisions.hpp"

fff::engine::engine(){
    space = cpSpaceNew();
    cpSpaceSetIterations(space, 100);
    cpSpaceSetGravity(space, (cpVect){0.f, METERSTOPIXELS(10.f)});
    
    using namespace fff::collisions;
    
    cpSpaceAddCollisionHandler(space, types::explosive, types::kitty, fff::explosive::Begin, NULL, NULL, NULL, this);
    
    cpSpaceAddBody(space, kitty.body);
    
    shapeleftlimit = cpSegmentShapeNew(cpSpaceGetStaticBody(space), (cpVect){-4.f, 0.f}, (cpVect){-4.f, -FLT_MAX}, 4.f);
    cpSpaceAddShape(space, shapeleftlimit);
    shaperightlimit = cpSegmentShapeNew(cpSpaceGetStaticBody(space), (cpVect){640+4.f, 0.f}, (cpVect){640+4.f, -FLT_MAX}, 4.f);
    cpSpaceAddShape(space, shaperightlimit);
    floor.SetPosition(0, 0);
    camera.SetCenter(320, 240);
    camera.SetSize(640, 480);
    kitty.setPosition(320, -2500);
    speed.SetColor(sf::Color::Black);
    km_h.SetString("km/h");
    km_h.SetColor(sf::Color::Black);
    km_h.SetX(120);
    height.SetColor(sf::Color::Black);
    height.SetPosition(0, 30);
    meters.SetString("meters");
    meters.SetColor(sf::Color::Black);
    meters.SetPosition(120, 30);
    clock.SetColor(sf::Color::Black);
    clock.SetPosition(300, 32);
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
    lua_pop(game.vm, 1);//startpos
    lua_getfield(game.vm, -1, "startvel");
    kitty.setInitialFallingSpeed(lua_tonumber(game.vm, -1));
    lua_pop(game.vm, 1);//startvel
    lua_pop(game.vm, 1);//engine
    engineclock.Reset();
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
}

void fff::engine::Event(sf::Event &event){
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
    
}

void fff::engine::Run(sf::RenderTarget &rendertarget){
    sf::Uint32 currenttime = game.realwindow.GetFrameTime();
    cpSpaceStep(space, currenttime/1000.f);
    
    char buffer[8] = {0};
    
    snprintf(buffer, 8, "%g", kitty.getVerticalSpeed() );
    speed.SetString(buffer);
    
    snprintf(buffer, 8, "%g", PIXELSTOMETERS(-kitty.getHeight()) );
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
                while(x <= 80 || x > 400){
                    x = rand() % 400;}
                explosive[i].setPosition( x, -(rand()%METERSTOPIXELS(250)) );
                cpSpaceAddShape(space, explosive[i].shape);
            }
        }
        else if (kitty.isClimbing() && this->generateExplosiveWhileClimbing() ){
        }
        
        time = 0;
    }
    
    //std::cout << "lua gettop: " << lua_gettop(game.vm) << std::endl;
    
    sf::Vector2f camerapos = camera.GetCenter();
    if (kitty.getHeight() < -240+32){
        camerapos.y = kitty.getHeight();
        
    }
    else{
        camerapos.y = -240+32;
    }
    camera.SetCenter(camerapos);
    
    sf::Vector3f listenerpos = sf::Listener::GetPosition();
    listenerpos.y = camerapos.y;
    listenerpos.x = camerapos.x;
    sf::Listener::SetPosition(listenerpos);
    
    rendertarget.SetView(camera);
    sf::FloatRect camerarect(camerapos.x-320, camerapos.y-240, 640, 480);
    rendertarget.Draw(kitty.sprite);
    for (int i = 0; i < MAXEXPLOSIVES; i += 1){
        if (!explosive[i].exists){
            continue;}
        if (explosive[i].sprite.GetPosition().y < camerarect.Top){
            explosive[i].setArrowAtTop();
        }else{
            explosive[i].setArrowAtBottom();
        }
        explosive[i].Update( camerapos.y );
        rendertarget.Draw(explosive[i].sprite);
    }
    rendertarget.Draw(floor);
    //draw hud
    rendertarget.SetView( rendertarget.GetDefaultView() );
    for(int i = 0; i < MAXEXPLOSIVES; i += 1){
        if (!explosive[i].exists){
            continue;}
        if ( !camerarect.Contains(explosive[i].sprite.GetPosition() ) ){
            rendertarget.Draw(explosive[i].arrow);
            rendertarget.Draw(explosive[i].meters);
        }
    }
    rendertarget.Draw(speed);
    rendertarget.Draw(km_h);
    rendertarget.Draw(height);
    rendertarget.Draw(meters);
    rendertarget.Draw(clock);
    //
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

bool fff::engine::generateExplosiveWhileClimbing(){
    bool generate = false;
    lua_getglobal(game.vm, "engine");
    lua_getfield(game.vm, -1, "explosiveclimbing");
    if ( (rand() % 101) <= lua_tonumber(game.vm, -1)){
        generate = true;}
    lua_pop(game.vm, 2);//explosiveclimbing and engine
    return generate;
}
