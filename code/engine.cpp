#include <iostream>
#include <cstdio>
#include <cfloat>
#include "engine.hpp"
#include "game.hpp"

fff::engine::engine(){
    space = cpSpaceNew();
    cpSpaceSetGravity(space, (cpVect){0.f, 9.8f});
    cpSpaceAddBody(space, kitty.body);
    shapefloor = cpSegmentShapeNew(cpSpaceGetStaticBody(space), (cpVect){0.f, 4.f}, (cpVect){640.f, 4.f}, 4.f);
    cpSpaceAddShape(space, shapefloor);
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
    cpShapeFree(shapefloor);
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
    
    if (time >= 1000){
        // time <= 1 sec
        //generate events
        time = 0; 
    }
    kitty.Update();
    sf::Vector2f camerapos = camera.GetCenter();
    //std::cout << "Height: " << kitty.getHeight() << std::endl;
    //camerapos.y = kitty.getHeight();
    //camera.SetCenter(camerapos);
    if (kitty.getHeight() <= -240+32){
        camerapos.y = kitty.getHeight();
        camera.SetCenter(camerapos);
    }
    rendertarget.SetView(camera);
    rendertarget.Draw(kitty.sprite);
    rendertarget.Draw(floor);
    //draw hud
    rendertarget.SetView( rendertarget.GetDefaultView() );
    rendertarget.Draw(speed);
    rendertarget.Draw(km_h);
    rendertarget.Draw(height);
    rendertarget.Draw(meters);
    rendertarget.Draw(clock);
    //
}