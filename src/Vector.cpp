#include "Vector.hpp"
Vector::Vector(GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
	element[0] = x;
	element[1] = y;
	element[2] = z;
	element[3] = w;
<<<<<<< HEAD
	length = std::sqrt(x * x + y * y + z * z);
=======
>>>>>>> 83e6d7c3ec4a8970cf9db19579d3c0af09582f7b
}

void Vector::update(GLfloat x, GLfloat y, GLfloat z, GLfloat angle) {
	Matrix t = Matrix::rotate(angle, x, y, z);
	update(t);
}

void Vector::update(Matrix t) {
	GLfloat updateElement[4];
<<<<<<< HEAD

	for (int i = 0; i < 4; i++) {
		updateElement[i] = t.data()[0 + i] * element[0] + t.data()[4 + i] * element[1] + t.data()[8 + i] * element[2] + t.data()[12 + i] * element[3];
	}

	GLfloat updateLength = 0.0f;

	for (int i = 0; i < 3; i++) updateLength += updateElement[i] * updateElement[i];
	updateLength = std::sqrt(updateLength);
	for (int i = 0; i < 3; i++) updateElement[i] *= (length / updateLength);

=======
	for (int i = 0; i < 4; i++) {
		updateElement[i] = t.data()[0 + i] * element[0] + t.data()[4 + i] * element[1] + t.data()[8 + i] * element[2] + t.data()[12 + i] * element[3];
	}
>>>>>>> 83e6d7c3ec4a8970cf9db19579d3c0af09582f7b
	for (int i = 0; i < 4; i++) element[i] = updateElement[i];
}

GLfloat* Vector::get() {
	return element;
}