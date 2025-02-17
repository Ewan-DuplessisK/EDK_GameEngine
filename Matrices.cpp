#include <iomanip>
#include "Matrices.h"

Matrix4::Matrix4() {
    identity();
}

Matrix4::Matrix4(const float src[4][4]) {
    set(src);
}

Matrix4::Matrix4(float m00, float m01, float m02, float m03, // 1st row
        float m10, float m11, float m12, float m13, // 2nd row
        float m20, float m21, float m22, float m23, // 3rd row
        float m30, float m31, float m32, float m33) {// 4th row
    set(m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22,  m23, m30, m31, m32, m33);
}

void Matrix4::set(const float src[4][4]) {
    for(int i=0;i<4;i++){
        setRow(i,src[i]);
    }
}

void Matrix4::set(float m00, float m01, float m02, float m03, // 1st row
         float m10, float m11, float m12, float m13, // 2nd row
         float m20, float m21, float m22, float m23, // 3rd row
         float m30, float m31, float m32, float m33){ //4th row
    matrix[0][0]=m00;
    matrix[0][1]=m01;
    matrix[0][2]=m02;
    matrix[0][3]=m03;

    matrix[1][0]=m10;
    matrix[1][1]=m11;
    matrix[1][2]=m12;
    matrix[1][3]=m13;

    matrix[2][0]=m20;
    matrix[2][1]=m21;
    matrix[2][2]=m22;
    matrix[2][3]=m23;

    matrix[3][0]=m30;
    matrix[3][1]=m31;
    matrix[3][2]=m32;
    matrix[3][3]=m33;
}

void Matrix4::setRow(int index, const float row[4]){
    for(int i=0;i<4;i++){
        matrix[index][i]=row[i];
    }
}

void Matrix4::setRow(int index, const Vector4& v){
    for(int i=0;i<4;i++){
        matrix[index][i]=v[i];
    }
}

void Matrix4::setColumn(int index, const float col[4]){
    for(int i=0;i<4;i++){
        matrix[i][index]=col[i];
    }
}

void Matrix4::setColumn(int index, const Vector4& v){
    for(int i=0;i<4;i++){
        matrix[i][index]=v[i];
    }
}

void Matrix4::setColumn(int index, const Vector3& v){
    for(int i=0;i<3;i++){
        matrix[i][index]=v[i];
    }
}

void Matrix4::computeTranspose(){
    transposeMatrix[0][0] = matrix[0][0];
    transposeMatrix[0][1] = matrix[1][0];
    transposeMatrix[0][2] = matrix[2][0];
    transposeMatrix[0][3] = matrix[3][0];

    transposeMatrix[1][0] = matrix[0][1];
    transposeMatrix[1][1] = matrix[1][1];
    transposeMatrix[1][2] = matrix[2][1];
    transposeMatrix[1][3] = matrix[3][1];

    transposeMatrix[2][0] = matrix[0][2];
    transposeMatrix[2][1] = matrix[1][2];
    transposeMatrix[2][2] = matrix[2][2];
    transposeMatrix[2][3] = matrix[3][2];

    transposeMatrix[3][0] = matrix[0][3];
    transposeMatrix[3][1] = matrix[1][3];
    transposeMatrix[3][2] = matrix[2][3];
    transposeMatrix[3][3] = matrix[3][3];
}

Vector4 Matrix4::getRow(int index) const{
    return Vector4{matrix[index][0],matrix[index][1],matrix[index][2],matrix[index][3]};
}

Vector4 Matrix4::getColumn(int index) const{
    return Vector4{matrix[0][index],matrix[1][index],matrix[2][index],matrix[3][index]};
}

float Matrix4::getDeterminant() const{
    return matrix[0][0]*getCofactor(/*[1][1]to[3][3]*/matrix[1][1],matrix[1][2],matrix[1][3],matrix[2][1],matrix[2][2],matrix[2][3],matrix[3][1],matrix[3][2],matrix[3][3])
    - matrix[0][1]*getCofactor(matrix[1][0],matrix[1][2],matrix[1][3],matrix[2][0],matrix[2][2],matrix[2][3],matrix[3][0],matrix[3][2],matrix[3][3])
    + matrix[0][2]*getCofactor(matrix[1][0],matrix[1][1],matrix[1][3],matrix[2][0],matrix[2][1],matrix[2][3],matrix[3][0],matrix[3][1],matrix[3][3])
    - matrix[0][3]*getCofactor(matrix[1][0],matrix[1][1],matrix[1][2],matrix[2][0],matrix[2][1],matrix[2][2],matrix[3][0],matrix[3][1],matrix[3][2]);
}

