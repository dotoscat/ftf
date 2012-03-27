#include "game.hpp"
#include "mainscene.hpp"

fff::mainscene::mainscene(){
    title.SetString("Free For Fall");
    //title.SetFont(*game.fonts["baroque"]);
    title.SetColor(sf::Color::Black);
    title.SetPosition(120, 64);
    instruction.SetString("Press any key for start");
    //instruction.SetFont(*game.fonts["baroque"]);
    instruction.SetColor(sf::Color::Black);
    instruction.SetPosition(120, 120);
}

void fff::mainscene::Event(sf::Event &event){

}

void fff::mainscene::Run(sf::RenderTarget &rendertarget){
    rendertarget.Draw(title);
    rendertarget.Draw(instruction);
}
