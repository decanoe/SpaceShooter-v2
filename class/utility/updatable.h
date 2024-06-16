#ifndef _UPDATABLE_CLASS
#define _UPDATABLE_CLASS

class Updatable
{
public:
    // false if this instance belongs to another object and should not be deleted
    bool free_object = false;
    virtual void update() {};
    virtual void release() {};
};


#endif