float Matrix4::getCofactor(float m00,float m01,float m02,float m10,float m11,float m12,float m20,float m21,float m22) const {
    return m00*(m11*m22-m12*m21) - m01*(m10*m22-m12*m20) + m02*(m10*m21-m11*m20);
}

Vector3 Matrix4::getAngle() const{
    float xAngle,yAngle,zAngle;

    yAngle = RAD2DEG * asin(matrix[2][0]);
    if(matrix[2][2]<0){
        if(yAngle>=0.f)yAngle=180.f-yAngle;
        else yAngle = -180.f-yAngle;
    }

    if(matrix[2][2]>-EPSILON && matrix[0][0]<EPSILON){
        zAngle = 0.f;
        xAngle = RAD2DEG * atan2f(matrix[0][1],matrix[1][1]);
    }else{
        zAngle = RAD2DEG * atan2f(-matrix[1][0],matrix[0][0]);
        xAngle = RAD2DEG * atan2f(-matrix[2][1],matrix[2][2]);
    }

    return Vector3(xAngle,yAngle,zAngle);
}

Vector3 Matrix4::getXVector() const {
    return Vector3(matrix[0][0],matrix[0][1],matrix[0][2]);
}

Vector3 Matrix4::getUpVector() const {
    return Vector3(matrix[1][0],matrix[1][1],matrix[1][2]);
}

Vector3 Matrix4::getForward() const {
    return Vector3(matrix[2][0],matrix[2][1],matrix[2][2]);
}

Vector3 Matrix4::getTranslation() const {
    return Vector3(matrix[3][0],matrix[3][1],matrix[3][2]);
}

Matrix4 &Matrix4::identity() {
    setRow(0,{1.f,0.f,0.f,0.f});
    setRow(1,{0.f,1.f,0.f,0.f});
    setRow(2,{0.f,0.f,1.f,0.f});
    setRow(3,{0.f,0.f,0.f,1.f});
    return *this;
}

Matrix4 &Matrix4::transpose() {
    std::swap(matrix[0][1],matrix[1][0]);
    std::swap(matrix[0][2],matrix[2][0]);
    std::swap(matrix[0][3],matrix[3][0]);
    std::swap(matrix[1][2],matrix[2][1]);
    std::swap(matrix[1][3],matrix[3][1]);
    std::swap(matrix[2][3],matrix[3][2]);

    return *this;
}

/*Matrix4 &Matrix4::invert() {
    if(matrix[0][3]==0 && matrix[1][3]==0 && matrix[2][3]==0 && matrix[3][3]==0)this->invertAffine();
    else this->invertGeneral();

    return *this;
}*/

//Matrix4 &Matrix4::invertAffine() {}

