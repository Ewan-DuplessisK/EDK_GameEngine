#ifndef ORPG_GAMEENGINE_MATRICES_H
#define ORPG_GAMEENGINE_MATRICES_H

#include <iostream>
//#include <iomanip>
#include "Vectors.h"

/*class Matrix2{
public:
    Matrix2();
    Matrix2(const float src[4]);
    Matrix2(float m0, float m1, float m2, float m3);

    //Functions
    void set(const float mat[4]);
    void set(float m0, float m1, float m2, float m3);
    void setRow(int index, const float row[2]);
    void setRow(int index, const Vector2& v);
    void setColumn(int index, const float col[2]);
    void setColumn(int index, const Vector2& v);

    const float* get() const;
    const float* getTranspose();
    Vector2 getRow(int index) const;
    Vector2 getColumn(int index) const;
    float getDeterminant() const;
    float getAngle() const;
    Matrix2 getNegative();

    Matrix2& identity();
    Matrix2& transpose();
    Matrix2& invert();

    //Operators
    Matrix2 operator+(const Matrix2& rightMatrix) const;
    Matrix2 operator-(const Matrix2& rightMatrix) const;
    Matrix2& operator+=(const Matrix2& rightMatrix);
    Matrix2& operator-=(const Matrix2& rightMatrix);
    Matrix2 operator*(const Matrix2& rightMatrix) const;
    Matrix2& operator*=(const Matrix2& rightMatrix);

    bool operator==(const Matrix2& rightMatrix) const; //exact comparison
    bool operator!=(const Matrix2& rightMatrix) const; //exact comparison

    float operator[](int index) const; //accessor
    float& operator[](int index); //accessor

    Vector2 operator*(const Vector2& rightVector) const;

    friend Matrix2 operator*(float scalar, const Matrix2& m);
    friend Vector2 operator*(const Vector2& vec, const Matrix2& m);
    friend std::ostream& operator<<(std::ostream& os, const Matrix2& m);

private:
    float ma[4];
    float tm[4];
};*/

class Matrix4{
public:

    float matrix[4][4];
    float transposeMatrix[4][4];


    Matrix4();
    Matrix4(const float src[4][4]); //[row][col]
    Matrix4(float m00, float m01, float m02, float m03, // 1st row
            float m10, float m11, float m12, float m13, // 2nd row
            float m20, float m21, float m22, float m23, // 3rd row
            float m30, float m31, float m32, float m33);// 4th row

    //Functions
        //Setters
    void set(const float src[4][4]);
    void set(float m00, float m01, float m02, float m03, // 1st row
             float m10, float m11, float m12, float m13, // 2nd row
             float m20, float m21, float m22, float m23, // 3rd row
             float m30, float m31, float m32, float m33);// 4th row
    void setRow(int index, const float row[4]);
    void setRow(int index, const Vector4& v);
    //void setRow(int index, const Vector3& v);
    void setColumn(int index, const float col[4]);
    void setColumn(int index, const Vector4& v);
    void setColumn(int index, const Vector3& v);

        //Getters
    //[[nodiscard]] const float* get() const;
    void computeTranspose();
    [[nodiscard]] Vector4 getRow(int index) const;
    [[nodiscard]] Vector4 getColumn(int index) const;
    [[nodiscard]] float getDeterminant() const;
    [[nodiscard]] Vector3 getAngle() const; //(x,y,z) degrees
    [[nodiscard]] Vector3 getXVector() const; //TODO check if leftVector or rightVector
    [[nodiscard]] Vector3 getUpVector() const;
    [[nodiscard]] Vector3 getForward() const;
    [[nodiscard]] Vector3 getTranslation() const;

    Matrix4& identity();

    Matrix4& transpose();//self transpose
    Matrix4& invert(); //invertGeneral          //check best inverse method
    //Matrix4& invertAffine();
    //Matrix4& invertGeneral();

        //Transformations
    Matrix4& translate(float x, float y, float z);
    Matrix4& translate(const Vector3& v);

    Matrix4& rotate(float angle, const Vector3& rotAxis);
    Matrix4& rotate(float angle, float x, float y, float z);
    Matrix4& rotateX(float angle); //degrees
    Matrix4& rotateY(float angle); //degrees
    Matrix4& rotateZ(float angle); //degrees

    Matrix4& scale(float scale); //uniform
    Matrix4& scale(float xScale, float yScale, float zScale);
    Matrix4& scale(const Vector3& scaleVector);

    Matrix4& lookAt(float targetX, float targetY, float targetZ); //rotate towards target
    Matrix4& lookAt(float targetX, float targetY, float targetZ, float upX, float upY, float upZ); //rotate towards target and set up vector
    Matrix4& lookAt(const Vector3& target);
    Matrix4& lookAt(const Vector3& target, const Vector3& up);

    //Operators
    Matrix4 operator+(const Matrix4& rightMatrix) const;
    Matrix4 operator-(const Matrix4& rightMatrix) const;
    Matrix4& operator+=(const Matrix4& rightMatrix);
    Matrix4& operator-=(const Matrix4& rightMatrix);
    Matrix4 operator*(const Matrix4& rightMatrix) const;
    Matrix4& operator*=(const Matrix4& rightMatrix);
    bool operator==(const Matrix4& rightMatrix) const; //exact comparison
    bool operator!=(const Matrix4& rightMatrix) const; //exact comparison

    Vector4 operator*(const Vector4& rightVector) const;    // multiplication: v' = M * v
    Vector3 operator*(const Vector3& rightVector) const;    // multiplication: v' = M * v

    /*const float* operator[](int index) const; //accessor
    const float operator[](int index); //accessor*/

    friend Matrix4 operator-(const Matrix4& rightMatrix);
    friend Matrix4 operator*(float scalar, const Matrix4& rightMatrix);
    friend Vector3 operator*(const Vector3& leftVector, const Matrix4& rightMatrix);
    friend Vector4 operator*(const Vector4& leftVector, const Matrix4& rightMatrix);
    friend std::ostream& operator<<(std::ostream& os, const Matrix4& rightMatrix); //toString

private:
    float getCofactor(float m00,float m01,float m02,float m10,float m11,float m12,float m20,float m21,float m22) const;

public:
    Matrix4 createPerspectiveFOV(float fovY, float width, float height, float near, float far);
};




#endif //ORPG_GAMEENGINE_MATRICES_H
