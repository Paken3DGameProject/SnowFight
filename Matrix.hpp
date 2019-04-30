#pragma once

#include "Base.hpp"

//
// ����͍s���\��Class�ł�
//
class Matrix {
  public:
	// �s��̍s���A��
	int height, width;

	static const int MAX_MATRIX_SIZE = 4;

	// �s��̃f�[�^([�s][��])
	ld dat[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];

	Matrix(int height, int width) : height(height), width(width) {}
	Matrix() : height(0), width(0) {}

	Matrix& operator=(const Matrix& mat);
	Matrix operator+() {
		return (*this);
	}
	Matrix operator-();
	Matrix& operator+=(const Matrix& mat);
	Matrix& operator-=(const Matrix& mat);
	Matrix& operator*=(const ld& x);
	Matrix& operator/=(const ld& x);
	Matrix& operator%=(const ll& x);
	bool operator==(const Matrix& mat);
	bool operator!=(const Matrix& mat);

	// ��*�񐔂̒P�ʍs��ɂ���
	void identity();
	// �S�Ă̗v�f���[���ɂ���
	void initialize();
};

inline Matrix operator+(const Matrix& a, const Matrix& b) {
	Matrix c = a;
	return c += b;
}
inline Matrix operator-(const Matrix& a, const Matrix& b) {
	Matrix c = a;
	return c -= b;
}
inline Matrix operator*(const Matrix& a, const ld& b) {
	Matrix c = a;
	return c *= b;
}
inline Matrix operator/(const Matrix& a, const ld& b) {
	Matrix c = a;
	return c /= b;
}
inline Matrix operator%(const Matrix& a, const long long& b) {
	Matrix c = a;
	c %= b;
	return c;
}
inline Matrix operator*(const Matrix& a, const Matrix& b) {
	Matrix c(a.height, b.width);
	c.initialize();
	for (int i = 0; i < a.height; i++) {
		for (int j = 0; j < a.width; j++) {
			for (int z = 0; z < b.width; z++) {
				c.dat[i][z] += a.dat[i][j] * b.dat[j][z];
			}
		}
	}
	return c;
}

[[deprecated]] Matrix mod_pow(const Matrix& matrix, long long n, long long Mod);