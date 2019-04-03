#pragma once

//
// ����͍s���\��Class�ł�
//
class Matrix{
  public:
	// �s��̍���
	int height;
	// �s��̉���
	int width;
	
    // ���̒l�ȏ�̍����A�����͎w��ł��܂���
	static const int MAX_MATRIX_SIZE = 4;

	// �s��̎��f�[�^([����][����])
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

    // �����Ɖ����������Ƃ��P�ʍs��ɂ��܂�
    void identity();
    // �S�Ă̗v�f���[���ɂ��܂�
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