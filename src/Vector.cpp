#include "Vector.hpp"
Vector::Vector(GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
	element[0] = x;
	element[1] = y;
	element[2] = z;
	element[3] = w;
}

void Vector::update(GLfloat x, GLfloat y, GLfloat z, GLfloat angle) {
	Matrix t = Matrix::rotate(angle, x, y, z);
	update(t);
}

void Vector::update(Matrix t) {
	GLfloat updateElement[4];
	for (int i = 0; i < 4; i++) {
		updateElement[i] = t.data()[0 + i] * element[0] + t.data()[4 + i] * element[1] + t.data()[8 + i] * element[2] + t.data()[12 + i] * element[3];
	}
	for (int i = 0; i < 4; i++) element[i] = updateElement[i];
}

GLfloat* Vector::get() {
	return element;
}