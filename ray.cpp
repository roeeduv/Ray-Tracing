#include "ray.h"

ray::ray(Vector3f o, Vector3f d) {
	origin = o;
	dir = d;
}
ray::ray() {
	origin = Vector3f(0, 0, 0);
	dir = Vector3f(1, 0, 0);
}
Vector3f ray::getOrigin() { return origin; }
Vector3f ray::getDir() { return dir; }
