#include "data_repository.h"

#pragma warning (disable:4127)
#pragma warning (disable:4244)
#pragma warning (disable:4706)
#define SQLITE_ENABLE_COLUMN_METADATA
#include "sqlite3.h"


void repository::test()
{
    sqlite3* DB; 
    int exit = 0; 
    exit = sqlite3_open("example.db", &DB); 
  
    
    sqlite3_close(DB); 
}
