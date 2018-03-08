#include "sphere.h"

sphere::sphere() {
	center = Vector3f(0, 0, 0);
	radius = 1;
	Ka = color(1, 1, 1);
	Kd = color(1, 1, 1);
	Ks = color(1, 1, 1);
	shine = 0;
}

sphere::sphere(Vector3f c, double r, color ka, color kd, color ks, double s) {
	center = c;
	radius = r;
	Ka = ka;
	Kd = kd;
	Ks = ks;
	shine = s;
}

double sphere::findIntersection(ray ray) {
	Vector3f rayOrigin = ray.getOrigin();
	double Ox, Oy, Oz, Dx, Dy, Dz, Sx, Sy, Sz, b, c, disc, root1, root2;
	Ox = rayOrigin.p[0];
	Oy = rayOrigin.p[1];
	Oz = rayOrigin.p[2];

	Vector3f rayDir = ray.getDir();
	Dx = rayDir.p[0];
	Dy = rayDir.p[1];
	Dz = rayDir.p[2];

	Sx = center.p[0];
	Sy = center.p[1];
	Sz = center.p[2];

	b = (2 * (Ox - Sx)*Dx) + (2 * (Oy - Sy)*Dy) + (2 * (Oz - Sz)*Dz);
	c = pow(Ox - Sx, 2) + pow(Oy - Sy, 2) + pow(Oz - Sz, 2) - (radius*radius);

	disc = b*b - 4 * c;

	if (disc > 0) {
		root1 = ((-1 * b - sqrt(disc)) / 2) - 0.000001;
		root2 = ((sqrt(disc) - b) / 2) - 0.000001;
		if (root1 > 0)
			return root1;
		else
			return root2;
	}
	else //ray missed
		return -1;
}


Vector3f sphere::getNormalAt(Vector3f v){
	Vector3f normal = v - center;
	normal.normalize();
	return normal;
}


