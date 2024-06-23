#ifndef _TRANSFORM_CLASS
#define _TRANSFORM_CLASS

#include "../math/vector2.h"
#include "./component.h"
#include <vector>

class GameObject;
class Component;
class Transform
{
private:
    static unsigned int ID_COUNT;
    unsigned int ID;
public:
    std::string name = "unnamed transform";
    Vector2 local_position = Vector2();
    float local_angle = 0;
    Vector2 local_size = Vector2(1, 1);
    Transform* parent = nullptr;
    std::vector<Component*> components;

    Transform(std::string name, Transform* parent = nullptr);
    ~Transform() {}

    virtual void update();
    virtual void release();

    std::string to_str() const;

    Vector2 root_position();
    Vector2 global_position();
    float global_angle();
    Vector2 global_size();

    void set_global_pos(Vector2 position);
    void set_global_angle(float angle);

    template <class T>
    std::vector<T*> get_components() {
        std::vector<T*> result;
        for (Component* c : this->components)
        {
            T* tptr = dynamic_cast<T*>(c);
            if (tptr != nullptr) result.push_back(tptr);
        }
        return result;
    }
    template <class T>
    T* get_component() {
        for (Component* c : this->components)
        {
            T* tptr = dynamic_cast<T*>(c);
            if (tptr != nullptr) return tptr;
        }
        return nullptr;
    }
};

#endif