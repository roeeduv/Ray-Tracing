#include "plane.h"


plane::plane() {
	normal = Vector3f(1, 0, 0);
	center = Vector3f(0, 0, 0);
	width = 32;
	length = 32;
	Ka = color(1, 1, 1);
	Kd = color(1, 1, 1);
	Ks = color(1, 1, 1);
	shine = 0;
}

plane::plane(Vector3f c, Vector3f n, double w, double l, color ka, color kd, color ks, double s) {
	center = c;
	normal = n;
	width = w;
	length = l;
	Ka = ka;
	Kd = kd;
	Ks = ks;
	shine = s;
}

double plane::findIntersection(ray ray){
	Vector3f v = ray.getDir();
	double a = Vector3f::dotProduct(normal, v);
	if (a == 0) {
		// ray is parallel to the plane
		return -1;
	}
	else {
		Vector3f P0 = ray.getOrigin();
		P0 += normal;
		P0.makeNegative();
		double b = Vector3f::dotProduct(P0, normal);
		return -1 * b / a;
	}
}