Matrix4 &Matrix4::invert(){
    float determinant=getDeterminant();
    if(fabsf(determinant)<=EPSILON)return identity();

    float cof0 = getCofactor(matrix[1][1],matrix[1][2],matrix[1][3],matrix[2][1],matrix[2][2],matrix[2][3],matrix[3][1],matrix[3][2],matrix[3][3]);
    float cof1 = getCofactor(matrix[1][0],matrix[1][2],matrix[1][3],matrix[2][0],matrix[2][2],matrix[2][3],matrix[3][0],matrix[3][2],matrix[3][3]);
    float cof2 = getCofactor(matrix[1][0],matrix[1][1],matrix[1][3],matrix[2][0],matrix[2][1],matrix[2][3],matrix[3][0],matrix[3][1],matrix[3][3]);
    float cof3 = getCofactor(matrix[1][0],matrix[1][1],matrix[1][2],matrix[2][0],matrix[2][1],matrix[2][2],matrix[3][0],matrix[3][1],matrix[3][2]);

    float cof4 = getCofactor(matrix[0][1],matrix[0][2],matrix[0][3],matrix[2][1],matrix[2][2],matrix[2][3],matrix[3][1],matrix[3][2],matrix[3][3]);
    float cof5 = getCofactor(matrix[0][0],matrix[0][2],matrix[0][3],matrix[2][0],matrix[2][2],matrix[2][3],matrix[3][0],matrix[3][2],matrix[3][3]);
    float cof6 = getCofactor(matrix[0][0],matrix[0][1],matrix[0][3],matrix[2][0],matrix[2][1],matrix[2][3],matrix[3][0],matrix[3][1],matrix[3][3]);
    float cof7 = getCofactor(matrix[0][0],matrix[0][1],matrix[0][2],matrix[2][0],matrix[2][1],matrix[2][2],matrix[3][0],matrix[3][1],matrix[3][2]);

    float cof8 = getCofactor(matrix[0][1],matrix[0][2],matrix[0][3],matrix[1][1],matrix[1][2],matrix[1][3],matrix[3][1],matrix[3][2],matrix[3][3]);
    float cof9 = getCofactor(matrix[0][0],matrix[0][2],matrix[0][3],matrix[1][0],matrix[1][2],matrix[1][3],matrix[3][0],matrix[3][2],matrix[3][3]);
    float cof10 = getCofactor(matrix[0][0],matrix[0][1],matrix[0][3],matrix[1][0],matrix[1][1],matrix[1][3],matrix[3][0],matrix[3][1],matrix[3][3]);
    float cof11 = getCofactor(matrix[0][0],matrix[0][1],matrix[0][2],matrix[1][0],matrix[1][1],matrix[1][2],matrix[3][0],matrix[3][1],matrix[3][2]);

    float cof12 = getCofactor(matrix[0][1],matrix[0][2],matrix[0][3],matrix[1][1],matrix[1][2],matrix[1][3],matrix[2][1],matrix[2][2],matrix[2][3]);
    float cof13 = getCofactor(matrix[0][0],matrix[0][2],matrix[0][3],matrix[1][0],matrix[1][2],matrix[1][3],matrix[2][0],matrix[2][2],matrix[2][3]);
    float cof14 = getCofactor(matrix[0][0],matrix[0][1],matrix[0][3],matrix[1][0],matrix[1][1],matrix[1][3],matrix[2][0],matrix[2][1],matrix[2][3]);
    float cof15 = getCofactor(matrix[0][0],matrix[0][1],matrix[0][2],matrix[1][0],matrix[1][1],matrix[1][2],matrix[2][0],matrix[2][1],matrix[2][2]);

    float invDet = 1.f/determinant;

    matrix[0][0] = cof0 * invDet;
    matrix[0][1] = cof4 * invDet;
    matrix[0][2] = cof8 * invDet;
    matrix[0][3] = cof12 * invDet;

    matrix[1][0] = cof1 * invDet;
    matrix[1][1] = cof5 * invDet;
    matrix[1][2] = cof9 * invDet;
    matrix[1][3] = cof13 * invDet;

    matrix[2][0] = cof2 * invDet;
    matrix[2][1] = cof6 * invDet;
    matrix[2][2] = cof10 * invDet;
    matrix[2][3] = cof14 * invDet;

    matrix[3][0] = cof3 * invDet;
    matrix[3][1] = cof7 * invDet;
    matrix[3][2] = cof11 * invDet;
    matrix[3][3] = cof15 * invDet;

    return *this;
}

Matrix4& Matrix4::translate(float x, float y, float z){
    matrix[0][0] += matrix[0][3] * x;
    matrix[0][1] += matrix[0][3] * y;
    matrix[0][2] += matrix[0][3] * z;

    matrix[1][0] += matrix[1][3] * x;
    matrix[1][1] += matrix[1][3] * y;
    matrix[1][2] += matrix[1][3] * z;

    matrix[2][0] += matrix[2][3] * x;
    matrix[2][1] += matrix[2][3] * y;
    matrix[2][2] += matrix[2][3] * z;

    matrix[3][0] += matrix[3][3] * x;
    matrix[3][1] += matrix[3][3] * y;
    matrix[3][2] += matrix[3][3] * z;

    return *this;
}

Matrix4& Matrix4::translate(const Vector3& v){
    return translate(v.x,v.y,v.z);
}

Matrix4& Matrix4::rotate(float angle, const Vector3& rotAxis){
    return rotate(angle,rotAxis.x,rotAxis.y,rotAxis.z);
}

Matrix4& Matrix4::rotate(float angle, float x, float y, float z){
    float cosAngle = cosf(angle * DEG2RAD);
    float sinAngle = sinf(angle * DEG2RAD);
    float oneMinus = 1.f - cosAngle;

    float m00=matrix[0][0];
    float m01=matrix[0][1];
    float m02=matrix[0][2];

    float m10=matrix[1][0];
    float m11=matrix[1][1];
    float m12=matrix[1][2];

    float m20=matrix[2][0];
    float m21=matrix[2][1];
    float m22=matrix[2][2];

    float m30=matrix[3][0];
    float m31=matrix[3][1];
    float m32=matrix[3][2];

    //Rotation matrix
    float r00 = x*x * oneMinus * cosAngle;
    float r01 = x*y * oneMinus + z * sinAngle;
    float r02 = x*z * oneMinus - y * sinAngle;

    float r10 = x*y * oneMinus - z * sinAngle;
    float r11 = y*y * oneMinus + cosAngle;
    float r12 = y*z * oneMinus + x * sinAngle;

    float r20 = x*z * oneMinus + y * sinAngle;
    float r21 = y*z * oneMinus - x * sinAngle;
    float r22 = z*z * oneMinus + cosAngle;

    matrix[0][0] = r00 * m00 + r10 * m01 + r20 * m02;
    matrix[0][1] = r01 * m00 + r11 * m01 + r21 * m02;
    matrix[0][2] = r02 * m00 + r12 * m01 + r22 * m02;

    matrix[1][0] = r00 * m10 + r10 * m11 + r20 * m12;
    matrix[1][1] = r01 * m10 + r11 * m11 + r21 * m12;
    matrix[1][2] = r02 * m10 + r12 * m11 + r22 * m12;

    matrix[2][0] = r00 * m20 + r10 * m21 + r20 * m22;
    matrix[2][1] = r01 * m20 + r11 * m21 + r21 * m22;
    matrix[2][2] = r02 * m20 + r12 * m21 + r22 * m22;

    matrix[3][0] = r00 * m30 + r10 * m31 + r20 * m32;
    matrix[3][1] = r01 * m30 + r11 * m31 + r21 * m32;
    matrix[3][2] = r02 * m30 + r12 * m31 + r22 * m32;

    return *this;
}

