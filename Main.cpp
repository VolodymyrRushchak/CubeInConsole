#include <iostream>
#include <cmath>
#include <chrono> 
#include <iomanip>

using std::cout;
using std::cin;

#include "auxiliary_functions.h"
#include "MyMathClasses.h"
#include "MyMathFunctions.h"


void showSphere(Sphere& sphere, Point& person, Point& light)
{
	gotoxy(0, 0);
	Point startVec(-8, -2, 2);
	Point endVec(-8, 2, -2);
	double dn = 0.15;
	double dk = 0.15;

	double m = startVec.x;
	double a, b, c, D, t1, t2, x1, y1, z1, x2, y2, z2, X, Y, Z;
	double scalar, cos_a;
	for (double k = startVec.z; k > endVec.z; k -= dk)
	{
		for (double n = startVec.y; n < endVec.y; n += dn)
		{
			a = m * m + n * n + k * k;
			b = 2 * (person.x * m + person.y * n + person.z * k);
			c = -pow(sphere.radius, 2) + pow(person.x, 2) + pow(person.y, 2) + pow(person.z, 2);
			D = b * b - 4 * a * c;

			if (D >= 0)
			{
				t1 = (-b - sqrt(D)) / (2 * a);
				t2 = (-b + sqrt(D)) / (2 * a);

				x1 = m * t1 + person.x;
				y1 = n * t1 + person.y;
				z1 = k * t1 + person.z;

				x2 = m * t2 + person.x;
				y2 = n * t2 + person.y;
				z2 = k * t2 + person.z;

				if (dist(x1, y1, z1, person.x, person.y, person.z) > dist(x2, y2, z2, person.x, person.y, person.z))
				{
					X = x2;
					Y = y2;
					Z = z2;
				}
				else
				{
					X = x1;
					Y = y1;
					Z = z1;
				}

				scalar = (X - sphere.center.x) * (X - light.x) + (Y - sphere.center.y) * (Y - light.y) + (Z - sphere.center.z) * (Z - light.z);
				cos_a = scalar / (dist(X, Y, Z, sphere.center.x, sphere.center.y, sphere.center.z)
					* dist(X, Y, Z, light.x, light.y, light.z));

				//cout << std::setw(4) << cos_a;

				if (-cos_a > 0.8) cout << std::setw(2) << "#";
				else if (-cos_a > 0.5) cout << std::setw(2) << "0";
				else if (-cos_a > 0.3) cout << std::setw(2) << "*";
				else cout << std::setw(2) << "-";
			}
			else
			{
				cout << std::setw(2) << " ";
			}
		}
		cout << '\n';
	}

}


void showCube(Cube& cube, Point& person, Point& light)
{
	gotoxy(0, 0);
	Point startVec(-5, -0.9, 0.9);
	Point endVec(-5, 0.9, -0.9);
	double dn = 0.04;
	double dk = 0.04;

	double m = startVec.x;
	double scalar, cos_a, cos_b, projection, res_cos;
	Point intersectPoint, normal, reflectedVec;
	for (double k = startVec.z; k > endVec.z; k -= dk)
	{
		for (double n = startVec.y; n < endVec.y; n += dn)
		{
			if (lineCubeIntersect(cube, Point(m, n, k), person, intersectPoint, normal))
			{
				double normalAbs = dist(normal.x, normal.y, normal.z, 0, 0, 0);
				scalar = normal.x * (intersectPoint.x - person.x) + normal.y * (intersectPoint.y - person.y) + normal.z * (intersectPoint.z - person.z);
				cos_a = scalar / (normalAbs * dist(intersectPoint.x, intersectPoint.y, intersectPoint.z, person.x, person.y, person.z));

				cos_a *= 0.3;

				scalar = normal.x * (intersectPoint.x - light.x) + normal.y * (intersectPoint.y - light.y) + normal.z * (intersectPoint.z - light.z);
				projection = scalar / dist(normal.x, normal.y, normal.z, 0, 0, 0);
				reflectedVec.x = intersectPoint.x - light.x - 2 * normal.x * (projection / normalAbs);
				reflectedVec.y = intersectPoint.y - light.y - 2 * normal.y * (projection / normalAbs);
				reflectedVec.z = intersectPoint.z - light.z - 2 * normal.z * (projection / normalAbs);

				scalar = reflectedVec.x * (intersectPoint.x - person.x) + reflectedVec.y * (intersectPoint.y - person.y) + reflectedVec.z * (intersectPoint.z - person.z);
				cos_b = -scalar / (Abs(reflectedVec) * dist(intersectPoint.x, intersectPoint.y, intersectPoint.z, person.x, person.y, person.z));

				cos_b = cos_b > 0 ? cos_b : 0;
				cos_b = pow(cos_b, 3);

				res_cos = cos_a + cos_b;

				if (res_cos > 0.84) cout << std::setw(2) << "&";
				else if (res_cos > 0.7) cout << std::setw(2) << "#";
				else if (res_cos > 0.56) cout << std::setw(2) << "$";
				else if (res_cos > 0.42) cout << std::setw(2) << "0";
				else if (res_cos > 0.28) cout << std::setw(2) << "+";
				else if (res_cos > 0.14) cout << std::setw(2) << "\"";
				else cout << std::setw(2) << "-";

			}
			else
			{
				cout << std::setw(2) << " ";
			}
		}
		cout << '\n';
	}
}




int main()
{
	const double PI = 3.1415926;
	Cube cube(1, 0, 0);
	Point point(0, 0, 0);
	Sphere sphere(1, point);

	Point person(5, 0, 0);

	Point light(1, 0, 1);

	double old_angleXY, old_angleXZ, new_angleXY, new_angleXZ;
	auto start = std::chrono::system_clock::now();
	long millis;

	old_angleXY = 0;
	old_angleXZ = PI;

	while (1)
	{
		millis = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count();
		new_angleXY = PI * sin((double)(millis) / 3000);
		new_angleXZ = PI * cos((double)(millis) / 3000);
		rotate(cube, new_angleXY - old_angleXY, new_angleXZ - old_angleXZ);
		old_angleXY = new_angleXY;
		old_angleXZ = new_angleXZ;
		showCube(cube, person, light);
		//showSphere(sphere,person,light);
		//rotate(light, PI / 90, PI / 90);
		//sleep_ms(100);
	}

	return 0;

}