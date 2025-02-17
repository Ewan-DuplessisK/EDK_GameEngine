#include "Vectors.h"

//Vector2
    //Functions

void Vector2::set(float inX, float inY) {
    x=inX;
    y=inY;
}

float Vector2::length() const {
    return sqrtf(x*x + y*y);
}

Vector2& Vector2::normalize() {
    float iLength = 1.f/ sqrtf(x*x+y*y);
    x *= iLength;
    y *= iLength;
    return *this;
}

Vector2 Vector2::getNegative() const {
    return Vector2(-x, -y);
}

float Vector2::distance(const Vector2& other) const {
    return sqrtf((other.x-x)*(other.x-x) + (other.y-y)*(other.y-y));
}

float Vector2::dot(const Vector2& other) const {
    return (x*other.x + y*other.y);
}

bool Vector2::equal(const Vector2& other, float eps) const {
    return fabs(x - other.x) < eps && fabs(y - other.y) < eps;
}

float Vector2::angleDeg(const Vector2& other) const {
    //[0, 180] degrees
    return acosf(this->dot(other)/(this->length()*other.length()))*RAD2DEG;
}

    //Operators

Vector2 Vector2::operator+(const Vector2& rightVector) const {
    return Vector2(x+rightVector.x, y+rightVector.y);
}

Vector2 Vector2::operator-(const Vector2& rightVector) const {
    return Vector2(x-rightVector.x, y-rightVector.y);
}

Vector2& Vector2::operator+=(const Vector2& rightVector) {
    x += rightVector.x; y += rightVector.y; return *this;
}

Vector2& Vector2::operator-=(const Vector2& rightVector) {
    x -= rightVector.x; y -= rightVector.y; return *this;
}

Vector2 Vector2::operator*(const Vector2& rightVector) const {
    return Vector2(x*rightVector.x, y*rightVector.y);
}

Vector2& Vector2::operator*=(const Vector2& rightVector) {
    x *= rightVector.x; y *= rightVector.y; return *this;
}

bool Vector2::operator==(const Vector2& rightVector) const {
    return (x == rightVector.x) && (y == rightVector.y);
}

bool Vector2::operator!=(const Vector2& rightVector) const {
    return (x != rightVector.x) || (y != rightVector.y);
}

bool Vector2::operator<(const Vector2& rightVector) const {
    if(x < rightVector.x) return true;
    if(x > rightVector.x) return false;
    if(y < rightVector.y) return true;
    if(y > rightVector.y) return false;
    return false;
}

Vector2 Vector2::operator*(const float a) const {
    return Vector2(x*a, y*a);
}

Vector2& Vector2::operator*=(const float a) {
    x *= a; y *= a; return *this;
}

Vector2 Vector2::operator/(const float a) const {
    return Vector2(x/a, y/a);
}

Vector2& Vector2::operator/=(const float a) {
    x /= a; y /= a; return *this;
}

float Vector2::operator[](int index) const {
    return (&x)[index];
}

float& Vector2::operator[](int index) {
    return (&x)[index];
}

Vector2 operator*(const float a, const Vector2 vec) {
    return Vector2(a*vec.x, a*vec.y);
}

std::ostream& operator<<(std::ostream& os, const Vector2& vec) {
    os << "(" << vec.x << ", " << vec.y << ")";
    return os;
}




//Vector3
    //Functions
void Vector3::set(float x, float y, float z) {
    this->x = x; this->y = y; this->z = z;
}

float Vector3::length() const {
    return sqrtf(x*x + y*y + z*z);
}

Vector3& Vector3::normalize() {
    float iLength = 1.0f / sqrtf(x*x+y*y+z*z);
    x *= iLength;
    y *= iLength;
    z *= iLength;
    return *this;
}

Vector3 Vector3::getNegative() const {
    return Vector3(-x, -y, -z);
}

float Vector3::distance(const Vector3& other) const {
    return sqrtf((other.x-x)*(other.x-x) + (other.y-y)*(other.y-y) + (other.z-z)*(other.z-z));
}

float Vector3::dot(const Vector3& rightVector) const {
    return (x*rightVector.x + y*rightVector.y + z*rightVector.z);
}

bool Vector3::equal(const Vector3& rightVector, float eps) const {
    return fabs(x - rightVector.x) < eps && fabs(y - rightVector.y) < eps && fabs(z - rightVector.z) < eps;
}

float Vector3::angleDeg(const Vector3& other) const {
    //[0, 180] degrees
    return acosf(this->dot(other)/(this->length()*other.length()))*RAD2DEG;
}

Vector3 Vector3::cross(const Vector3& rightVector) const {
    return Vector3(y*rightVector.z - z*rightVector.y, z*rightVector.x - x*rightVector.z, x*rightVector.y - y*rightVector.x);
}


    //Operators
Vector3 Vector3::operator+(const Vector3& rightVector) const {
    return Vector3(x+rightVector.x, y+rightVector.y, z+rightVector.z);
}

Vector3 Vector3::operator-(const Vector3& rightVector) const {
    return Vector3(x-rightVector.x, y-rightVector.y, z-rightVector.z);
}

Vector3& Vector3::operator+=(const Vector3& rightVector) {
    x += rightVector.x; y += rightVector.y; z += rightVector.z; return *this;
}

Vector3& Vector3::operator-=(const Vector3& rightVector) {
    x -= rightVector.x; y -= rightVector.y; z -= rightVector.z; return *this;
}

Vector3 Vector3::operator*(const Vector3& rightVector) const {
    return Vector3(x*rightVector.x, y*rightVector.y, z*rightVector.z);
}

