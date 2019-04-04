#pragma once
#include "Base.hpp"

class Vec3 {
public:
	ld x, y, z;
	Vec3(ld x, ld y, ld z) :x(x), y(y), z(z) {}
	Vec3() :x(0), y(0), z(0) {}

	inline Vec3& operator+() { return (*this); };
	inline Vec3& operator-();

	inline Vec3& operator+=(const Vec3 & vec);
	inline Vec3& operator-=(const Vec3 & vec);

	inline Vec3& operator*=(const ld & a);
	inline Vec3& operator/=(const ld & a);
	inline Vec3& operator%=(const ll & a);

	inline bool operator==(const Vec3 & vec);
	inline bool operator!=(const Vec3 & vec);

	ld length();
	//ベクトルを正規化する
	void normal();
};
inline Vec3 operator+(const Vec3& a, const Vec3& b);
inline Vec3 operator-(const Vec3& a, const Vec3& b);
inline ld operator*(const Vec3& a, const Vec3& b);
inline Vec3 operator%(const Vec3& a, const Vec3& b);

inline Vec3 operator*(const Vec3& vec, const ld& a);
inline Vec3 operator/(const Vec3& vec, const ld& a);
inline Vec3 operator%(const Vec3& vec, const ll& a);
inline Vec3 operator*(const ld& a, const Vec3& vec);
inline Vec3 operator/(const ld& a, const Vec3& vec);
inline Vec3 operator%(const ll& a, const Vec3& vec);

//ベクトル2つの間の角度を返す
ld radian(Vec3& a, Vec3& b);