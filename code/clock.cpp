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

#include "clock.hpp"

bool fff::clock::operator<(fff::clock &clock){
    if (this->hours < clock.hours && this->minutes < clock.minutes \
    && this->seconds < clock.seconds && this->ms < clock.ms){
        return true;
    }
    return false;
}

fff::clock::clock(const fff::clock &clock){
    this->ms = clock.ms;
    this->seconds = clock.seconds;
    this->minutes = clock.minutes;
    this->hours = clock.hours;
}

void fff::clock::Reset(){
    ms = 0;
    seconds = 0;
    minutes = 0;
    hours = 0;
}

void fff::clock::Update(sf::Uint32 time){
    ms += time;
    if (ms > 1000){
        ms = 0;
        seconds += 1;
    }
    if (seconds > 59){
        seconds = 0;
        minutes += 1;
    }
    if (minutes > 59){
        minutes = 0;
        hours += 1;
    }
}

char *fff::clock::getString(){
    snprintf(buffer, 12, "%02u:%02u:%02u:%02u", hours, minutes, seconds, ms);
    return buffer;
}