Matrix4& Matrix4::rotateX(float angle){
    float cosAngle = cosf(angle * DEG2RAD);
    float sinAngle = sinf(angle * DEG2RAD);

    float m01=matrix[0][1];
    float m02=matrix[0][2];

    float m11=matrix[1][1];
    float m12=matrix[1][2];

    float m21=matrix[2][1];
    float m22=matrix[2][2];

    float m31=matrix[3][1];
    float m32=matrix[3][2];

    matrix[0][1] = m01 * cosAngle + m02 * -sinAngle;
    matrix[0][2] = m01 * sinAngle + m02 * cosAngle;

    matrix[1][1] = m11 * cosAngle + m12 * -sinAngle;
    matrix[1][2] = m11 * sinAngle + m12 * cosAngle;

    matrix[2][1] = m21 * cosAngle + m22 * -sinAngle;
    matrix[2][2] = m21 * sinAngle + m22 * cosAngle;

    matrix[3][1] = m31 * cosAngle + m32 * -sinAngle;
    matrix[3][2] = m31 * sinAngle + m32 * cosAngle;

    return *this;
}

Matrix4& Matrix4::rotateY(float angle) {
    float cosAngle = cosf(angle * DEG2RAD);
    float sinAngle = sinf(angle * DEG2RAD);

    float m00=matrix[0][0];
    float m02=matrix[0][2];

    float m10=matrix[1][0];
    float m12=matrix[1][2];

    float m20=matrix[2][0];
    float m22=matrix[2][2];

    float m30=matrix[3][0];
    float m32=matrix[3][2];

    matrix[0][0] = m00 * cosAngle + m02 * sinAngle;
    matrix[0][2] = m00 * -sinAngle + m02 * cosAngle;

    matrix[1][0] = m10 * cosAngle + m12 * sinAngle;
    matrix[1][2] = m10 * -sinAngle + m12 * cosAngle;

    matrix[2][0] = m20 * cosAngle + m22 * sinAngle;
    matrix[2][2] = m20 * -sinAngle + m22 * cosAngle;

    matrix[3][0] = m30 * cosAngle + m32 * sinAngle;
    matrix[3][2] = m30 * -sinAngle + m32 * cosAngle;

    return *this;
}

Matrix4& Matrix4::rotateZ(float angle){
    float cosAngle = cosf(angle * DEG2RAD);
    float sinAngle = sinf(angle * DEG2RAD);

    float m00=matrix[0][0];
    float m01=matrix[0][1];

    float m10=matrix[1][0];
    float m11=matrix[1][1];

    float m20=matrix[2][0];
    float m21=matrix[2][1];

    float m30=matrix[3][0];
    float m31=matrix[3][1];

    matrix[0][0] = m00 * cosAngle + m01 * -sinAngle;
    matrix[0][1] = m00 * sinAngle + m01 * cosAngle;

    matrix[1][0] = m10 * cosAngle + m11 * -sinAngle;
    matrix[1][1] = m10 * sinAngle + m11 * cosAngle;

    matrix[2][0] = m20 * cosAngle + m21 * -sinAngle;
    matrix[2][1] = m20 * sinAngle + m21 * cosAngle;

    matrix[3][0] = m30 * cosAngle + m31 * -sinAngle;
    matrix[3][1] = m30 * sinAngle + m31 * cosAngle;

    return *this;
}

Matrix4& Matrix4::scale(float pScale){
    return scale(pScale,pScale,pScale);
}

