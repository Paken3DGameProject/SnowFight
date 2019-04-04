#include "Base.hpp"
#include "Vector3.hpp"

Vec3& Vec3::operator+=(const Vec3& vec) {
	x += vec.x; y += vec.y; z += vec.z;
	return (*this);
}
Vec3& Vec3::operator-=(const Vec3& vec) {
	x -= vec.x; y -= vec.y; z -= vec.z;
	return (*this);
}
Vec3& Vec3::operator*=(const ld& a) {
	(*this).x *= a; (*this).y *= a; (*this).z *= a;
	return (*this);
}
Vec3& Vec3::operator/=(const ld& a) {
	if (a > 0) (*this).x /= a, (*this).y /= a, (*this).z /= a;
	else (*this).x = INF, (*this).y = INF, (*this).z = INF;
	return (*this);
}
Vec3& Vec3::operator%=(const ll& a) {
	if (a > 0) (*this).x = ((ll)(*this).x) % a,
		(*this).y = ((ll)(*this).y) % a,
		(*this).z = ((ll)(*this).z) % a;
	else (*this).x = INF, (*this).y = INF, (*this).z = INF;
	return (*this);
}
bool Vec3::operator==(const Vec3& vec) {
	return x == vec.x && y == vec.y && z == vec.z;
}
bool Vec3::operator!=(const Vec3& vec) {
	return (*this) != vec;
}

ld Vec3::length() {
	return sqrt(x * x + y * y + z * z);
}
void Vec3::normal() {
	ld t = this->length();
	x /= t; y /= t; z /= t;
}
ld radian(Vec3 &a,Vec3 & b) {
	ld tmp = a * b;
	return tmp / a.length() / b.length();
}