#ifndef MATRIX_H
#define MATRIX_H

class Matrix {
	typedef long double ld;
public:
	int h, w, size = 100;
	//height, width, size of matrix
	ld dat[100][100];
	Matrix(int h, int w) :h(h), w(w) {}
	Matrix() :h(0), w(0) {}
	Matrix& operator=(const Matrix& mat) {
		for (int i = 0; i < mat.h; i++) {
			for (int j = 0; j < mat.w; j++) {
				this->dat[i][j] = mat.dat[i][j];
			}
		}
		return (*this);
	}
	ld* operator[](int x) {
		if (x >= h) {
			cerr << "Matrix []: not match matrix size" << endl;
		}
		return dat[x];
	}
	Matrix operator+() { return *this; }
	Matrix operator-() {
		Matrix control(h, w);
		for (int i = 0; i < h; i++) { for (int j = 0; j < w; j++) { control[i][j] = -dat[i][j]; } }
		return control;
	}
	Matrix& operator+=(const Matrix &mat) {
		if (h != mat.h || w != mat.w) {
			cerr << "Matrix +: not match height and width" << endl;
		}
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				dat[i][j] += mat.dat[i][j];
			}
		}
		return (*this);
	}
	Matrix& operator-=(const Matrix& mat) {
		if (h != mat.h || w != mat.w) {
			cerr << "Matrix -: not match height and width" << endl;
		}
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				dat[i][j] -= mat.dat[i][j];
			}
		}
		return (*this);
	}
	Matrix& operator*=(const ld& x) {
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				dat[i][j] *= x;
			}
		}
		return (*this);
	}
	Matrix& operator/=(const ld& x) {
		if (x == 0) {
			cerr << "Matrix /: can't divide by zero" << endl;
		}
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				dat[i][j] /= x;
			}
		}
		return (*this);
	}
	Matrix& operator%=(const long long x) {
		//floor and take remainder
		if (x == 0) {
			cerr << "Matrix %: can't divide by zero" << endl;
		}
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				dat[i][j] = ((long long)(dat[i][j])) % x;
			}
		}
		return (*this);
	}
	void identity() {
		//make matrix to identity matrix of h*h
		h = h, w = h;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				dat[i][j] = 0;
			}
			(*this).dat[i][i] = 1;
		}
		return;
	}
	void initialize() {
		//initialize by 0
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				dat[i][j] = 0;
			}
		}
	}
	bool operator==(Matrix mat) {
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				if (dat[i][j] != mat.dat[i][j]) {
					return false;
				}
			}
		}
		return true;
	}
	bool operator!=(Matrix mat) {
		return !((*this) == mat);
	}
};
inline Matrix operator+(const Matrix& a, const Matrix& b) {
	Matrix c = a;
	return c += b;
}
inline Matrix operator-(const Matrix& a, const Matrix& b) {
	Matrix c = a;
	return c -= b;
}
inline Matrix operator*(const Matrix& a, const long double& b) {
	Matrix c = a;
	return c *= b;
}
inline Matrix operator*(const long double& b, const Matrix& a) {
	Matrix c = a;
	return c *= b;
}
inline Matrix operator/(const Matrix& a, const long double& b) {
	Matrix c = a;
	return c /= b;
}
inline Matrix operator/(const long double& b, const Matrix& a) {
	return a / b;
}
inline Matrix operator%(const Matrix& a, const long long& b) {
	Matrix c = a;
	c %= b;
	return c;
}
inline Matrix operator%(const long long& b, const Matrix& a) {
	return a % b;
}
inline Matrix operator*(const Matrix& a, const Matrix &b) {
	Matrix c(a.h, b.w);
	c.initialize();
	for (int i = 0; i < a.h; i++) {
		for (int j = 0; j < a.w; j++) {
			for (int z = 0; z < b.w; z++) {
				c[i][z] += a.dat[i][j] * b.dat[j][z];
				c[i][z] = (long long)(c[i][z]) % 1000000007;
			}
		}
	}
	return c;
}
Matrix mod_pow(const Matrix& matrix, long long n, long long Mod) {
	Matrix mat = matrix, cont(mat.h, mat.w);
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


class Vec3 {
	typedef long double ld;
public:
	ld x, y, z;
	Vec3(ld x, ld y, ld z) :x(x), y(y), z(z) {}
	Vec3() :x(0), y(0), z(0) {}
};

#endif