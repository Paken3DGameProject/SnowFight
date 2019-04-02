#include <Matrix.hpp>
#include <iostream>
typedef long double ld;
Matrix::Matrix(int h, int w) : h(h), w(w){}
Matrix::Matrix():Matrix(0,0){}
Matrix& Matrix::operator=(const Matrix &mat){
	for (int i = 0; i < mat.h; i++){
		for (int j = 0; j < mat.w; j++){
			this->dat[i][j] = mat.dat[i][j];
		}
	}
	return (*this);
}
ld* Matrix::operator[](int x){
	if (x >= h) {
		std::cerr << "Matrix []: not match matrix size" << std::endl;
	}
	return dat[x];
}
Matrix Matrix::operator+() { 
	return *this; 
}
Matrix Matrix::operator-(){
	Matrix control(h, w);
	for (int i = 0; i < h; i++) { 
		for (int j = 0; j < w; j++) { 
			control[i][j] = -dat[i][j]; 
		} 
	}
	return control;
}
Matrix& Matrix::operator+=(const Matrix &mat){
	if (h != mat.h || w != mat.w){
		std::cerr << "Matrix +: not match height and width" << std::endl;
	}
	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			dat[i][j] += mat.dat[i][j];
		}
	}
	return (*this);
}
Matrix& Matrix::operator-=(const Matrix &mat){
	if (h != mat.h || w != mat.w){
		std::cerr << "Matrix -: not match height and width" << std::endl;
	}
	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			dat[i][j] -= mat.dat[i][j];
		}
	}
	return (*this);
}
Matrix& Matrix::operator*=(const ld &x){
	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			dat[i][j] *= x;
		}
	}
	return (*this);
}
Matrix& Matrix::operator/=(const ld& x) {
	if (x == 0) {
		std::cerr << "Matrix /: can't divide by zero" << std::endl;
	}
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			dat[i][j] /= x;
		}
	}
	return (*this);
}
Matrix& Matrix::operator%=(const long long x) {
	//floor and take remainder
	if (x == 0) {
		std::cerr << "Matrix %%: can't divide by zero" << std::endl;
	}
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			dat[i][j] = ((long long)(dat[i][j])) % x;
		}
	}
	return (*this);
}
void Matrix::identity() {
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
void Matrix::initialize(){
	//initialize by 0
	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			dat[i][j] = 0;
		}
	}
}
bool Matrix::operator==(Matrix mat) {
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (dat[i][j] != mat.dat[i][j]) {
				return false;
			}
		}
	}
	return true;
}
bool Matrix::operator!=(Matrix mat) {
	return !((*this) == mat);
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
Vec3::Vec3(ld x, ld y, ld z) : x(x), y(y), z(z) {}
Vec3::Vec3():Vec3(0,0,0){}