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

Invokable<void>* __sketch_bindings__[4][MAX_SKETCH_BINDINGS];
byte __sketch_binding_count__[4];

/// @brief Bind a function to a sketch function.
/// @param bindType Where
/// @param invokable invokable
/// @return `bool` true if successfully bound
bool addInternalSketchBinding(SketchBindTypes bindType, Invokable<void>* invokable)
{
	if (!invokable)
		return false;
	if (!invokable->valid())
		return false;
	if (__sketch_binding_count__[bindType] == MAX_SKETCH_BINDINGS)
		return false;
	__sketch_bindings__[bindType][__sketch_binding_count__[bindType]] = invokable;
	__sketch_binding_count__[bindType]++;
	return true;
}

/// @brief Remove a function from a sketch function
/// @param bindType Where
/// @param invokable invokable
void removeInternalSketchBinding(SketchBindTypes bindType, Invokable<void>* invokable)
{
	for (byte i = 0; i < __sketch_binding_count__[bindType]; i++)
		if (__sketch_bindings__[bindType][i] == invokable)
		{
			for (byte iShift = i; iShift < __sketch_binding_count__[bindType] - 1; iShift++)
				__sketch_bindings__[bindType][iShift] = __sketch_bindings__[bindType][iShift + 1];
			__sketch_binding_count__[bindType]--;
		}
}

namespace binds
{
	void setup_pre()
	{
		for (byte i = 0; i < __sketch_binding_count__[bind_setup]; i++)
			__sketch_bindings__[bind_setup][i]->invoke();
	}

	void setup_post()
	{
		for (byte i = 0; i < __sketch_binding_count__[bind_setup_post]; i++)
			__sketch_bindings__[bind_setup_post][i]->invoke();
	}

	void loop_pre()
	{
		for (byte i = 0; i < __sketch_binding_count__[bind_loop]; i++)
			__sketch_bindings__[bind_loop][i]->invoke();
	}

	void loop_post()
	{
		for (byte i = 0; i < __sketch_binding_count__[bind_loop_post]; i++)
			__sketch_bindings__[bind_loop_post][i]->invoke();
	}
}

#endif
