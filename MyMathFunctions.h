#ifndef BLABLA_H
#define BLABLA_H

#include "MyMathClasses.h"

Point crossProduct(Point vec1, Point vec2);

double dotProduct(Point& vec1, Point& vec2);

void rotate(Point& point, double angleXY, double angleXZ);

double dist(double x1, double y1, double z1, double x2, double y2, double z2);

double Abs(Point& vec);

bool isOnPlane(Point point, Plane plane);

bool lineCubeIntersect(Cube& cube, Point dirVec, Point& person, Point& point, Point& normal);

void rotate(Cube& cube, double angleXY, double angleXZ);


#endif