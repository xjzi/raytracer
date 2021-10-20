#include <limits>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include "save.hpp"

struct Sphere {
	Vec3 center;
	float radius;

	Sphere(const Vec3 &c, const float &r) : center(c), radius(r) {}

	bool ray_intersect(const Vec3 &origin, const Vec3 &direction, float &t0) const {
		Vec3 L = center - origin;
		float tca = L * direction;
		float d2 = L * L -  tca * tca;
		if (d2 > radius * radius) return false;
		float thc = sqrtf(radius * radius - d2);
		t0 = tca - thc;
		float t1 = tca + thc;
		if (t0 < 0) t0 = t1;
		if (t0 < 0) return false;
		return true;
	}
};

Vec3 cast_ray(const Vec3 &origin, const Vec3 &direction, const Sphere &sphere) {
	float sphere_dist = std::numeric_limits<float>::max();
	if (!sphere.ray_intersect(origin, direction, sphere_dist)) {
		return Vec3(0, 0, 0);
	}
	return Vec3(0.5, 0.5, 0.5);
}

int main() {
	Matrix<Vec3> buf(1920, 1080);
	const int fov = M_PI/2;
	Sphere sphere(Vec3(-3, 0, -16), 2);

	for (size_t x = 0; x < buf.width; x++) {
		for (size_t y = 0; y < buf.height; y++) {
			Vec3 direction = Vec3(0, 0, -1);
			direction.x =  (2*(y + 0.5)/(float)buf.width  - 1)*tan(fov/2.)*buf.width/(float)buf.height;
            		direction.y = -(2*(x + 0.5)/(float)buf.height - 1)*tan(fov/2.);
			direction = direction.normalize();
			buf(x, y) = cast_ray(Vec3(0, 0, 0), direction, sphere);
		}
	}

	save(buf);

	return 0;
}
