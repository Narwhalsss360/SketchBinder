#include "Binds.h"

extern bool __ran_setup__;

bool binds::ranSetup()
{
    return __ran_setup__;
}
