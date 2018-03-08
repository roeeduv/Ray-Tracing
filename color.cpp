#include "color.h"

color::color() {
	red = 0;
	green = 0;
	blue = 0;
}

color::color(double r, double g, double b) {
	red = r;
	green = g;
	blue = b;
}

double color::getRed()
{
	return red;
}

double color::getGreen()
{
	return green;
}

double color::getBlue()
{
	return blue;
}

void color::setRed(double x) { red = x; }
void color::setGreen(double x) { green = x; }
void color::setBlue(double x) { blue = x; }
void color::setBlack() {
	red = 0;
	green = 0;
	blue = 0;
}
void color::setWhite() {
	red = 1;
	green = 1;
	blue = 1;
}

color color::multByScalar(double scalar) {
	return color(red*scalar, green*scalar, blue*scalar);
}

color color::clip() {
	double light = red + green + blue;
	double excesslight = light - 3;
	if (excesslight > 0) {
		red = red + excesslight*(red / light);
		green = green + excesslight*(green / light);
		blue = blue + excesslight*(blue / light);
	}
	if (red > 1) { red = 1; }
	if (green > 1) { green = 1; }
	if (blue > 1) { blue = 1; }
	if (red < 0) { red = 0; }
	if (green < 0) { green = 0; }
	if (blue < 0) { blue = 0; }

	return color(red, green, blue);
}

color color::operator* (color c) {
	return color(red*c.getRed(), green*c.getGreen(), blue*c.getBlue());
}
color& color::operator*= (color c)
{
	red *= c.getRed();
	green *= c.getGreen();
	blue *= c.getBlue();
	return (*this);
}
color color::operator+ (color c)
{
	color res;
	res.setRed(c.getRed() + red);
	res.setGreen(c.getGreen() + green);
	res.setBlue(c.getBlue() + blue);
	return res;
}
color& color::operator+= (color c)
{
	red += c.getRed();
	green += c.getGreen();
	blue += c.getBlue();
	return (*this);
}