#pragma once
#include <cmath>
#include <vector>
#include <iostream>
#include <stdio.h>


using namespace std;
class Line;
class Point;
class Vector;
class Plane;
class Triangle;






class Shape {
public:
	virtual bool interSect(Line line, Point& ptOfCrossing) = 0;
};

class Vector {
public:	
	double x, y, z;

	Vector(double x = 0, double y = 0, double z = 0) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	double lengthPow2() {
		return x * x + y * y + z * z;
	}
	friend double operator*(const Vector& a, const Vector& b) {
		return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
	}
};

class Point {
public:	
	double x, y, z;
	Point(double x = 0, double y = 0, double z = 0) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	friend Vector operator-(const Point& first, const Point& second){
		return Vector(first.x-second.x, first.y - second.y, first.z - second.z);
	}
};

class Plane {
public:
	Vector normal;
	double A, B, C, D;

	Plane(Point a = Point(), Point b = Point(), Point c = Point()) :normal{ Vector(0, 0, 0) } {
		//determinant
		A = b.y * c.z - a.y * c.z - b.y * a.z - c.y * b.z + c.y * a.z + a.y * b.z;
		B = b.z * c.x - a.z * c.x - b.z * a.x - c.z * b.x + c.z * a.x + a.z * b.x;
		C = b.x * c.y - a.x * c.y - b.x * a.y - c.x * b.y + c.x * a.y + a.x * b.y;
		D = -a.x * A - a.y * B - a.z * C;
		normal = Vector(A, B, C);//normal vector
	}
};

double distEuclid(Point A, Point B) {
	return sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y) + (A.z - B.z) * (A.z - B.z));
}

class Line {
public:
	Vector a;
	Point p;
	Line(Point point, Vector a) {
		this->a = a;
		p = point;
	}
};

class Triangle{
private:
	double s(Point A, Point B, Point C) {
		double a = distEuclid(A, B);
		double b = distEuclid(B, C);
		double c = distEuclid(A, C);
		double p = (a+b+c)/2.;
		return sqrt( fabs(p * (p - a) * (p - b) * (p - c)) );
	}


public:
	Point A, B, C;
	Plane plane;
	Triangle(Point a, Point b, Point c) : plane{Plane(a, b, c)} {
		A = a;
		B = b;
		C = c;
	}
	bool interSect(Line line, Point& ptOfCrossing){
		// k * t = h
		double k = this->plane.A * line.a.x + this->plane.B * line.a.y + this->plane.C * line.a.z;
		if (fabs(k) < 1e-3) {
			return false;
		}
		else {
			double t = -(this->plane.A * line.p.x + this->plane.B * line.p.y + this->plane.C * line.p.z + this->plane.D) / k;
			ptOfCrossing = Point(line.p.x + line.a.x * t, line.p.y + line.a.y * t, line.p.z + line.a.z * t);
			if (this->containsPoint(ptOfCrossing)) {
				return true;
			}
			else return false;
		}
	}
	bool containsPoint(Point pt) {
		return s(pt, A, B) + s(pt, A, C) + s(B, C, pt) - 1e-5 < s(C, A, B);
	}
};

class Circle: public Shape {
private:
	double radius;
	Point center;
	Plane plane;
	double distEuclid(Point A, Point B) {
		return sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y) + (A.z - B.z) * (A.z - B.z));
	}
	bool containsPoint(Point pt) {
		return distEuclid(center, pt) <= radius;
	}
public:
	Circle(Plane plane, Point center, double radius) {
		this->plane = plane;
		this->center = center;
		this->radius = radius;
	}

	virtual bool interSect(Line line, Point& ptOfCrossing)override {
		// k * t = h
		double k = this->plane.A * line.a.x + this->plane.B * line.a.y + this->plane.C * line.a.z;
		if (fabs(k) < 1e-3) {
			return false;
		}
		else {
			double t = -(this->plane.A * line.p.x + this->plane.B * line.p.y + this->plane.C * line.p.z + this->plane.D) / k;
			ptOfCrossing = Point(line.p.x + line.a.x * t, line.p.y + line.a.y * t, line.p.z + line.a.z * t);
			if (this->containsPoint(ptOfCrossing)) {
				return true;
			}
			else return false;
		}

	}
};




class Parallelepiped {
	Point origin;
	Vector X;
	Vector Y;
	Vector Z;

public:
	bool intersectLineWithPlane(Line line, Plane plane, Point& point) {
		double k = plane.A * line.a.x + plane.B * line.a.y + plane.C * line.a.z;
		if (fabs(k) < 1e-3) {
			return false;
		}
		double t = -(plane.A * line.p.x + plane.B * line.p.y + plane.C * line.p.z + plane.D) / k;
		point = Point(line.p.x + line.a.x * t, line.p.y + line.a.y * t, line.p.z + line.a.z * t);
		return true;
	}