Matrix4& Matrix4::scale(float xScale, float yScale, float zScale){
    matrix[0][0] *= xScale;
    matrix[0][1] *= yScale;
    matrix[0][2] *= zScale;

    matrix[1][0] *= xScale;
    matrix[1][1] *= yScale;
    matrix[1][2] *= zScale;

    matrix[2][0] *= xScale;
    matrix[2][1] *= yScale;
    matrix[2][2] *= zScale;

    matrix[3][0] *= xScale;
    matrix[3][1] *= yScale;
    matrix[3][2] *= zScale;

    return *this;
}

Matrix4& Matrix4::scale(const Vector3& scaleVector){
    return scale(scaleVector.x,scaleVector.y,scaleVector.z);
}

Matrix4& Matrix4::lookAt(float targetX, float targetY, float targetZ){
    return lookAt(Vector3(targetX,targetY,targetZ));
}

Matrix4& Matrix4::lookAt(float targetX, float targetY, float targetZ, float upX, float upY, float upZ){
    return lookAt(Vector3(targetX,targetY,targetZ),Vector3(upX,upY,upZ));
}

Matrix4& Matrix4::lookAt(const Vector3& target){
    Vector3 position = Vector3(matrix[3][0],matrix[3][1],matrix[3][2]);
    Vector3 forward = target - position;
    forward.normalize();
    Vector3 up,horizontal; //TODO left or right vector

    if(fabs(forward.x)<EPSILON && fabs(forward.z)<EPSILON){
        if(forward.y>0)up.set(0,0,-1);
        else up.set(0,0,1);
    }else{
        up.set(0,1,0); //precompute / assumption
    }

    horizontal = up.cross(forward);
    horizontal.normalize();

    up = forward.cross(horizontal);

    setColumn(0,horizontal);
    setColumn(1,up);
    setColumn(2,forward);

    return *this;
}

Matrix4& Matrix4::lookAt(const Vector3& target, const Vector3& up){
    Vector3 position = Vector3(matrix[3][0],matrix[3][1],matrix[3][2]);
    Vector3 forward = target - position;
    forward.normalize();

    Vector3 horizontal = up.cross(forward); //TODO left or right vector
    horizontal.normalize();

    setColumn(0,horizontal);
    setColumn(1,up);
    setColumn(2,forward);

    return *this;
}

Matrix4 Matrix4::operator+(const Matrix4 &rightMatrix) const{
    auto rMatrix = rightMatrix.matrix; //TODO clean up after getter change
    return Matrix4(
    matrix[0][0] + rMatrix[0][0],
    matrix[0][1] + rMatrix[0][1],
    matrix[0][2] + rMatrix[0][2],
    matrix[0][3] + rMatrix[0][3],

    matrix[1][0] + rMatrix[1][0],
    matrix[1][1] + rMatrix[1][1],
    matrix[1][2] + rMatrix[1][2],
    matrix[1][3] + rMatrix[1][3],

    matrix[2][0] + rMatrix[2][0],
    matrix[2][1] + rMatrix[2][1],
    matrix[2][2] + rMatrix[2][2],
    matrix[2][3] + rMatrix[2][3],

    matrix[3][0] + rMatrix[3][0],
    matrix[3][1] + rMatrix[3][1],
    matrix[3][2] + rMatrix[3][2],
    matrix[3][3] + rMatrix[3][3]
    );
}

Matrix4 Matrix4::operator-(const Matrix4& rightMatrix) const{
    auto rMatrix = rightMatrix.matrix;
    return Matrix4(
            matrix[0][0] - rMatrix[0][0],
            matrix[0][1] - rMatrix[0][1],
            matrix[0][2] - rMatrix[0][2],
            matrix[0][3] - rMatrix[0][3],

            matrix[1][0] - rMatrix[1][0],
            matrix[1][1] - rMatrix[1][1],
            matrix[1][2] - rMatrix[1][2],
            matrix[1][3] - rMatrix[1][3],

            matrix[2][0] - rMatrix[2][0],
            matrix[2][1] - rMatrix[2][1],
            matrix[2][2] - rMatrix[2][2],
            matrix[2][3] - rMatrix[2][3],

            matrix[3][0] - rMatrix[3][0],
            matrix[3][1] - rMatrix[3][1],
            matrix[3][2] - rMatrix[3][2],
            matrix[3][3] - rMatrix[3][3]
    );
}

Matrix4& Matrix4::operator+=(const Matrix4& rightMatrix){
    auto rMatrix = rightMatrix.matrix;
    matrix[0][0] += rMatrix[0][0];
    matrix[0][1] += rMatrix[0][1];
    matrix[0][2] += rMatrix[0][2];
    matrix[0][3] += rMatrix[0][3];

    matrix[1][0] += rMatrix[1][0];
    matrix[1][1] += rMatrix[1][1];
    matrix[1][2] += rMatrix[1][2];
    matrix[1][3] += rMatrix[1][3];

    matrix[2][0] += rMatrix[2][0];
    matrix[2][1] += rMatrix[2][1];
    matrix[2][2] += rMatrix[2][2];
    matrix[2][3] += rMatrix[2][3];

    matrix[3][0] += rMatrix[3][0];
    matrix[3][1] += rMatrix[3][1];
    matrix[3][2] += rMatrix[3][2];
    matrix[3][3] += rMatrix[3][3];
    return *this;
}

