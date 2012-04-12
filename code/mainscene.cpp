#include "game.hpp"
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

#include "mainscene.hpp"

fff::mainscene::mainscene(){
    title.SetString("Free To Fall");
    title.SetColor(sf::Color::Black);
    title.SetPosition(120, 64);
    instruction.SetString("Press Return key");
    instruction.SetCharacterSize(22);
    instruction.SetColor(sf::Color::Black);
    instruction.SetPosition(120, 120);
    
    record.SetPosition(120, 150);
    record.SetColor(sf::Color::Black);
    
    credits.SetString("2012 - Oscar Triano Garcia <teritriano@gmail.com>\nSEE README.txt \"CREDITS\" FOR DETAILS");
    credits.SetCharacterSize(14);
    credits.SetPosition(0, 480-50);
    credits.SetColor(sf::Color::Black);
    
}

void fff::mainscene::loadResources(){
    title.SetFont(*game.fonts["baroque"]);
    instruction.SetFont(*game.fonts["baroque"]);
    bg.loadResources();
}

void fff::mainscene::Event(sf::Event &event){
    if (event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Keyboard::Return){
        game.startEngine();
    }
}

void fff::mainscene::Run(sf::RenderTarget &rendertarget){
    bg.Run(rendertarget, 0, 0.f);
    rendertarget.Draw(title);
    rendertarget.Draw(instruction);
    rendertarget.Draw(record);
    rendertarget.Draw(credits);
}

void fff::mainscene::setRecord(char *txtrecord){
    record.SetString(txtrecord);
}
