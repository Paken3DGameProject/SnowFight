#include "Matrix.hpp"
#include "Base.hpp"

#include <iostream>

Matrix& Matrix::operator=(const Matrix& mat) {
	width = mat.width;
	height = mat.height;
	for (int i = 0; i < mat.height; i++) {
		for (int j = 0; j < mat.width; j++) {
			dat[i][j] = mat.dat[i][j];
		}
	}
	return (*this);
}
Matrix Matrix::operator-() {
	Matrix tmp(height, width);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			tmp.dat[i][j] = -dat[i][j];
		}
	}
	return tmp;
}
Matrix& Matrix::operator+=(const Matrix& mat) {
	if (height != mat.height || width != mat.width) {
		std::cerr << "Matrix operator\"+\": not match height and width" << std::endl;
		throw;
	}
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			dat[i][j] += mat.dat[i][j];
		}
	}
	return (*this);
}
Matrix& Matrix::operator-=(const Matrix& mat) {
	if (height != mat.height || width != mat.width) {
		std::cerr << "Matrix operator\"-\": not match height and width" << std::endl;
		throw;
	}
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			dat[i][j] -= mat.dat[i][j];
		}
	}
	return (*this);
}
Matrix& Matrix::operator*=(const ld& x) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			dat[i][j] *= x;
		}
	}
	return (*this);
}
Matrix& Matrix::operator/=(const ld& x) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (x == 0)
				dat[i][j] = dat[i][j] == 0 ? 0 : INF;
			else
				dat[i][j] /= x;
		}
	}
	return (*this);
}
Matrix& Matrix::operator%=(const ll& x) {
	// floor and take remainder
	if (x == 0) {
		std::cerr << "Matrix operator\"%%\": can't divide by zero" << std::endl;
		throw;
	}
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			dat[i][j] = ((long long)(dat[i][j])) % x;
		}
	}
	return (*this);
}
void Matrix::identity() {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < width; j++) {
			if (i == j)
				dat[i][j] = 1;
			else
				dat[i][j] = 0;
		}
	}
	return;
}
void Matrix::initialize() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			dat[i][j] = 0;
		}
	}
}
bool Matrix::operator==(const Matrix& mat) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (dat[i][j] != mat.dat[i][j]) {
				return false;
			}
		}
	}
	return true;
}
bool Matrix::operator!=(const Matrix& mat) {
	return !((*this) == mat);
}

[[deprecated]] Matrix mod_pow(const Matrix& matrix, long long n, long long Mod) {
	Matrix mat = matrix, cont(mat.height, mat.width);
	cont.identity();
	while (n > 0) {
		if (n & 1) {
			cont = cont * mat;
			cont %= Mod;
		}
		n >>= 1;
		mat = mat * mat;
		mat %= Mod;
	}
	return cont;
}