Matrix4& Matrix4::operator-=(const Matrix4& rightMatrix){
    auto rMatrix = rightMatrix.matrix;
    matrix[0][0] -= rMatrix[0][0];
    matrix[0][1] -= rMatrix[0][1];
    matrix[0][2] -= rMatrix[0][2];
    matrix[0][3] -= rMatrix[0][3];

    matrix[1][0] -= rMatrix[1][0];
    matrix[1][1] -= rMatrix[1][1];
    matrix[1][2] -= rMatrix[1][2];
    matrix[1][3] -= rMatrix[1][3];

    matrix[2][0] -= rMatrix[2][0];
    matrix[2][1] -= rMatrix[2][1];
    matrix[2][2] -= rMatrix[2][2];
    matrix[2][3] -= rMatrix[2][3];

    matrix[3][0] -= rMatrix[3][0];
    matrix[3][1] -= rMatrix[3][1];
    matrix[3][2] -= rMatrix[3][2];
    matrix[3][3] -= rMatrix[3][3];
    return *this;
}

Matrix4 Matrix4::operator*(const Matrix4& rightMatrix) const{
    auto rMatrix = rightMatrix.matrix;
    return Matrix4(
        matrix[0][0]*rMatrix[0][0] + matrix[1][0]*rMatrix[0][1] + matrix[2][0]*rMatrix[0][2] + matrix[3][0]*rMatrix[0][3],
        matrix[0][1]*rMatrix[0][0] + matrix[1][1]*rMatrix[0][1] + matrix[2][1]*rMatrix[0][2] + matrix[3][1]*rMatrix[0][3],
        matrix[0][2]*rMatrix[0][0] + matrix[1][2]*rMatrix[0][1] + matrix[2][2]*rMatrix[0][2] + matrix[3][2]*rMatrix[0][3],
        matrix[0][3]*rMatrix[0][0] + matrix[1][3]*rMatrix[0][1] + matrix[2][3]*rMatrix[0][2] + matrix[3][3]*rMatrix[0][3],

        matrix[0][0]*rMatrix[1][0] + matrix[1][0]*rMatrix[1][1] + matrix[2][0]*rMatrix[1][2] + matrix[3][0]*rMatrix[1][3],
        matrix[0][1]*rMatrix[1][0] + matrix[1][1]*rMatrix[1][1] + matrix[2][1]*rMatrix[1][2] + matrix[3][1]*rMatrix[1][3],
        matrix[0][2]*rMatrix[1][0] + matrix[1][2]*rMatrix[1][1] + matrix[2][2]*rMatrix[1][2] + matrix[3][2]*rMatrix[1][3],
        matrix[0][3]*rMatrix[1][0] + matrix[1][3]*rMatrix[1][1] + matrix[2][3]*rMatrix[1][2] + matrix[3][3]*rMatrix[1][3],

        matrix[0][0]*rMatrix[2][0] + matrix[1][0]*rMatrix[2][1] + matrix[2][0]*rMatrix[2][2] + matrix[3][0]*rMatrix[2][3],
        matrix[0][1]*rMatrix[2][0] + matrix[1][1]*rMatrix[2][1] + matrix[2][1]*rMatrix[2][2] + matrix[3][1]*rMatrix[2][3],
        matrix[0][2]*rMatrix[2][0] + matrix[1][2]*rMatrix[2][1] + matrix[2][2]*rMatrix[2][2] + matrix[3][2]*rMatrix[2][3],
        matrix[0][3]*rMatrix[2][0] + matrix[1][3]*rMatrix[2][1] + matrix[2][3]*rMatrix[2][2] + matrix[3][3]*rMatrix[2][3],

        matrix[0][0]*rMatrix[3][0] + matrix[1][0]*rMatrix[3][1] + matrix[2][0]*rMatrix[3][2] + matrix[3][0]*rMatrix[3][3],
        matrix[0][1]*rMatrix[3][0] + matrix[1][1]*rMatrix[3][1] + matrix[2][1]*rMatrix[3][2] + matrix[3][1]*rMatrix[3][3],
        matrix[0][2]*rMatrix[3][0] + matrix[1][2]*rMatrix[3][1] + matrix[2][2]*rMatrix[3][2] + matrix[3][2]*rMatrix[3][3],
        matrix[0][3]*rMatrix[3][0] + matrix[1][3]*rMatrix[3][1] + matrix[2][3]*rMatrix[3][2] + matrix[3][3]*rMatrix[3][3]
    );
}

