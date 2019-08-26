#include "Base.hpp"
#include "Matrix.hpp"

Matrix::Matrix(const GLfloat* a) {
	std::copy(a, a + 16, matrix);
}

Matrix::Matrix(Player player) {
	GLfloat look[] = {*player.getPosition() + *player.getDirection(), *(player.getPosition() + 1) + *(player.getDirection() + 1), *(player.getPosition() + 2) + *(player.getDirection() + 2)};

	*this = lookat(*player.getPosition(), *(player.getPosition() + 1) + 2.0f, *(player.getPosition() + 2), *player.getPosition() + *player.getDirection(), *(player.getPosition() + 1) + *(player.getDirection() + 1),
	    *(player.getPosition() + 2) + *(player.getDirection() + 2), 0.0f, 1.0f, 0.0f);
}

const GLfloat* Matrix::data() const {
	return matrix;
}

void Matrix::getNormalMatrix(GLfloat* m) const {
	m[0] = matrix[5] * matrix[10] - matrix[6] * matrix[9];
	m[1] = matrix[6] * matrix[8] - matrix[4] * matrix[10];
	m[2] = matrix[4] * matrix[9] - matrix[5] * matrix[8];
	m[3] = matrix[9] * matrix[2] - matrix[10] * matrix[1];
	m[4] = matrix[10] * matrix[0] - matrix[8] * matrix[2];
	m[5] = matrix[8] * matrix[1] - matrix[9] * matrix[0];
	m[6] = matrix[1] * matrix[6] - matrix[2] * matrix[5];
	m[7] = matrix[2] * matrix[4] - matrix[0] * matrix[6];
	m[8] = matrix[0] * matrix[5] - matrix[1] * matrix[4];
}

void Matrix::loadIdentity() {
	std::fill(matrix, matrix + 16, 0.0f);
	matrix[0] = matrix[5] = matrix[10] = matrix[15] = 1.0f;
}

Matrix Matrix::identity() {
	Matrix t;
	t.loadIdentity();
	return t;
}

Matrix Matrix::translate(GLfloat x, GLfloat y, GLfloat z) {
	Matrix t = identity();

	t.matrix[12] = x;
	t.matrix[13] = y;
	t.matrix[14] = z;

	return t;
}

Matrix Matrix::scale(GLfloat x, GLfloat y, GLfloat z) {
	Matrix t = identity();

	t.matrix[0] = x;
	t.matrix[5] = y;
	t.matrix[10] = z;

	return t;
}

Matrix Matrix::rotate(GLfloat a, GLfloat x, GLfloat y, GLfloat z) {
	Matrix t;
	const GLfloat d(sqrt(x * x + y * y + z * z));

	if (d > 0.0f) {
		const GLfloat l(x / d), m(y / d), n(z / d);
		const GLfloat l2(l * l), m2(m * m), n2(n * n);
		const GLfloat lm(l * m), mn(m * n), nl(n * l);
		const GLfloat c(cos(a)), c1(1.0f - c), s(sin(a));

		t.loadIdentity();
		t.matrix[0] = (1.0f - l2) * c + l2;
		t.matrix[1] = lm * c1 + n * s;
		t.matrix[2] = nl * c1 - m * s;
		t.matrix[4] = lm * c1 - n * s;
		t.matrix[5] = (1.0f - m2) * c + m2;
		t.matrix[6] = mn * c1 + l * s;
		t.matrix[8] = nl * c1 + m * s;
		t.matrix[9] = mn * c1 - l * s;
		t.matrix[10] = (1.0f - n2) * c + n2;
	}

	return t;
}

Matrix Matrix::rotateX(GLfloat s) {
	Matrix t = identity();

	t.matrix[5] = cos(s);
	t.matrix[6] = -sin(s);
	t.matrix[9] = sin(s);
	t.matrix[10] = cos(s);

	return t;
}

