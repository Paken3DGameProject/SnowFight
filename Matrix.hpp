#pragma once
class Matrix{
    typedef long double ld;

  public:
    int h, w, size = 100;
    //height, width, size of matrix
    ld dat[100][100];
    Matrix(int h, int w);
    Matrix();
    Matrix &operator=(const Matrix &mat);
    ld *operator[](int x);
    Matrix operator+();
    Matrix operator-();
    Matrix &operator+=(const Matrix &mat);
    Matrix &operator-=(const Matrix &mat);
    Matrix &operator*=(const ld &x);
    Matrix &operator/=(const ld &x);
    Matrix &operator%=(const long long x);
    void identity();
    void initialize();
    bool operator==(Matrix mat);
    bool operator!=(Matrix mat);
};
inline Matrix operator+(const Matrix &a, const Matrix &b){
    Matrix c = a;
    return c += b;
}
inline Matrix operator-(const Matrix &a, const Matrix &b){
    Matrix c = a;
    return c -= b;
}
inline Matrix operator*(const Matrix &a, const long double &b){
    Matrix c = a;
    return c *= b;
}
inline Matrix operator*(const long double &b, const Matrix &a){
    Matrix c = a;
    return c *= b;
}
inline Matrix operator/(const Matrix &a, const long double &b){
    Matrix c = a;
    return c /= b;
}
inline Matrix operator/(const long double &b, const Matrix &a){
    return a / b;
}
inline Matrix operator%(const Matrix &a, const long long &b){
    Matrix c = a;
    c %= b;
    return c;
}
inline Matrix operator%(const long long &b, const Matrix &a){
    return a % b;
}
inline Matrix operator*(const Matrix &a, const Matrix &b){
    Matrix c(a.h, b.w);
    c.initialize();
    for (int i = 0; i < a.h; i++){
        for (int j = 0; j < a.w; j++){
            for (int z = 0; z < b.w; z++){
                c[i][z] += a.dat[i][j] * b.dat[j][z];
                c[i][z] = (long long)(c[i][z]) % 1000000007;
            }
        }
    }
    return c;
}
Matrix mod_pow(const Matrix &matrix, long long n, long long Mod);

class Vec3{
    typedef long double ld;

  public:
    ld x, y, z;
    Vec3(ld x, ld y, ld z);
    Vec3();
};
