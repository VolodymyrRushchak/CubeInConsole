#ifndef BLA_H
#define BLA_H

class Point {

public:
	double x, y, z;

	Point() : x{ 0 }, y{ 0 }, z{ 0 }
	{
	}

	Point(double X, double Y, double Z) : x{ X }, y{ Y }, z{ Z }
	{
	}

	Point operator-()
	{
		Point newPoint(-this->x, -this->y, -this->z);
		return newPoint;
	}

};



class Sphere {

public:
	int radius;
	Point& center;

	Sphere(int R, Point& C) : radius{ R }, center{ C }
	{
	}

};


class Plane {

public:
	double A, B, C, D;    //these are coefficients for plane equation: Ax + By + Cz + D = 0
	Point p0, p1;         //these are coordinates of the diagonal points 
						  //(they are used when determining whether a point belongs to the face of a cube)

	Plane() : p0(Point(0, 0, 0)), p1(Point(0, 0, 0))
	{
		A = 0;
		B = 0;
		C = 0;
		D = 0;
	}

	Plane(Point& p1, Point& p2, Point& p3);

};


class Cube {

public:
	Plane planes[6];

	Cube(double edgeSize, double angleXY, double angleXZ);

};

#endif