Matrix4& Matrix4::operator*=(const Matrix4& rightMatrix){
    *this = *this * rightMatrix;
    return *this;
}

bool Matrix4::operator==(const Matrix4& rightMatrix) const{
    auto rMatrix = rightMatrix.matrix;
    return (matrix[0][0]==rMatrix[0][0]) &&
            (matrix[0][1]==rMatrix[0][1]) &&
            (matrix[0][2]==rMatrix[0][2]) &&
            (matrix[0][3]==rMatrix[0][3]) &&

            (matrix[1][0]==rMatrix[1][0]) &&
            (matrix[1][1]==rMatrix[1][1]) &&
            (matrix[1][2]==rMatrix[1][2]) &&
            (matrix[1][3]==rMatrix[1][3]) &&

            (matrix[2][0]==rMatrix[2][0]) &&
            (matrix[2][1]==rMatrix[2][1]) &&
            (matrix[2][2]==rMatrix[2][2]) &&
            (matrix[2][3]==rMatrix[2][3]) &&

            (matrix[3][0]==rMatrix[3][0]) &&
            (matrix[3][1]==rMatrix[3][1]) &&
            (matrix[3][2]==rMatrix[3][2]) &&
            (matrix[3][3]==rMatrix[3][3]);
}

bool Matrix4::operator!=(const Matrix4& rightMatrix) const{
    auto rMatrix = rightMatrix.matrix;
    return (matrix[0][0]!=rMatrix[0][0]) ||
           (matrix[0][1]!=rMatrix[0][1]) ||
           (matrix[0][2]!=rMatrix[0][2]) ||
           (matrix[0][3]!=rMatrix[0][3]) ||

           (matrix[1][0]!=rMatrix[1][0]) ||
           (matrix[1][1]!=rMatrix[1][1]) ||
           (matrix[1][2]!=rMatrix[1][2]) ||
           (matrix[1][3]!=rMatrix[1][3]) ||

           (matrix[2][0]!=rMatrix[2][0]) ||
           (matrix[2][1]!=rMatrix[2][1]) ||
           (matrix[2][2]!=rMatrix[2][2]) ||
           (matrix[2][3]!=rMatrix[2][3]) ||

           (matrix[3][0]!=rMatrix[3][0]) ||
           (matrix[3][1]!=rMatrix[3][1]) ||
           (matrix[3][2]!=rMatrix[3][2]) ||
           (matrix[3][3]!=rMatrix[3][3]);
}

Vector4 Matrix4::operator*(const Vector4& rightVector) const{
    return Vector4(
        matrix[0][0]*rightVector.x + matrix[1][0]*rightVector.y + matrix[2][0]*rightVector.z + matrix[3][0]*rightVector.w,
        matrix[0][1]*rightVector.x + matrix[1][1]*rightVector.y + matrix[2][1]*rightVector.z + matrix[3][1]*rightVector.w,
        matrix[0][2]*rightVector.x + matrix[1][2]*rightVector.y + matrix[2][2]*rightVector.z + matrix[3][2]*rightVector.w,
        matrix[0][3]*rightVector.x + matrix[1][3]*rightVector.y + matrix[2][3]*rightVector.z + matrix[3][3]*rightVector.w
    );
}

Vector3 Matrix4::operator*(const Vector3& rightVector) const{
    return Vector3(
        matrix[0][0]*rightVector.x + matrix[1][0]*rightVector.y + matrix[2][0]*rightVector.z,
        matrix[0][1]*rightVector.x + matrix[1][1]*rightVector.y + matrix[2][1]*rightVector.z,
        matrix[0][2]*rightVector.x + matrix[1][2]*rightVector.y + matrix[2][2]*rightVector.z
    );
}


Matrix4 operator-(Matrix4& rightMatrix){
    Matrix4 negMat = Matrix4();
    negMat.setRow(0,Vector4(rightMatrix.matrix[0][0],rightMatrix.matrix[0][1],rightMatrix.matrix[0][2],rightMatrix.matrix[0][3]));
    negMat.setRow(1,Vector4(rightMatrix.matrix[1][0],rightMatrix.matrix[1][1],rightMatrix.matrix[1][2],rightMatrix.matrix[1][3]));
    negMat.setRow(2,Vector4(rightMatrix.matrix[2][0],rightMatrix.matrix[2][1],rightMatrix.matrix[2][2],rightMatrix.matrix[2][3]));
    negMat.setRow(3,Vector4(rightMatrix.matrix[3][0],rightMatrix.matrix[3][1],rightMatrix.matrix[3][2],rightMatrix.matrix[3][3]));

    return negMat;
}

