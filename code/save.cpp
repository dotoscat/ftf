#include "save.hpp"

fff::_save::_save(){
    sqlite3_open("game/.save", &db);
}

fff::_save::~_save(){
    sqlite3_close(db);
}

fff::_save save;
