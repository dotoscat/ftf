#include <iostream>
#include <cstdio>
#include "save.hpp"

fff::_save::_save(){
    db = NULL;
    if (sqlite3_open("game/.save", &db) != SQLITE_OK){
        std::cout << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_stmt *stmt = NULL;
    
    //does exists the table "game"?
    if( sqlite3_prepare_v2(db, "SELECT count(*) from sqlite_master WHERE type='table' AND name='game' ", -1, &stmt, NULL) != SQLITE_OK){
        std::cout << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_step(stmt);
    if (sqlite3_column_int(stmt, 0) ){
        sqlite3_finalize(stmt);
        return;
    }
    sqlite3_finalize(stmt);
    //
        
    //create the table the game
    if (sqlite3_prepare_v2(db, \
    "CREATE TABLE game (meters REAL, hours INTEGER, minutes INTEGER, seconds INTEGER, ms INTEGER)"\
    , -1, &stmt, NULL) != SQLITE_OK){
        std::cout << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    //
    //fill the table game
    if (sqlite3_prepare_v2(db, \
    "INSERT INTO game (meters, hours, minutes, seconds, ms) VALUES (0, 0, 0, 0, 0)"\
    , -1, &stmt, NULL) != SQLITE_OK){
        std::cout << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

fff::_save::~_save(){
    sqlite3_close(db);
}

float fff::_save::getMeters(){
    sqlite3_stmt *stmt = NULL;
    if (sqlite3_prepare_v2(db, \
    "SELECT meters FROM game"\
    , -1, &stmt, NULL) != SQLITE_OK){
        std::cout << sqlite3_errmsg(db) << std::endl;
    }
    float meters = 0.f;
    sqlite3_step(stmt);
    meters = sqlite3_column_double(stmt, 0);
    sqlite3_finalize(stmt);
    return meters;
}

fff::clock fff::_save::getClock(){
    sqlite3_stmt *stmt = NULL;
    if (sqlite3_prepare_v2(db, "SELECT hours, minutes, seconds, ms FROM game", -1, &stmt, NULL) != SQLITE_OK){
        std::cout << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_step(stmt);
    fff::clock clock;
    clock.hours = sqlite3_column_int(stmt, 0);
    clock.minutes = sqlite3_column_int(stmt, 1);
    clock.seconds = sqlite3_column_int(stmt, 2);
    clock.ms = sqlite3_column_int(stmt, 3);
    sqlite3_finalize(stmt);
    return clock;
}

void fff::_save::saveNewScore(float meters, fff::clock &clock){
    sqlite3_stmt *stmt = NULL;
    char buffer[128] = {0};
    snprintf(buffer, 128, \
    "UPDATE game SET meters=%g, hours=%d, minutes=%d, seconds=%d, ms=%d"\
    , meters, clock.hours, clock.minutes, clock.seconds, clock.ms);
    if (sqlite3_prepare_v2(db, buffer, -1, &stmt, NULL) != SQLITE_OK){
        std::cout << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    
}

fff::_save fff::save;
