#ifndef _color_H
#define _color_H

class color {
	double red, green, blue;
public:
	color();
	color(double, double, double);

	double getRed(); 
	double getGreen();
	double getBlue(); 
	void setRed(double x);
	void setGreen(double x);
	void setBlue(double x);
	void setBlack();
	void setWhite();

	color multByScalar(double scalar);
	color clip();
	color operator* (color c);
	color& operator*= (color c);
	color operator+ (color c);
	color& operator+= (color c);
};


#endif