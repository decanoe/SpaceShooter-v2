#ifndef _UPDATABLE_CLASS
#define _UPDATABLE_CLASS

#include "./screen.h"

class Updatable
{
public:
    void update(const Screen& screen) const;
};

#endif