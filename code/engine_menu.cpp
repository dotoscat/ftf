#include "engine_menu"

fff::engine_menu::engine_menu(){
    bg = sf::Shape::Rectangle(0, 0, 640, 480, sf::Color(0, 0, 0, 128));
    iselection = 0;
}

void fff::engine_menu::Event(sf::Event &event){
}

void fff:engine_menu::Run(sf::RenderTarget &rendertarget){
    rendertarget.Draw(bg);
    rendertarget.Draw(selection[0]);
    rendertarget.Draw(selection[1]);
}