Matrix4 operator*(float scalar, const Matrix4& rightMatrix){
    auto rMatrix = rightMatrix.matrix;
    return Matrix4(
        scalar*rMatrix[0][0],
        scalar*rMatrix[0][1],
        scalar*rMatrix[0][2],
        scalar*rMatrix[0][3],

        scalar*rMatrix[1][0],
        scalar*rMatrix[1][1],
        scalar*rMatrix[1][2],
        scalar*rMatrix[1][3],

        scalar*rMatrix[2][0],
        scalar*rMatrix[2][1],
        scalar*rMatrix[2][2],
        scalar*rMatrix[2][3],

        scalar*rMatrix[3][0],
        scalar*rMatrix[3][1],
        scalar*rMatrix[3][2],
        scalar*rMatrix[3][3]
    );
}

Vector3 operator*(const Vector3& leftVector, const Matrix4& rightMatrix){
    auto rMatrix = rightMatrix.matrix;
    return Vector3(
            rMatrix[0][0]*leftVector.x + rMatrix[1][0]*leftVector.y + rMatrix[2][0]*leftVector.z,
            rMatrix[0][1]*leftVector.x + rMatrix[1][1]*leftVector.y + rMatrix[2][1]*leftVector.z,
            rMatrix[0][2]*leftVector.x + rMatrix[1][2]*leftVector.y + rMatrix[2][2]*leftVector.z
    );
}

Vector4 operator*(const Vector4& leftVector, const Matrix4& rightMatrix){
    auto rMatrix = rightMatrix.matrix;
    return Vector4(
            rMatrix[0][0]*leftVector.x + rMatrix[1][0]*leftVector.y + rMatrix[2][0]*leftVector.z + rMatrix[3][0]*leftVector.w,
            rMatrix[0][1]*leftVector.x + rMatrix[1][1]*leftVector.y + rMatrix[2][1]*leftVector.z + rMatrix[3][1]*leftVector.w,
            rMatrix[0][2]*leftVector.x + rMatrix[1][2]*leftVector.y + rMatrix[2][2]*leftVector.z + rMatrix[3][2]*leftVector.w,
            rMatrix[0][2]*leftVector.x + rMatrix[1][2]*leftVector.y + rMatrix[2][2]*leftVector.z + rMatrix[3][3]*leftVector.w
    );
}
std::ostream& operator<<(std::ostream& os, const Matrix4& rightMatrix){
    auto rMatrix = rightMatrix.matrix;
    os<<std::fixed<<std::setprecision(5);
    os<<"["<<std::setw(10)<<rMatrix[0][0]<<"  "<<"["<<std::setw(10)<<rMatrix[0][1]<<"  "<<"["<<std::setw(10)<<rMatrix[0][2]<<"  "<<"["<<std::setw(10)<<rMatrix[0][3]<<"]\n"
        <<"["<<std::setw(10)<<rMatrix[1][0]<<"  "<<"["<<std::setw(10)<<rMatrix[1][1]<<"  "<<"["<<std::setw(10)<<rMatrix[1][2]<<"  "<<"["<<std::setw(10)<<rMatrix[1][3]<<"]\n"
        <<"["<<std::setw(10)<<rMatrix[2][0]<<"  "<<"["<<std::setw(10)<<rMatrix[2][1]<<"  "<<"["<<std::setw(10)<<rMatrix[2][2]<<"  "<<"["<<std::setw(10)<<rMatrix[2][3]<<"]\n"
        <<"["<<std::setw(10)<<rMatrix[3][0]<<"  "<<"["<<std::setw(10)<<rMatrix[3][1]<<"  "<<"["<<std::setw(10)<<rMatrix[3][2]<<"  "<<"["<<std::setw(10)<<rMatrix[3][3]<<"]\n";
    os<<std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);
    return os;
}

Matrix4 Matrix4::createPerspectiveFOV(float fovY, float width, float height, float near, float far){
    float yScale = 1.f/tanf(fovY / 2.0f);
    float xScale = yScale * height / width;
    float m22,m32;
    m22 = float(far) / (float(far)-float(near));
    m32 = -float(near)*float(far)/(float(far)-float(near));
    float temp[4][4] = {{xScale,0,0,0},{0,yScale,0,0},{0,0,m22,1},{0,0,m32,0}};
    /*{
            { xScale, 0.0f, 0.0f, 0.0f },
            { 0.0f, yScale, 0.0f, 0.0f },
            { 0.0f, 0.0f, far/(far-near), 1.0f },
            { 0.0f, 0.0f, -near * far / (far - near), 0.0f }
    };*/
    return Matrix4(temp);
}