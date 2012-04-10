#ifndef  _save_
#define  _save_

#include <sqlite3.h>

namespace fff{
    
    class _save{
    
        sqlite3 *db;
    
        public:
            _save();
            ~_save();
    
    };
    
    extern fff::_save save;
    
}

#endif
