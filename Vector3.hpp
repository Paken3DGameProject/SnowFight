#pragma once
#include "Base.hpp"

class Vec3 {
public:
	ld x = 0, y = 0, z = 0;
	Vec3(ld x, ld y, ld z) :x(x), y(y), z(z) {}

	inline Vec3& operator+() { return (*this); };
	inline Vec3& operator-() { return Vec3(-x, -y, -z); };

	inline Vec3& operator+=(const Vec3 & vec);
	inline Vec3& operator-=(const Vec3 & vec);

	inline Vec3& operator*=(const ld & a);
	inline Vec3& operator/=(const ld & a);
	inline Vec3& operator%=(const ld & a);

	inline bool operator==(const Vec3 & vec);
	inline bool operator!=(const Vec3 & vec);

	ld length();
	void normal();
	ld radian(const Vec3 & vec);
};
inline Vec3 Vec3::operator+(const Vec3& a, const Vec3& b);
inline Vec3 Vec3::operator-(const Vec3& a, const Vec3& b);
inline ld Vec3::operator*(const Vec3& a, const Vec3& b);
inline Vec3 Vec3::operator%(const Vec3& a, const Vec3& b);
inline Vec3& operator%=(const Vec3& vec);

inline Vec3 Vec3::operator*(const Vec3& vec, const ld& a);
inline Vec3 Vec3::operator/(const Vec3& vec, const ld& a);
inline Vec3 Vec3::operator%(const Vec3& vec, const ld& a);
inline Vec3 Vec3::operator*(const ld& a, const Vec3& vec);
inline Vec3 Vec3::operator/(const ld& a, const Vec3& vec);
inline Vec3 Vec3::operator%(const ld& a, const Vec3& vec);