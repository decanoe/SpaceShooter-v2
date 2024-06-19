#ifndef _UPDATABLE_CLASS
#define _UPDATABLE_CLASS

#include "./physics/transform.h"
class Updatable: public Transform
{
public:
    // false if this instance belongs to another object and should not be deleted
    bool free_object = false;
    virtual void update() {};
    virtual void release() {};
    virtual void insert_to_world(bool free_object = false) {};
    virtual void change_chunk(Vector2Int previous_chunk_index) {};
};


#endif