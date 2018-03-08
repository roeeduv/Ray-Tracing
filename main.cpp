#pragma warning( disable : 4996 ) 
#include "bitmap_image.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>      
#include <sstream>
#include <stdio.h>
#include <cmath>
#include <stdlib.h>
#include <vector>
#include "Vector3f.h"
#include "ray.h"
#include "camera.h"
#include "color.h"
#include "light.h"
#include "sphere.h"
#include "object.h"
#include "plane.h"

using namespace std;


int closestObject(vector<double> objIntersect) {
	// return the index of closest object
	int min;
	if (objIntersect.size() == 0)
		return -1;

	else if (objIntersect.size() == 1) {
		if (objIntersect.at(0) > 0)
			return 0;
		else
			return -1;
	}
	else {
		// otherwise there is more than one intersection
		// first find the maximum value

		double max = 0;
		for (size_t i = 0; i < objIntersect.size(); i++) {
			if (max < objIntersect.at(i)) {
				max = objIntersect.at(i);
			}
		}
		// then starting from the maximum value find the minimum positive value
		if (max > 0) {
			for (size_t i = 0; i < objIntersect.size(); i++) {
				if (objIntersect.at(i) > 0 && objIntersect.at(i) <= max) {
					max = objIntersect.at(i);
					min = i;
				}
			}
			return min;
		}
		else {
			// all the intersections were negative
			return -1;
		}
	}
}


color ambient;
vector<double> nums;
vector<string> items;
vector<int>amountPerLine;
const int MAX_CHARS_PER_LINE = 512;
const int MAX_TOKENS_PER_LINE = 50;
const char* const DELIMITER = " ";
const char* const DELIMITER2 = ",";
void parse(char * file) {
	string tok;
	ifstream fin;
	fin.open(file);
	if (!fin.good())
		cout << "cant open file" << endl;
	while (!fin.eof()) {
		// read an entire line into memory
		char buf[MAX_CHARS_PER_LINE];
		fin.getline(buf, MAX_CHARS_PER_LINE);
		// parse the line into blank-delimited tokens
		int n = 0; // a for-loop index
				   // array to store memory addresses of the tokens in buf
		const char* token[MAX_TOKENS_PER_LINE] = {}; // initialize to 0
		token[0] = strtok(buf, DELIMITER); // first token
		items.push_back(token[0]);
		if (token[0]) { // zero if line is blank
			for (n = 0; n < MAX_TOKENS_PER_LINE; n++) {
				token[n] = strtok(0, DELIMITER2); // subsequent tokens
				if (!token[n]) break; // no more tokens
			}
		}
		amountPerLine.push_back(n);
		for (int i = 0; i < n; i++)  // n = #of tokens
			nums.push_back(stof(token[i]));
	}
}


int isShadowRay(ray shadowRay, vector<Object*> sceneObjects, double disToLight) {
	int shadow = 1; // shadow=1 - is not shadowed , shadow=0 it's shadowed
	vector<double> shadowIntersect;
	for (size_t i = 0; i < sceneObjects.size(); i++)
		shadowIntersect.push_back(sceneObjects.at(i)->findIntersection(shadowRay));
	for (size_t i = 0; i < shadowIntersect.size(); i++) {
		if (shadowIntersect.at(i) <= disToLight)
			shadow = 0;
	}
	return shadow;
}

color difuseCol(color Kd, Vector3f N, Vector3f L) {

	double dot = Vector3f::dotProduct(N, L);
	color ans = Kd.multByScalar(dot);
	return ans;
}
color specularCol(color Ks, Vector3f V, Vector3f R, double n) {
	double dot = pow(Vector3f::dotProduct(R, V), n);
	color ans = Ks.multByScalar(dot);
	return ans;
}

