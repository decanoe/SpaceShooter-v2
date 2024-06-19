#ifndef _VECTOR2_CLASS
#define _VECTOR2_CLASS

#ifndef PI
#define PI 3.14159265359
#endif

#include <iostream>
#include <string>
#include <cmath>

class Vector2Int;

class Vector2
{
private:
public:
    float x = 0, y = 0;
    
    Vector2();
    Vector2(float x, float y);
    Vector2(const Vector2Int& other);

    Vector2Int round() const;
    Vector2Int floor() const;
    // return a vector which goes in the closest cardinal direction (right by default)
    Vector2 flat() const;

    Vector2 operator+(const Vector2& other) const;
    Vector2& operator+=(const Vector2& other);

    Vector2 operator-(const Vector2& other) const;
    Vector2& operator-=(const Vector2& other);

    // per component multiplication
    Vector2 operator*(const Vector2& other) const;
    // per component multiplication
    Vector2& operator*=(const Vector2& other);
    Vector2 operator*(float scalar) const;
    Vector2& operator*=(float scalar);

    // per component division
    Vector2 operator/(const Vector2& other) const;
    // per component division
    Vector2& operator/=(const Vector2& other);
    Vector2 operator/(float scalar) const;
    Vector2& operator/=(float scalar);

    // per component mod
    Vector2 operator%(float scalar) const;
    // per component mod
    Vector2& operator%=(float scalar);

    // return the component at this index (0 => x, 1 => y)
    // throws an error if index < 0 or index > 1
    float& operator[](int index);
    bool operator==(const Vector2& other) const;
    bool operator!=(const Vector2& other) const;

    // return a vector othogonal to this vector
    Vector2 cross() const;
    // return the dot product of the two vectors
    float dot(const Vector2& other) const;
    // return the length of the vector
    float magnitude() const;
    // return the squared length of the vector
    float sqrmagnitude() const;
    // normalize the vector in place and return itself
    Vector2& normalize();
    // return a new vector with same direction and a norm of 1
    Vector2 normalized() const;

    // return a vector matching an angle (in radian)
    // 0 rad => right
    static Vector2 from_angle(float angle);
    // return the reflection of the vector on a surface of normal given
    Vector2 reflect(const Vector2& normal) const;
    // return a vector equals to this vector rotated by an angle <angle> in radians
    Vector2 rotate(float angle) const;
    // return the signed angle between 2 vectors
    float signed_angle(const Vector2& other) const;
    
    // return the vector with positive y as newUp
    Vector2 change_base(const Vector2& newUp) const;
    // return the vector with x between maxX and minX and y between maxY and minY
    Vector2 clamp(float maxX = 1, float maxY = 1, float minX = -1, float minY = -1) const;
    // return the interpolation of v1 and v2 with value
    static Vector2 Lerp(const Vector2& v1, const Vector2& v2, float value);

    // first test the x coordinate and only test the y if this.x == other.x. Must be implemented to use Vector2 in maps
    bool operator<(const Vector2 &other) const;
    std::string to_str() const;
};

class Vector2Int
{
private:
public:
    int x = 0, y = 0;
    
    Vector2Int();
    Vector2Int(int x, int y);
    Vector2Int(const Vector2& other);

    Vector2Int operator+(const Vector2& other) const;
    Vector2Int& operator+=(const Vector2& other);

    Vector2Int operator-(const Vector2& other) const;
    Vector2Int& operator-=(const Vector2& other);

    // per component multiplication
    Vector2Int operator*(const Vector2& other) const;
    // per component multiplication
    Vector2Int& operator*=(const Vector2& other);
    Vector2Int operator*(float scalar) const;
    Vector2Int& operator*=(float scalar);

    // per component division
    Vector2Int operator/(const Vector2& other) const;
    // per component division
    Vector2Int& operator/=(const Vector2& other);
    Vector2Int operator/(float scalar) const;
    Vector2Int& operator/=(float scalar);

    // per component mod
    Vector2Int operator%(int scalar) const;
    // per component mod
    Vector2Int& operator%=(int scalar);

    // return the component at this index (0 => x, 1 => y)
    // throws an error if index < 0 or index > 1
    int& operator[](int index);
    bool operator==(const Vector2Int& other) const;
    bool operator!=(const Vector2Int& other) const;

    // return the dot product of the two vectors
    float dot(const Vector2& other) const;
    // return the length of the vector
    float magnitude() const;
    // return the squared length of the vector
    float sqrmagnitude() const;

    // first test the x coordinate and only test the y if this.x == other.x. Must be implemented to use Vector2Int in maps
    bool operator<(const Vector2Int &other) const;
    std::string to_str() const;
};

#endif