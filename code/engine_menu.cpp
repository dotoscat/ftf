#include "engine_menu.hpp"
#include "game.hpp"

fff::engine_menu::engine_menu(){
    bg = sf::Shape::Rectangle(0, 0, 640, 480, sf::Color(0, 0, 0, 128));
    iselection = 0;
    selection[0].SetString("Continue");
    selection[0].SetColor(sf::Color(200, 200, 255));
    selection[0].SetPosition(160, 120);
    selection[1].SetString("Exit");
    selection[1].SetPosition(160, 200);
}

void fff::engine_menu::Reset(){
    iselection = 0;
    selection[0].SetColor(sf::Color(200, 200, 255));
    selection[1].SetColor(sf::Color::White);
}

void fff::engine_menu::loadResources(){
    selection[0].SetFont(*game.fonts["baroque"]);
    selection[1].SetFont(*game.fonts["baroque"]);
}

void fff::engine_menu::Event(sf::Event &event){
    sf::Color selected(200, 200, 255);
    if (event.Type == sf::Event::KeyPressed){
        if (event.Key.Code == sf::Keyboard::Up && iselection > 0){
            selection[1].SetColor(sf::Color::White);
            iselection = 0;
             selection[0].SetColor(selected);
        }
        else if (event.Key.Code == sf::Keyboard::Down && iselection < 1){
            selection[0].SetColor(sf::Color::White);
            iselection = 1;
             selection[1].SetColor(selected);
        }
        else if (event.Key.Code == sf::Keyboard::Return){
            switch (iselection){
                case 0://continue
                    game.continueEngine();
                break;
                case 1://exit
                    game.returnToMainScene();
                break;
            }
        }
    }
}

void fff::engine_menu::Run(sf::RenderTarget &rendertarget){
    rendertarget.Draw(bg);
    rendertarget.Draw(selection[0]);
    rendertarget.Draw(selection[1]);
}
