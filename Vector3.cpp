#include "Base.hpp"
#include "Vector3.hpp"

inline Vec3& Vec3::operator+=(const Vec3& vec) {
	x += vec.x; y += vec.y; z += vec.z;
	return (*this);
}
inline Vec3& Vec3::operator-=(const Vec3& vec) {
	x -= vec.x; y -= vec.y; z -= vec.z;
	return (*this);
}


inline Vec3& Vec3::operator*=(const ld& a) {
	(*this).x *= a; (*this).y *= a; (*this).z *= a;
	return (*this);
}
inline Vec3& Vec3::operator/=(const ld& a) {
	if (a > 0) (*this).x /= a, (*this).y /= a, (*this).z /= a;
	else (*this).x = INF, (*this).y = INF, (*this).z = INF;
	return (*this);
}
inline Vec3& Vec3::operator%=(const ll& a) {
	if (a > 0) (*this).x = ((ll)(*this).x) % a,
		(*this).y = ((ll)(*this).y) % a,
		(*this).z = ((ll)(*this).z) % a;
	else (*this).x = INF, (*this).y = INF, (*this).z = INF;
	return (*this);
}


inline bool Vec3::operator==(const Vec3& vec) {
	return x == vec.x && y == vec.y && z == vec.z;
}
inline bool Vec3::operator!=(const Vec3& vec) {
	return (*this) != vec;
}


inline Vec3 operator+(const Vec3& a, const Vec3& b) {
	Vec3 vec = a; vec += b;
	return vec;
}
inline Vec3 operator-(const Vec3& a, const Vec3& b) {
	Vec3 vec = a; vec -= b;
	return vec;
}
inline ld operator*(const Vec3& a, const Vec3& b) {
	ld num = a.x * b.x + a.y * b.y + a.z * b.z;
	return num;
}
inline Vec3 operator%(const Vec3& a, const Vec3& b) {
	Vec3 vec;
	vec.x = a.y * b.z - a.z * b.y;
	vec.y = a.z * b.x - a.x * b.z;
	vec.z = a.x * b.y - a.y * b.x;
	return vec;
}


inline Vec3 operator*(const Vec3& vec, const ld& a) {
	Vec3 b = vec;
	b *= a;
	return b;
}
inline Vec3 operator/(const Vec3& vec, const ld& a) {
	Vec3 b = vec;
	b /= a;
	return b;
}
inline Vec3 operator%(const Vec3& vec, const ll& a) {
	Vec3 b = vec;
	b %= a;
	return b;
}
inline Vec3 operator*(const ld& a, const Vec3& vec) {
	return vec * a;
}
inline Vec3 operator/(const ld& a, const Vec3& vec) {
	return vec / a;
}
inline Vec3 operator%(const ll& a, const Vec3& vec) {
	return vec % a;
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