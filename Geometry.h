#pragma once
#include <cmath>
#include <vector>
#include <iostream>
#include <stdio.h>

using namespace std;
class Line;
//class Point;
class Vector;
//class Shield;
class Plane;
class Triangle;

class Vector {
public:
	double x, y, z;

	Vector(double x = 0, double y = 0, double z = 0) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	double length() {
		return sqrt(x * x + y * y + z * z);
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
	friend Vector operator-(const Point& first, const Point& second) {
		return Vector(first.x - second.x, first.y - second.y, first.z - second.z);
	}
};


class Shape {
public:
	virtual bool interSect(Line line, Point& ptOfCrossing) = 0;
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

class Triangle: public Shape{
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