color getTrueColor(vector<Object*> sceneObjects, Vector3f rayDir, Vector3f intersect, int closeObj,
	vector<light*> lightSources) {
	color trueColor, colKd, colKs;
	color colKa = sceneObjects.at(closeObj)->getKa();

	if (sceneObjects.at(closeObj)->isPlane()) {
		// checker pattern
		int square = (int)floor(intersect.p[0] + (int)floor(intersect.p[2]));
		if ((square % 2) == 0)
			trueColor.setBlack();
		else
			trueColor.setWhite();
		trueColor *= ambient;
		colKa.setBlack();
	}

	double n = sceneObjects.at(closeObj)->getShine();
	//Ka*Ia - Ambient
	colKa *= ambient;
	//N = intersection to normal
	Vector3f N = sceneObjects.at(closeObj)->getNormalAt(intersect);
	N.normalize();
	//V = Vector to viewer
	Vector3f V = rayDir;
	V.makeNegative();
	V.normalize();

	for (size_t i = 0; i < lightSources.size(); i++) {
		color tempCol(0, 0, 0);
		colKd = sceneObjects.at(closeObj)->getKd();
		colKs = sceneObjects.at(closeObj)->getKs();

		light *tempLight = (lightSources.at(i));
		//get light color
		color intensity = tempLight->getIntensity();
		//L= vector to light 
		Vector3f L = tempLight->getDirection();
		L.makeNegative();
		L.normalize();

		//Kd(N*Li)
		color diffuse = difuseCol(colKd, N, L);

		// Ks((V*Ri)^n)
		double dot = Vector3f::dotProduct(L, N);
		Vector3f R = L - (2 * N*dot);
		R.normalize();

		color spec = specularCol(colKs, V, R, n);

		tempCol += diffuse;
		tempCol += spec;

		//shadowRay
		Vector3f lDir = tempLight->getPosition() - intersect;
		lDir.normalize();
		double distToLight = lDir.getLength();
		ray shadowRay(intersect, lDir);

		int Si = isShadowRay(shadowRay, sceneObjects, distToLight);
		if (Si)
			cout << 0;


		//tempCol=tempCol.multByScalar(Si); 
		Vector3f L1 = L + intersect;
		L1.normalize();
		//Ii - source light intensity
		double cosin = Vector3f::dotProduct(L1, L*(-1));
		double cutOff = tempLight->getCutOff();

		intensity = intensity.multByScalar(cosin);
		tempCol *= intensity;


		trueColor += tempCol;
	}
	trueColor += colKa;


	return trueColor.clip();
}

