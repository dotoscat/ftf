#include "clock.hpp"

void fff::clock::Reset(){
    ms = 0;
    secs = 0;
    min = 0;
    hours = 0;
}

void fff::clock::Update(sf::Uint32 time){
    ms += time;
    if (ms > 1000){
        ms = 0;
        secs += 1;
    }
    if (secs > 59){
        secs = 0;
        min += 1;
    }
    if (min > 59){
        min = 0;
        hours += 1;
    }
}

char *fff::clock::getString(){
    snprintf(buffer, 12, "%02u:%02u:%02u:%02u", hours, min, secs, ms);
    return buffer;
}
