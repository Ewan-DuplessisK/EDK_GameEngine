#ifndef ORPG_GAMEENGINE_VECTORS_H
#define ORPG_GAMEENGINE_VECTORS_H


#include <ostream>

const float DEG2RAD = 3.141593f / 180.0f;
const float RAD2DEG = 180.0f / 3.141593f;
const float EPSILON = 0.00001f;

struct Vector2{
public:
    float x,y;

    Vector2():x(0.f),y(0.f){}
    Vector2(float inX,float inY):x(inX),y(inY){}
    
    //Functions
    void set(float inX,float inY);
    
    float length() const;
    Vector2& normalize();
    Vector2 getNegative() const;
    
    float distance(const Vector2& other) const;
    float dot(const Vector2& other) const;
    bool equal(const Vector2& other,float eps) const; //epsilon comparison
    float angleDeg(const Vector2& other) const;
    
    //Operators
    Vector2 operator+(const Vector2& rightVector) const;
    Vector2 operator-(const Vector2& rightVector) const;
    Vector2& operator+=(const Vector2& rightVector);
    Vector2& operator-=(const Vector2& rightVector);
    Vector2 operator*(const Vector2& rightVector) const;
    Vector2& operator*=(const Vector2& rightVector);
    bool operator==(const Vector2& rightVector) const; //exact comparison
    bool operator!=(const Vector2& rightVector) const; //exact comparison
    bool operator<(const Vector2& rightVector) const; //sorting

    Vector2 operator*(const float scaleFactor) const;
    Vector2& operator*=(const float scaleFactor);
    Vector2 operator/(const float scaleFactor) const;
    Vector2& operator/=(const float scaleFactor);

    float operator[](int index) const; //accessor
    float& operator[](int index); //accessor

    friend Vector2 operator*(const float a, const Vector2 vec);
    friend std::ostream& operator<<(std::ostream& os, const Vector2& vec);
};


struct Vector3{
public:
    float x,y,z;

    Vector3():x(0.f),y(0.f),z(0.f){}
    Vector3(float inX,float inY,float inZ):x(inX),y(inY),z(inZ){}

    //Functions
    void set(float inX,float inY,float inZ);

    float length() const;
    Vector3& normalize();
    Vector3 getNegative() const;

    float distance(const Vector3& other) const;
    float dot(const Vector3& other) const;
    bool equal(const Vector3& other,float eps) const; //epsilon comparison
    float angleDeg(const Vector3& other) const;
    Vector3 cross(const Vector3& other) const;

    //Operators
    Vector3 operator+(const Vector3& rightVector) const;
    Vector3 operator-(const Vector3& rightVector) const;
    Vector3& operator+=(const Vector3& rightVector);
    Vector3& operator-=(const Vector3& rightVector);
    Vector3 operator*(const Vector3& rightVector) const;
    Vector3& operator*=(const Vector3& rightVector);
    bool operator==(const Vector3& rightVector) const; //exact comparison
    bool operator!=(const Vector3& rightVector) const; //exact comparison
    bool operator<(const Vector3& rightVector) const; //sorting

    Vector3 operator*(const float scaleFactor) const;
    Vector3& operator*=(const float scaleFactor);
    Vector3 operator/(const float scaleFactor) const;
    Vector3& operator/=(const float scaleFactor);

    float operator[](int index) const; //accessor
    float& operator[](int index); //accessor

    friend Vector3 operator*(const float a, const Vector3 vec);
    friend std::ostream& operator<<(std::ostream& os, const Vector3& vec);
};

struct Vector4{
public:
    float x,y,z,w;

    Vector4():x(0.f),y(0.f),z(0.f),w(0.f){}
    Vector4(float inX,float inY,float inZ,float inW):x(inX),y(inY),z(inZ),w(inW){}

    //Functions
    void set(float inX,float inY,float inZ,float inW);

    float length() const;
    Vector4& normalize();
    Vector4 getNegative() const;

    float distance(const Vector4& other) const;
    float dot(const Vector4& other) const;
    bool equal(const Vector4& other,float eps) const; //epsilon comparison

    //Operators
    Vector4 operator+(const Vector4& rightVector) const;
    Vector4 operator-(const Vector4& rightVector) const;
    Vector4& operator+=(const Vector4& rightVector);
    Vector4& operator-=(const Vector4& rightVector);
    Vector4 operator*(const Vector4& rightVector) const;
    Vector4& operator*=(const Vector4& rightVector);
    bool operator==(const Vector4& rightVector) const; //exact comparison
    bool operator!=(const Vector4& rightVector) const; //exact comparison
    bool operator<(const Vector4& rightVector) const; //sorting

    Vector4 operator*(const float scaleFactor) const;
    Vector4& operator*=(const float scaleFactor);
    Vector4 operator/(const float scaleFactor) const;
    Vector4& operator/=(const float scaleFactor);

    float operator[](int index) const; //accessor
    float& operator[](int index); //accessor

    friend Vector4 operator*(const float a, const Vector4 vec);
    friend std::ostream& operator<<(std::ostream& os, const Vector4& vec);
};


#endif //ORPG_GAMEENGINE_VECTORS_H