int main(int argc, char *argv[]) {
	cout << "prepare to be amazed!\n" << endl;
	parse(argv[1]);
	int ind;
	Vector3f CAM(nums.at(0), nums.at(1), nums.at(2));
	Vector3f up(nums.at(3), nums.at(4), nums.at(5));
	int wid = nums.at(6);
	int Rx = nums.at(7);
	int Ry = nums.at(8);
	ambient = color(nums.at(9), nums.at(10), nums.at(11));
	ind = 12;

	Vector3f POV(0, 0, 0);
	Vector3f camDir(CAM.p[0] - POV.p[0], CAM.p[1] - POV.p[1], CAM.p[2] - POV.p[2]);
	camDir.normalize();

	Vector3f camRight = Vector3f::crossProduct(up, camDir);
	camRight.normalize();
	Vector3f camDown = Vector3f::crossProduct(camRight, camDir);
	camDown.makeNegative();
	camRight.makeNegative();
	camera sceneCamera(CAM, camDir, camRight, camDown);

	vector<light*> lightSources;
	size_t i = 1;
	string l, s, p;
	l = "light";
	s = "spher";
	p = "plane";
	while (items.at(i).compare(l) == 0) {
		Vector3f lightDir(nums.at(ind), nums.at(ind + 1), nums.at(ind + 2));
		ind = ind + 3;
		color lightCol(nums.at(ind), nums.at(ind + 1), nums.at(ind + 2));
		ind = ind + 3;

		if (amountPerLine.at(i) == 6) {
			light *L = new light(lightDir, lightCol);
			lightSources.push_back(L);
		}
		else {
			Vector3f lightPos(nums.at(ind), nums.at(ind + 1), nums.at(ind + 2));
			ind = ind + 3;
			float cutOff = nums.at(ind++);
			light *L = new light(lightDir, lightCol, lightPos, cutOff);
			lightSources.push_back(L);
		}
		i++;
	}

	vector<Object*> sceneObjects;
	while (items.at(i).compare(s) == 0) {
		Vector3f center(nums.at(ind), nums.at(ind + 1), nums.at(ind + 2));
		ind = ind + 3;
		double r = nums.at(ind++);
		color Ka(nums.at(ind), nums.at(ind + 1), nums.at(ind + 2));
		ind = ind + 3;
		color Kd(nums.at(ind), nums.at(ind + 1), nums.at(ind + 2));
		ind = ind + 3;
		color Ks(nums.at(ind), nums.at(ind + 1), nums.at(ind + 2));
		ind += 3;
		double shine = nums.at(ind++);

		sphere *sp = new sphere(center, r, Ka, Kd, Ks, shine);
		sceneObjects.push_back(dynamic_cast<Object*>(sp));
		i++;
	}

	while (i<items.size() && items.at(i).compare(p) == 0) {
		Vector3f center(nums.at(ind), nums.at(ind + 1), nums.at(ind + 2));
		ind += 3;
		Vector3f normal(nums.at(ind), nums.at(ind + 1), nums.at(ind + 2));
		ind += 3;
		double wid = nums.at(ind++);
		double len = nums.at(ind++);
		color Ka(nums.at(ind), nums.at(ind + 1), nums.at(ind + 2));
		ind += 3;
		color Kd(nums.at(ind), nums.at(ind + 1), nums.at(ind + 2));
		ind += 3;
		color Ks(nums.at(ind), nums.at(ind + 1), nums.at(ind + 2));
		ind += 3;
		double shine = nums.at(ind++);;
		plane *pl = new plane(center, normal, wid, len, Ka, Kd, Ks, shine);
		sceneObjects.push_back(dynamic_cast<Object*>(pl));
		i++;
	}

	

	double ratio = Rx / Ry;
	double xCord, yCord;

	bitmap_image image(Rx, Ry);
	image.clear();
	for (int i = 0; i < Ry; i++) {
		for (int j = 0; j < Rx; j++) {
			if (Rx < Ry) {
				xCord = ((i + 0.5) / Rx)*ratio - (((Rx - Ry) / Ry) / 2);
				yCord = ((Ry - j) + 0.5) / Ry;
			}
			else if (Ry < Rx) {
				xCord = (i + 0.5) / Rx;
				yCord = (((Ry - j) + 0.5) / Ry) / ratio - (((Ry - Rx) / Rx) / 2);
			}
			else {
				xCord = (i + 0.5) / Rx;
				yCord = (Ry - j + 0.5) / Ry;
			}

			Vector3f camRayOrig = sceneCamera.getCamPos();
			Vector3f camRayDir = camDir + (camRight*(xCord - 0.5) + (camDown*(yCord - 0.5)));
			camRayDir.normalize();

			ray camRay(sceneCamera.getCamPos(), camRayDir);

			vector<double> intersections;

			for (size_t i = 0; i < sceneObjects.size(); i++) {
				intersections.push_back(sceneObjects.at(i)->findIntersection(camRay));
			}
			int closeObj = closestObject(intersections);
			if (closeObj == -1) {
				rgb_t color;
				color.red = 0;
				color.green = 0;
				color.blue = 0;

				image.set_pixel(i, j, color);
			}
			else {
				Vector3f intersect = camRayOrig + (camRayDir*(intersections.at(closeObj)));
				color finalCol = getTrueColor(sceneObjects, camRayDir, intersect, closeObj, lightSources);
				rgb_t color;
				color.red = finalCol.getRed() * 255;
				color.green = finalCol.getGreen() * 255;
				color.blue = finalCol.getBlue() * 255;
				image.set_pixel(i, j, color);
			}
		}
	}

	image.save_image(argv[2]);

	return 0;
}

