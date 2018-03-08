#ifndef _CAMERA_H
#define _CAMERA_H
#include "Vector3f.h"

class camera {

private:
	Vector3f cameraPos, cameraDir, cameraRight, cameraDown;

public:
	camera();
	camera(Vector3f, Vector3f, Vector3f, Vector3f);
	Vector3f getCamPos();
	Vector3f getCamDir();
	Vector3f getCamRight();
	Vector3f getCamDown();
};
#endif
