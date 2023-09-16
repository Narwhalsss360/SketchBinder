#ifndef SketchBinder_h
#define SketchBinder_h

#include <Arduino.h>
#include <Callables.h>

#ifndef MAX_SKETCH_BINDINGS
#define MAX_SKETCH_BINDINGS 16
#endif

enum SketchBindTypes
{
	bind_setup,
	bind_setup_post,
	bind_loop,
	bind_loop_post
};

Callable* __sketch_bindings__[4][MAX_SKETCH_BINDINGS];
byte __sketch_binding_count__[4];

bool addInternalSketchBinding(SketchBindTypes bindType, Callable* callable)
{
	if (!callable)
		return false;
	if (__sketch_binding_count__[bindType] == MAX_SKETCH_BINDINGS)
		return false;
	__sketch_bindings__[bindType][__sketch_binding_count__[bindType]] = callable;
	__sketch_binding_count__[bindType]++;
}

void removeInternalSketchBinding(SketchBindTypes bindType, Callable* callable)
{
	for (byte i = 0; i < __sketch_binding_count__[bindType]; i++)
		if (__sketch_bindings__[bindType][i] == callable)
		{
			for (byte iShift = i; iShift < __sketch_binding_count__[bindType] - 1; iShift++)
				__sketch_bindings__[bindType][iShift] = __sketch_bindings__[bindType][iShift + 1];
			__sketch_binding_count__[bindType]--;
		}
}

void __setup__();
void __loop__();

void setup()
{
	for (byte i = 0; i < __sketch_binding_count__[bind_setup]; i++)
		__sketch_bindings__[bind_setup][i]->invoke();
	__setup__();
	for (byte i = 0; i < __sketch_binding_count__[bind_setup_post]; i++)
		__sketch_bindings__[bind_setup_post][i]->invoke();
}

void loop()
{
	for (byte i = 0; i < __sketch_binding_count__[bind_loop]; i++)
		__sketch_bindings__[bind_loop][i]->invoke();
	__loop__();
	for (byte i = 0; i < __sketch_binding_count__[bind_loop_post]; i++)
		__sketch_bindings__[bind_loop_post][i]->invoke();
}

#define setup __setup__
#define loop __loop__

#endif