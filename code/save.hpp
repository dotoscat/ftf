#ifndef  _save_
#define  _save_

#include <sqlite3.h>
#include "clock.hpp"

namespace fff{
    
    class _save{
    
        sqlite3 *db;
    
        public:
            _save();
            ~_save();
    
            float getMeters();
            fff::clock getClock();
            void saveNewScore(float, fff::clock &);
            
    };
    
    extern fff::_save save;
    
}

#endif
