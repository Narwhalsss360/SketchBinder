#if !defined(SketchBoundLibrary_h)
#define SketchBoundLibrary_h

#ifndef SketchBinder_h
#include <Callables.h>

enum SketchBindTypes
{
    bind_setup,
    bind_setup_post,
    bind_loop,
    bind_loop_post
};

bool addInternalSketchBinding(SketchBindTypes bindType, Invokable<void>* callable) __attribute__((weak));
void removeInternalSketchBinding(SketchBindTypes bindType, Invokable<void>* callable) __attribute__((weak));
#endif

/// @brief Bind a function to a sketch function.
/// @param bindType Where
/// @param invokable invokable
/// @return `bool` true if successfully bound
static bool addSketchBinding(SketchBindTypes bindType, Invokable<void>* invokable)
{
    if (addInternalSketchBinding)
        return addInternalSketchBinding(bindType, invokable);
    else
        return false;
}

/// @brief Remove a function from a sketch functiond
/// @param bindType Where
/// @param invokable invokable
static void removeSketchBinding(SketchBindTypes bindType, Invokable<void>* invokable)
{
    if (removeInternalSketchBinding)
        removeInternalSketchBinding(bindType, invokable);
}

#endif