Vector3& Vector3::operator*=(const Vector3& rightVector) {
    x *= rightVector.x; y *= rightVector.y; z *= rightVector.z; return *this;
}

bool Vector3::operator==(const Vector3& rightVector) const {
    return (x == rightVector.x) && (y == rightVector.y) && (z == rightVector.z);
}

bool Vector3::operator!=(const Vector3& rightVector) const {
    return (x != rightVector.x) || (y != rightVector.y) || (z != rightVector.z);
}

bool Vector3::operator<(const Vector3& rightVector) const {
    if(x < rightVector.x) return true;
    if(x > rightVector.x) return false;
    if(y < rightVector.y) return true;
    if(y > rightVector.y) return false;
    if(z < rightVector.z) return true;
    if(z > rightVector.z) return false;
    return false;
}

Vector3 Vector3::operator*(const float a) const {
    return Vector3(x*a, y*a, z*a);
}

Vector3& Vector3::operator*=(const float a) {
    x *= a; y *= a; z *= a; return *this;
}

Vector3 Vector3::operator/(const float a) const {
    return Vector3(x/a, y/a, z/a);
}

Vector3& Vector3::operator/=(const float a) {
    x /= a; y /= a; z /= a; return *this;
}

float Vector3::operator[](int index) const {
    return (&x)[index];
}

float& Vector3::operator[](int index) {
    return (&x)[index];
}

Vector3 operator*(const float a, const Vector3 vec) {
    return Vector3(a*vec.x, a*vec.y, a*vec.z);
}

std::ostream& operator<<(std::ostream& os, const Vector3& vec) {
    os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return os;
}


//Vector4
    //Functions
void Vector4::set(float x, float y, float z, float w) {
    this->x = x; this->y = y; this->z = z; this->w = w;
}

float Vector4::length() const {
    return sqrtf(x*x + y*y + z*z + w*w);
}

Vector4& Vector4::normalize() {
    float iLength = 1.0f / sqrtf(x*x+y*y+z*z+w*w);
    x *= iLength;
    y *= iLength;
    z *= iLength;
    w *= iLength;
    return *this;
}

Vector4 Vector4::getNegative() const {
    return Vector4(-x, -y, -z, -w);
}

float Vector4::distance(const Vector4& vec) const {
    return sqrtf((vec.x-x)*(vec.x-x) + (vec.y-y)*(vec.y-y) + (vec.z-z)*(vec.z-z) + (vec.w-w)*(vec.w-w));
}

float Vector4::dot(const Vector4& rightVector) const {
    return (x*rightVector.x + y*rightVector.y + z*rightVector.z + w*rightVector.w);
}

bool Vector4::equal(const Vector4& rightVector, float eps) const {
    return fabs(x - rightVector.x) < eps && fabs(y - rightVector.y) < eps &&
           fabs(z - rightVector.z) < eps && fabs(w - rightVector.w) < eps;
}

    //Operators
Vector4 Vector4::operator+(const Vector4& rightVector) const {
    return Vector4(x+rightVector.x, y+rightVector.y, z+rightVector.z, w+rightVector.w);
}

Vector4 Vector4::operator-(const Vector4& rightVector) const {
    return Vector4(x-rightVector.x, y-rightVector.y, z-rightVector.z, w-rightVector.w);
}

Vector4& Vector4::operator+=(const Vector4& rightVector) {
    x += rightVector.x; y += rightVector.y; z += rightVector.z; w += rightVector.w; return *this;
}

Vector4& Vector4::operator-=(const Vector4& rightVector) {
    x -= rightVector.x; y -= rightVector.y; z -= rightVector.z; w -= rightVector.w; return *this;
}

Vector4 Vector4::operator*(const Vector4& rightVector) const {
    return Vector4(x*rightVector.x, y*rightVector.y, z*rightVector.z, w*rightVector.w);
}

Vector4& Vector4::operator*=(const Vector4& rightVector) {
    x *= rightVector.x; y *= rightVector.y; z *= rightVector.z; w *= rightVector.w; return *this;
}

bool Vector4::operator==(const Vector4& rightVector) const {
    return (x == rightVector.x) && (y == rightVector.y) && (z == rightVector.z) && (w == rightVector.w);
}

bool Vector4::operator!=(const Vector4& rightVector) const {
    return (x != rightVector.x) || (y != rightVector.y) || (z != rightVector.z) || (w != rightVector.w);
}

bool Vector4::operator<(const Vector4& rightVector) const {
    if(x < rightVector.x) return true;
    if(x > rightVector.x) return false;
    if(y < rightVector.y) return true;
    if(y > rightVector.y) return false;
    if(z < rightVector.z) return true;
    if(z > rightVector.z) return false;
    if(w < rightVector.w) return true;
    if(w > rightVector.w) return false;
    return false;
}

Vector4 Vector4::operator*(const float a) const {
    return Vector4(x*a, y*a, z*a, w*a);
}

Vector4& Vector4::operator*=(const float a) {
    x *= a; y *= a; z *= a; w *= a; return *this;
}

Vector4 Vector4::operator/(const float a) const {
    return Vector4(x/a, y/a, z/a, w/a);
}

Vector4& Vector4::operator/=(const float a) {
    x /= a; y /= a; z /= a; w /= a; return *this;
}

float Vector4::operator[](int index) const {
    return (&x)[index];
}

float& Vector4::operator[](int index) {
    return (&x)[index];
}

Vector4 operator*(const float a, const Vector4 vec) {
    return Vector4(a*vec.x, a*vec.y, a*vec.z, a*vec.w);
}

std::ostream& operator<<(std::ostream& os, const Vector4& vec) {
    os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
    return os;
}