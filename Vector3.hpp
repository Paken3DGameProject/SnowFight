#pragma once
#include "Base.hpp"

class Vec3 {
  public:
	ld x, y, z;
	Vec3(ld x, ld y, ld z) : x(x), y(y), z(z) {}
	Vec3() : x(0), y(0), z(0) {}

	Vec3& operator+() {
		return (*this);
	};
	Vec3& operator-();

	Vec3& operator+=(const Vec3& vec);
	Vec3& operator-=(const Vec3& vec);

	Vec3& operator*=(const ld& a);
	Vec3& operator/=(const ld& a);
	Vec3& operator%=(const ll& a);

	bool operator==(const Vec3& vec);
	bool operator!=(const Vec3& vec);

	ld size();
	//ベクトルを正規化する
	void normal();
};

inline Vec3 operator+(const Vec3& a, const Vec3& b) {
	Vec3 vec = a;
	vec += b;
	return vec;
}
inline Vec3 operator-(const Vec3& a, const Vec3& b) {
	Vec3 vec = a;
	vec -= b;
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

//ベクトル2つの間の角度を返す
ld radian(Vec3& a, Vec3& b);
