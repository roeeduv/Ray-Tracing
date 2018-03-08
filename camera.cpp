#include "Vector3f.h"
#include "camera.h"

camera::camera() {
	cameraPos = Vector3f(0, 0, 0);
	cameraDir = Vector3f(0, 0, 1);
	cameraRight = Vector3f(0, 0, 0);
	cameraDown = Vector3f(0, 0, 0);
}

camera::camera(Vector3f p, Vector3f dir, Vector3f r, Vector3f down) {
	cameraPos = p;
	cameraDir = dir;
	cameraRight = r;
	cameraDown = down;
}
Vector3f camera::getCamPos() { return cameraPos; }
Vector3f camera::getCamDir() { return cameraDir; }
Vector3f camera::getCamRight() { return cameraRight; }
Vector3f camera::getCamDown() { return cameraDown; }