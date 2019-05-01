#include "Base.hpp"
#include "Vector3.hpp"

signed main() {
	Vec3 vec(1, 2, 3);
	vec = vec;
	cout << vec.length() << endl;
}