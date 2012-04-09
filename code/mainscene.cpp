#include "game.hpp"
#include "mainscene.hpp"

fff::mainscene::mainscene(){
    title.SetString("Free To Fall");
    title.SetColor(sf::Color::White);
    title.SetPosition(120, 64);
    instruction.SetString("Press Return key");
    instruction.SetColor(sf::Color::White);
    instruction.SetPosition(120, 120);
}

void fff::mainscene::loadResources(){
    title.SetFont(*game.fonts["baroque"]);
    instruction.SetFont(*game.fonts["baroque"]);
}

void fff::mainscene::Event(sf::Event &event){
    if (event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Keyboard::Return){
        game.startEngine();
    }
}

void fff::mainscene::Run(sf::RenderTarget &rendertarget){
    rendertarget.Draw(title);
    rendertarget.Draw(instruction);
}