Matrix Matrix::operator*(const Matrix& m) const {
	Matrix t;

	for (int i = 0; i < 16; i++) {
		const int j(i & 3), k(i & ~3);

		t.matrix[i] = matrix[0 + j] * m.matrix[k + 0] + matrix[4 + j] * m.matrix[k + 1] + matrix[8 + j] * m.matrix[k + 2] + matrix[12 + j] * m.matrix[k + 3];
	}

	return t;
}

Matrix Matrix::lookat(GLfloat ex, GLfloat ey, GLfloat ez, //視点の座標
    GLfloat gx, GLfloat gy, GLfloat gz,                   //目標点の座標
    GLfloat ux, GLfloat uy, GLfloat uz) {                 //上方向のベクトル
	const Matrix tv(translate(-ex, -ey, -ez));

	const GLfloat tx(ex - gx);
	const GLfloat ty(ey - gy);
	const GLfloat tz(ez - gz);

	const GLfloat rx(uy * tz - uz * ty);
	const GLfloat ry(uz * tx - ux * tz);
	const GLfloat rz(ux * ty - uy * tx);

	const GLfloat sx(ty * rz - tz * ry);
	const GLfloat sy(tz * rx - tx * rz);
	const GLfloat sz(tx * ry - ty * rx);

	const GLfloat s2(sx * sx + sy * sy + gz * gz);
	if (s2 == 0.0f) return tv;

	Matrix rv = identity();

	const GLfloat r(sqrt(rx * rx + ry * ry + rz * rz));
	rv.matrix[0] = rx / r;
	rv.matrix[4] = ry / r;
	rv.matrix[8] = rz / r;

	const GLfloat s(sqrt(s2));
	rv.matrix[1] = sx / s;
	rv.matrix[5] = sy / s;
	rv.matrix[9] = sz / s;

	const GLfloat t(sqrt(tx * tx + ty * ty + tz * tz));
	rv.matrix[2] = tx / t;
	rv.matrix[6] = ty / t;
	rv.matrix[10] = tz / t;

	return rv * tv;
}

Matrix Matrix::orthogonal(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar) { //直交投影変換行列の生成
	Matrix t;
	const GLfloat dx(right - left);
	const GLfloat dy(top - bottom);
	const GLfloat dz(zFar - zNear);

	if (dx != 0.0f && dy != 0.0f && dz != 0.0f) {
		t.loadIdentity();
		t.matrix[0] = 2.0f / dx;
		t.matrix[5] = 2.0f / dy;
		t.matrix[10] = -2.0f / dz;
		t.matrix[12] = -(right + left) / dx;
		t.matrix[13] = -(top + bottom) / dy;
		t.matrix[14] = -(zFar - zNear) / dz;
	}

	return t;
}

Matrix Matrix::frustum(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar) { //透視投影変換行列の生成
	Matrix t;
	const GLfloat dx(right - left);
	const GLfloat dy(top - bottom);
	const GLfloat dz(zFar - zNear);

	if (dx != 0.0f && dy != 0.0f && dz != 0.0f) {
		t.loadIdentity();
		t.matrix[0] = 2.0f * zNear / dx;
		t.matrix[5] = 2.0f * zNear / dy;
		t.matrix[8] = (right + left) / dx;
		t.matrix[9] = (top + bottom) / dy;
		t.matrix[10] = -(zFar + zNear) / dz;
		t.matrix[11] = -1.0f;
		t.matrix[14] = -2.0f * zFar * zNear / dz;
		t.matrix[15] = 0.0f;
	}

	return t;
}

Matrix Matrix::perspective(GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar) { //画角と縦横比に基づく透視投影変換行列
	Matrix t;
	const GLfloat dz(zFar - zNear);

	if (dz != 0.0f) {
		t.loadIdentity();
		t.matrix[5] = 1.0f / tan(fovy * 0.5f);
		t.matrix[0] = t.matrix[5] / aspect;
		t.matrix[10] = -(zFar + zNear) / dz;
		t.matrix[11] = -1.0f;
		t.matrix[14] = -2.0f * zFar * zNear / dz;
		t.matrix[15] = 0.0f;
	}

	return t;
}
