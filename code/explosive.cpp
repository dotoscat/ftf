#include "explosive"

fff::explosive::explosive(){
    exists = false;
    impulse = 0.f;
    shape = NULL;
}

fff::explosive::~explosive(){
    if (shape == NULL){
        return;}
    cpShapeFree(shape);
}
