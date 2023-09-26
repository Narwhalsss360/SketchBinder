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

bool addInternalSketchBinding(SketchBindTypes bindType, Invokable<void>* callable); __attribute__((weak));
void removeInternalSketchBinding(SketchBindTypes bindType, Invokable<void>* callable); __attribute__((weak));
#endif

static bool addSketchBinding(SketchBindTypes bindType, Invokable<void>* callable)
{
    if (addInternalSketchBinding)
        return addInternalSketchBinding(bindType, callable);
    else
        return false;
}

static void removeSketchBinding(SketchBindTypes bindType, Invokable<void>* callable)
{
    if (removeInternalSketchBinding)
        removeInternalSketchBinding(bindType, callable);
}
#endif