#include "MyMathClasses.h" 
#include <cmath>


Point crossProduct(Point vec1, Point vec2) {

	double x, y, z;

	x = vec1.y * vec2.z - vec2.y * vec1.z;
	y = -(vec1.x * vec2.z - vec2.x * vec1.z);
	z = vec1.x * vec2.y - vec2.x * vec1.y;

	Point crossProduct(x, y, z);
	return crossProduct;

}



double dotProduct(Point& vec1, Point& vec2)
{
	return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}



void rotate(Point& point, double angleXY, double angleXZ)
{
	double old_x = point.x;
	double old_y = point.y;
	double old_z = point.z;

	point.x = old_x * cos(angleXY) - old_y * sin(angleXY);
	point.y = old_x * sin(angleXY) + old_y * cos(angleXY);

	old_x = point.x;
	old_y = point.y;

	point.x = old_x * cos(angleXZ) - old_z * sin(angleXZ);
	point.z = old_x * sin(angleXZ) + old_z * cos(angleXZ);
}


double dist(double x1, double y1, double z1, double x2, double y2, double z2)
{
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2) + pow(z1 - z2, 2));
}



double Abs(Point& vec)
{
	return sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
}


bool isOnPlane(Point point, Plane plane)
{
	Point vecAB(plane.p1.x - plane.p0.x, plane.p1.y - plane.p0.y, plane.p1.z - plane.p0.z);
	Point vecAP(point.x - plane.p0.x, point.y - plane.p0.y, point.z - plane.p0.z);
	Point vecBP(point.x - plane.p1.x, point.y - plane.p1.y, point.z - plane.p1.z);

	Point cA = crossProduct(vecAP, vecAB);
	double dA = dotProduct(vecAP, vecAB);
	Point cB = -crossProduct(vecAB, vecBP);
	double dB = -dotProduct(vecAB, vecBP);

	if ((dA < 0) || (dB < 0)) return false;
	if ((dA < Abs(cA)) || (dB < Abs(cB))) return false;

	return true;
}



//to return the point of intersection and normal to the plane which this point belongs to,
//this function uses the parameters point and normal
//The word person means an observer
bool lineCubeIntersect(Cube& cube, Point dirVec, Point& person, Point& point, Point& normal)
{
	Point p(1000, 1000, 1000);
	bool isIntersect = false;

	double A, B, C, D, t, x, y, z;
	for (int i = 0; i < 6; ++i)
	{
		A = cube.planes[i].A;
		B = cube.planes[i].B;
		C = cube.planes[i].C;
		D = cube.planes[i].D;
		t = -(A * person.x + B * person.y + C * person.z + D) / (A * dirVec.x + B * dirVec.y + C * dirVec.z);
		x = dirVec.x * t + person.x;
		y = dirVec.y * t + person.y;
		z = dirVec.z * t + person.z;

		if (isOnPlane(Point(x, y, z), cube.planes[i]))
			if (dist(person.x, person.y, person.z, x, y, z) < dist(person.x, person.y, person.z, p.x, p.y, p.z))
			{
				p.x = x;
				p.y = y;
				p.z = z;
				normal.x = cube.planes[i].A;
				normal.y = cube.planes[i].B;
				normal.z = cube.planes[i].C;
				isIntersect = true;
			}
	}

	point = p;
	return isIntersect;

}



void rotate(Cube& cube, double angleXY, double angleXZ)
{
	Point point;
	for (int i = 0; i < 6; ++i)
	{
		point = Point(cube.planes[i].A, cube.planes[i].B, cube.planes[i].C);
		rotate(point, angleXY, angleXZ);
		cube.planes[i].A = point.x;
		cube.planes[i].B = point.y;
		cube.planes[i].C = point.z;
		rotate(cube.planes[i].p0, angleXY, angleXZ);
		rotate(cube.planes[i].p1, angleXY, angleXZ);
		cube.planes[i].D = -(cube.planes[i].A * cube.planes[i].p0.x + cube.planes[i].B * cube.planes[i].p0.y + cube.planes[i].C * cube.planes[i].p0.z);
	}
}


Plane::Plane(Point& p1, Point& p2, Point& p3) : p0{ p1 }, p1{ p3 }
{
	Point vec1(p2.x - p1.x, p2.y - p1.y, p2.z - p1.z);
	Point vec2(p3.x - p1.x, p3.y - p1.y, p3.z - p1.z);
	Point normal = crossProduct(vec1, vec2);
	A = normal.x;
	B = normal.y;
	C = normal.z;
	D = -(A * p1.x + B * p1.y + C * p1.z);
}


Cube::Cube(double edgeSize, double angleXY, double angleXZ)
{
	Point p1(edgeSize / 2, -edgeSize / 2, edgeSize / 2);
	Point p2(-edgeSize / 2, -edgeSize / 2, edgeSize / 2);
	Point p3(-edgeSize / 2, edgeSize / 2, edgeSize / 2);
	Point p4(edgeSize / 2, edgeSize / 2, edgeSize / 2);
	Point p5(edgeSize / 2, -edgeSize / 2, -edgeSize / 2);
	Point p6(-edgeSize / 2, -edgeSize / 2, -edgeSize / 2);
	Point p7(-edgeSize / 2, edgeSize / 2, -edgeSize / 2);
	Point p8(edgeSize / 2, edgeSize / 2, -edgeSize / 2);
	rotate(p1, angleXY, angleXZ);
	rotate(p2, angleXY, angleXZ);
	rotate(p3, angleXY, angleXZ);
	rotate(p4, angleXY, angleXZ);
	rotate(p5, angleXY, angleXZ);
	rotate(p6, angleXY, angleXZ);
	rotate(p7, angleXY, angleXZ);
	rotate(p8, angleXY, angleXZ);

	planes[0] = Plane(p1, p2, p3);
	planes[1] = Plane(p5, p8, p7);
	planes[2] = Plane(p1, p5, p6);
	planes[3] = Plane(p2, p6, p7);
	planes[4] = Plane(p3, p7, p8);
	planes[5] = Plane(p4, p8, p5);
}

