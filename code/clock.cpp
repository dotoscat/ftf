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