	Parallelepiped() : origin(Point(0, 0, 0)) {
		X = Vector(0, 0, 0);
		Y = Vector(0, 0, 0);
		Z = Vector(0, 0, 0);
	}
	Parallelepiped(Point origin, double width, double length, double height) :origin(origin) {
		X.x = width;
		X.y = 0;
		X.z = 0;
		Y.x = 0;
		Y.y = length;
		Y.z = 0;
		Z.x = 0;
		Z.y = 0;
		Z.z = height;
	}
	Point getOrigin() {
		return origin;
	}
	Vector getX() {
		return X;
	}
	Vector getY() {
		return Y;
	}
	Vector getZ() {
		return Z;
	}
	bool intersectWithTriangle(Triangle& triangle) {
		if (containsPoint(triangle.A) || containsPoint(triangle.B) || containsPoint(triangle.C))
			return true;
		return false;
	}
	bool includeTriangleInside(Triangle& triangle) {
		if (containsPoint(triangle.A) && containsPoint(triangle.B) && containsPoint(triangle.C))
			return true;
		return false;
	}
	bool containsPoint(Point& point) {
		if (point.x >= origin.x && point.x <= origin.x + X.x && point.y >= origin.y && point.y <= origin.y + Y.y
			&& point.z >= origin.z && point.z <= origin.z + Z.z) {
			return true;
		}
		return false;
	}

	void extendByPoint(Point pt) {
		if (origin.x < pt.x) {
			X.x += fabs(origin.x - pt.x);
		}
		else {
			origin.x = pt.x;
			X.x += fabs(origin.x - pt.x);
		}

		if (origin.y < pt.y) {
			Y.y += fabs(origin.y - pt.y);
		}
		else {
			origin.y = pt.y;
			Y.y += fabs(origin.y - pt.y);
		}

		if (origin.z < pt.z) {
			Z.z += fabs(origin.z - pt.z);
		}
		else {
			origin.z = pt.z;
			Z.z += fabs(origin.z - pt.z);
		}
	}

	void extendByTriangle(Triangle t) {
		extendByPoint(t.A);
		extendByPoint(t.B);
		extendByPoint(t.C);
	}

	bool intersectWithLine(Line& line) {
		Point point1, point2, point3, intersect;
		point1 = origin;
		point2 = origin;
		point2.x += X.x;
		point3 = origin;
		point3.y += Y.y;
		Plane plane(point1, point2, point3);
		if (intersectLineWithPlane(line, plane, intersect)) {
			if (intersect.x >= point1.x && intersect.x <= point2.x && intersect.y >= point1.y && intersect.y <= point3.y)
				return true;
		}

		point1 = origin;
		point1.z += Z.z;
		point2 = origin;
		point2.z += Z.z;
		point2.x += X.x;
		point3 = origin;
		point3.z += Z.z;
		point3.y += Y.y;
		plane = Plane(point1, point2, point3);
		if (intersectLineWithPlane(line, plane, intersect)) {
			if (intersect.x >= point1.x && intersect.x <= point2.x && intersect.y >= point1.y && intersect.y <= point3.y)
				return true;
		}

		point1 = origin;
		point2 = origin;
		point2.y += Y.y;
		point3 = origin;
		point3.z += Z.z;
		plane = Plane(point1, point2, point3);
		if (intersectLineWithPlane(line, plane, intersect)) {
			if (intersect.y >= point1.y && intersect.y <= point2.y && intersect.z >= point1.z && intersect.z <= point3.z)
				return true;
		}

		point1 = origin;
		point1.x += X.x;
		point2 = origin;
		point2.x += X.x;
		point2.y += Y.y;
		point3 = origin;
		point3.x += X.x;
		point3.z += Z.z;
		plane = Plane(point1, point2, point3);
		if (intersectLineWithPlane(line, plane, intersect)) {
			if (intersect.y >= point1.y && intersect.y <= point2.y && intersect.z >= point1.z && intersect.z <= point3.z)
				return true;
		}

		point1 = origin;
		point2 = origin;
		point2.x += X.x;
		point3 = origin;
		point3.z += Z.z;
		plane = Plane(point1, point2, point3);
		if (intersectLineWithPlane(line, plane, intersect)) {
			if (intersect.x >= point1.x && intersect.x <= point2.x && intersect.z >= point1.z && intersect.z <= point3.z)
				return true;
		}

		point1 = origin;
		point1.y += Y.y;
		point2 = origin;
		point2.y += Y.y;
		point2.x += X.x;
		point3 = origin;
		point3.y += Y.y;
		point3.z += Z.z;
		plane = Plane(point1, point2, point3);
		if (intersectLineWithPlane(line, plane, intersect)) {
			if (intersect.x >= point1.x && intersect.x <= point2.x && intersect.z >= point1.z && intersect.z <= point3.z)
				return true;
		}
		return false;
	}
};
