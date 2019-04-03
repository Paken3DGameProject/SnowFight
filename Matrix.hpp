#pragma once

//
// これは行列を表すClassです
//
class Matrix{
  public:
	// 行列の高さ
	int height;
	// 行列の横幅
	int width;
	
    // この値以上の高さ、横幅は指定できません
	static const int MAX_MATRIX_SIZE = 4;

	// 行列の実データ([高さ][横幅])
    long double dat[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];

    Matrix(int height, int width);
    Matrix();

    Matrix &operator=(const Matrix &mat);
	Matrix operator+();
	Matrix operator-();
    Matrix &operator+=(const Matrix &mat);
    Matrix &operator-=(const Matrix &mat);
    Matrix &operator*=(const long double &x);
    Matrix &operator/=(const long double &x);
    Matrix &operator%=(const long long &x);
    bool operator==(const Matrix &mat);
    bool operator!=(const Matrix &mat);

    // 高さと横幅が同じとき単位行列にします
    void identity();
    // 全ての要素をゼロにします
    void initialize();
};

inline Matrix operator+(const Matrix& a, const Matrix& b);
inline Matrix operator-(const Matrix& a, const Matrix& b);
inline Matrix operator*(const Matrix& a, const long double& b);
inline Matrix operator/(const Matrix& a, const long double& b);
inline Matrix operator%(const Matrix& a, const long long& b);
inline Matrix operator*(const Matrix &a, const Matrix &b);

[[deprecated]]
Matrix mod_pow(const Matrix &matrix, long long n, long long Mod);