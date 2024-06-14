#ifndef _VECTOR2_CLASS

#include "./vector2.h"

#pragma region Vector2
Vector2::Vector2(float x, float y){
    this->x = x;
    this->y = y;
}
Vector2::Vector2(){
    this->x = 0;
    this->y = 0;
}

Vector2Int Vector2::round() const {
    return Vector2Int(
        roundf(this->x),
        roundf(this->y)
    );
}
Vector2Int Vector2::floor() const {
    return Vector2Int(
        floorf(this->x),
        floorf(this->y)
    );
}

// return a vector which goes in the closest cardinal direction (right by default)
Vector2 Vector2::flat() const {
    if (this->x == 0 && this->y == 0) return Vector2(1, 0);
    
    if (abs(this->x) >= abs(this->y)) return Vector2(this->x / abs(this->x), 0);

    return Vector2(0, this->y / abs(this->y));
}

Vector2 Vector2::operator+(const Vector2& other) const {
    return Vector2(
        this->x + other.x,
        this->y + other.y
    );
}
Vector2& Vector2::operator+=(const Vector2& other){
    this->x += other.x;
    this->y += other.y;
    return *this;
}

Vector2 Vector2::operator-(const Vector2& other) const {
    return Vector2(
        this->x - other.x,
        this->y - other.y
    );
}
Vector2& Vector2::operator-=(const Vector2& other){
    this->x -= other.x;
    this->y -= other.y;
    return *this;
}

// per component multiplication
Vector2 Vector2::operator*(const Vector2& other) const {
    return Vector2(
        this->x * other.x,
        this->y * other.y
    );
}
// per component multiplication
Vector2& Vector2::operator*=(const Vector2& other){
    this->x *= other.x;
    this->y *= other.y;
    return *this;
}
Vector2 Vector2::operator*(float scalar) const {
    return Vector2(
        this->x * scalar,
        this->y * scalar
    );
}
Vector2& Vector2::operator*=(float scalar){
    this->x *= scalar;
    this->y *= scalar;
    return *this;
}

// per component division
Vector2 Vector2::operator/(const Vector2& other) const {
    return Vector2(
        this->x / other.x,
        this->y / other.y
    );
}
// per component division
Vector2& Vector2::operator/=(const Vector2& other){
    this->x /= other.x;
    this->y /= other.y;
    return *this;
}
Vector2 Vector2::operator/(float scalar) const {
    return Vector2(
        this->x / scalar,
        this->y / scalar
    );
}
Vector2& Vector2::operator/=(float scalar){
    this->x /= scalar;
    this->y /= scalar;
    return *this;
}

// per component mod
Vector2 Vector2::operator%(float scalar) const {
    return Vector2(
        this->x - floorf(this->x / scalar) * scalar,
        this->y - floorf(this->y / scalar) * scalar
    );
}
// per component mod
Vector2& Vector2::operator%=(float scalar) {
    this->x -= floorf(this->x / scalar) * scalar;
    this->y -= floorf(this->y / scalar) * scalar;
    return *this;
}

// return the component at this index (0 => x, 1 => y)
// throws an error if index < 0 or index > 1
float& Vector2::operator[](int index){
    switch (index)
    {
    case 0:
        return this->x;
    case 1:
        return this->y;
    
    default:
        std::cerr << "ERROR: trying to acces component " << index << " of a Vector2\n";
        exit(1);
    }
}
bool Vector2::operator==(const Vector2& other) const {
    return this->x == other.x && this->y == other.y;
}
bool Vector2::operator!=(const Vector2& other) const {
    return this->x != other.x || this->y != other.y;
}

// return a vector othogonal to this vector
Vector2 Vector2::cross() const {
    return Vector2(-(this->y), this->x);
}
// return the dot product of the two vectors
float Vector2::dot(const Vector2& other) const {
    return this->x * other.x + this->y * other.y;
}
// return the length of the vector
float Vector2::magnitude() const {
    return sqrtf(this->sqrmagnitude());
}
// return the squared length of the vector
float Vector2::sqrmagnitude() const {
    return this->x * this->x + this->y * this->y;
}
// normalize the vector in place and return itself
Vector2& Vector2::normalize(){
    *this /= this->magnitude();
    return *this;
}
// return a new vector with same direction and a norm of 1
Vector2 Vector2::normalized() const {
    return *this / this->magnitude();
}


// return a vector matching an angle (in radian)
// 0 rad => right
Vector2 Vector2::from_angle(float angle) {
    return Vector2(std::cos(angle), -std::sin(angle));
}
// return the reflection of the vector on a surface of normal given
Vector2 Vector2::reflect(const Vector2& normal) const {
    return *this - normal.normalized() * 2 * this->dot(normal.normalized());
}
// return a vector equals to this vector rotated by an angle <angle> in radians
Vector2 Vector2::rotate(float angle) const {
    return Vector2(
        this->x * std::cos(angle) - this->y * std::sin(angle),
        this->x * std::sin(angle) + this->y * std::cos(angle)
    );
}
// return the signed angle between 2 vectors
float Vector2::signed_angle(const Vector2& other) const {
    return std::atan2(other.y * this->x - other.x * this->y, other.x * this->x + other.y * this->y);
}

