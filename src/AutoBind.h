#ifndef AutoBind_h
#define AutoBind_h

#include "SketchBinder.h"

//User defined setup and loop.
void __setup__();

void __loop__();

void setup()
{
    binds::setup_pre();
    __setup__();
    binds::setup_post();
}

void loop()
{
    binds::loop_pre();
    __loop__();
    binds::loop_post();
}

#define setup __setup__

#define loop __loop__

#endif
