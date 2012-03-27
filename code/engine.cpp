#include <iostream>
#include <cstdio>
#include "engine.hpp"
#include "game.hpp"

fff::engine::engine(){
    space = cpSpaceNew();
    cpSpaceSetGravity(space, (cpVect){0.f, 9.8f});
    cpSpaceAddBody(space, kitty.body);
    shapefloor = cpSegmentShapeNew(cpSpaceGetStaticBody(space), (cpVect){0.f, 4.f}, (cpVect){640.f, 4.f}, 4.f);
    cpSpaceAddShape(space, shapefloor);
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
}

fff::engine::~engine(){
    cpShapeFree(shapefloor);
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
}

void fff::engine::loadResources(){
    floor.SetTexture(*game.textures["floor"]);
    kitty.sprite.SetTexture(*game.textures["kitty"]);
    kitty.Update();
}

void fff::engine::Event(sf::Event &event){
}

void fff::engine::Run(sf::RenderTarget &rendertarget){
    sf::Uint32 currenttime = game.realwindow.GetFrameTime();
    
    char buffer[8] = {0};
    
    snprintf(buffer, 8, "%g", kitty.getVerticalSpeed() );
    speed.SetString(buffer);
    
    snprintf(buffer, 8, "%g", PIXELSTOMETERS(-kitty.getHeight()) );
    height.SetString(buffer);
    
    cpSpaceStep(space, currenttime/1000.f);
    time += currenttime;
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
    //
}