// return the vector with positive y as newUp
Vector2 Vector2::change_base(const Vector2& newUp) const {
    Vector2 newRight = newUp.cross();
    return Vector2(this->x * newRight.x + this->y * newRight.y, this->x * newUp.x + this->y * newUp.y);
}
// return the vector with x between maxX and minX and y between maxY and minY
Vector2 Vector2::clamp(float maxX, float maxY, float minX, float minY) const {
    return Vector2(__max(minX, __min(maxX, this->x)), __max(minY, __min(maxY, this->y)));
}
// return the interpolation of v1 and v2 with value
Vector2 Vector2::Lerp(const Vector2& v1, const Vector2& v2, float value) {
    return v1 + (v2 - v1) * value;
}

std::string Vector2::to_str() const {
    return "Vector2(" + std::to_string(this->x) + ", " + std::to_string(this->y) + ")";
}
#pragma endregion


#pragma region Vector2Int
Vector2Int::Vector2Int(int x, int y){
    this->x = x;
    this->y = y;
}
Vector2Int::Vector2Int(){
    this->x = 0;
    this->y = 0;
}

Vector2Int Vector2Int::operator+(const Vector2& other) const {
    return Vector2Int(
        this->x + other.x,
        this->y + other.y
    );
}
Vector2Int& Vector2Int::operator+=(const Vector2& other){
    this->x += other.x;
    this->y += other.y;
    return *this;
}

Vector2Int Vector2Int::operator-(const Vector2& other) const {
    return Vector2Int(
        this->x - other.x,
        this->y - other.y
    );
}
Vector2Int& Vector2Int::operator-=(const Vector2& other){
    this->x -= other.x;
    this->y -= other.y;
    return *this;
}

// per component multiplication
Vector2Int Vector2Int::operator*(const Vector2& other) const {
    return Vector2Int(
        this->x * other.x,
        this->y * other.y
    );
}
// per component multiplication
Vector2Int& Vector2Int::operator*=(const Vector2& other){
    this->x *= other.x;
    this->y *= other.y;
    return *this;
}
Vector2Int Vector2Int::operator*(float scalar) const {
    return Vector2(
        this->x * scalar,
        this->y * scalar
    ).round();
}
Vector2Int& Vector2Int::operator*=(float scalar){
    this->x *= scalar;
    this->y *= scalar;
    return *this;
}

// per component division
Vector2Int Vector2Int::operator/(const Vector2& other) const {
    return Vector2Int(
        this->x / other.x,
        this->y / other.y
    );
}
// per component division
Vector2Int& Vector2Int::operator/=(const Vector2& other){
    this->x /= other.x;
    this->y /= other.y;
    return *this;
}
Vector2Int Vector2Int::operator/(float scalar) const {
    return Vector2Int(
        this->x / scalar,
        this->y / scalar
    );
}
Vector2Int& Vector2Int::operator/=(float scalar){
    this->x /= scalar;
    this->y /= scalar;
    return *this;
}

// per component mod
Vector2Int Vector2Int::operator%(int scalar) const {
    return Vector2Int(
        this->x % scalar,
        this->y % scalar
    );
}
// per component mod
Vector2Int& Vector2Int::operator%=(int scalar) {
    this->x %= scalar;
    this->y %= scalar;
    return *this;
}

// return the component at this index (0 => x, 1 => y)
// throws an error if index < 0 or index > 1
int& Vector2Int::operator[](int index){
    switch (index)
    {
    case 0:
        return this->x;
    case 1:
        return this->y;
    
    default:
        std::cerr << "ERROR: trying to acces component " << index << " of a Vector2Int\n";
        exit(1);
    }
}
bool Vector2Int::operator==(const Vector2Int& other) const {
    return this->x == other.x && this->y == other.y;
}
bool Vector2Int::operator!=(const Vector2Int& other) const {
    return this->x != other.x || this->y != other.y;
}

// return the dot product of the two vectors
float Vector2Int::dot(const Vector2& other) const {
    return this->x * other.x + this->y * other.y;
}
// return the length of the vector
float Vector2Int::magnitude() const {
    return sqrt(this->sqrmagnitude());
}
// return the squared length of the vector
float Vector2Int::sqrmagnitude() const {
    return this->x * this->x + this->y * this->y;
}

std::string Vector2Int::to_str() const {
    return "Vector2Int(" + std::to_string(this->x) + ", " + std::to_string(this->y) + ")";
}
#pragma endregion

#endif