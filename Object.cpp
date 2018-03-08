#include "Object.h"


Object::Object(){}
double Object::findIntersection(ray r) { return 0; }
color Object::getKa() { return color(1, 1, 1); }
color Object::getKd() { return color(1, 1, 1); }
color Object::getKs() { return color(1, 1, 1); }
Vector3f Object::getCenter() { return Vector3f(0, 0, 0); }
Vector3f Object::getNormalAt(Vector3f v) { return Vector3f(0, 0, 0); }
bool Object::isPlane() { return false; }
double Object::getShine() { return 1; }

