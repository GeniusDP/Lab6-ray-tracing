#pragma once
#include "Geometry.h"

bool intersectLineWithPlane(Line line, Plane plane, Point& point) {
	/*point.y = double(line.p.y * (line.a.z * plane.C + line.a.x + plane.A) - line.a.y * (plane.C * line.p.z - plane.D)) /
		(line.a.x * plane.A + line.a.y * plane.B + line.a.z * plane.C);
	point.x = line.p.x + double(line.a.x * (point.y - line.p.y)) / line.a.y;
	point.z = line.p.z + double(line.a.z * (point.y - line.p.y)) / line.a.y;*/
	double k = plane.A * line.a.x + plane.B * line.a.y + plane.C * line.a.z;
	if (fabs(k) < 1e-3) {
		return false;
	}
	double t = -(plane.A * line.p.x + plane.B * line.p.y + plane.C * line.p.z + plane.D) / k;
	point = Point(line.p.x + line.a.x * t, line.p.y + line.a.y * t, line.p.z + line.a.z * t);
	return true;
}

class Parallelepiped {
	Point origin;
	Vector X;
	Vector Y;
	Vector Z;

public:
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
	bool intersectWithTriangle(Triangle triangle) {
		if (intersectWithPoint(triangle.A) || intersectWithPoint(triangle.B) || intersectWithPoint(triangle.C))
			return true;
		return false;
	}
	bool intersectWithPoint(Point point) {
		if (point.x >= origin.x && point.x <= origin.x + X.x && point.y >= origin.y && point.y <= origin.y + Y.y
			&& point.z >= origin.z && point.z <= origin.z + Z.z) {
			return true;
		}
		return false;
	}
	bool intersectWithLine(Line line) {
		Point point1, point2, point3, intersect;
		point1 = origin;
		point2 = origin;
		point2.x += X.x;
		point3 = origin;
		point3.y += Y.y;
		Plane plane(point1, point2, point3);
		if (intersectLineWithPlane(line, plane, intersect)) {
			if (!(intersect.x >= point1.x && intersect.x <= point2.x && intersect.y >= point1.y && intersect.y <= point3.y))
				return false;
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
			if (!(intersect.x >= point1.x && intersect.x <= point2.x && intersect.y >= point1.y && intersect.y <= point3.y))
				return false;
		}

		point1 = origin;
		point2 = origin;
		point2.y += Y.y;
		point3 = origin;
		point3.z += Z.z;
		plane = Plane(point1, point2, point3);
		if (intersectLineWithPlane(line, plane, intersect)) {
			if (!(intersect.y >= point1.y && intersect.y <= point2.y && intersect.z >= point1.z && intersect.z <= point3.z))
				return false;
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
			if (!(intersect.y >= point1.y && intersect.y <= point2.y && intersect.z >= point1.z && intersect.z <= point3.z))
				return false;
		}

		point1 = origin;
		point2 = origin;
		point2.x += X.x;
		point3 = origin;
		point3.z += Z.z;
		plane = Plane(point1, point2, point3);
		if (intersectLineWithPlane(line, plane, intersect)) {
			if (!(intersect.x >= point1.x && intersect.x <= point2.x && intersect.z >= point1.z && intersect.z <= point3.z))
				return false;
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
			if (!(intersect.x >= point1.x && intersect.x <= point2.x && intersect.z >= point1.z && intersect.z <= point3.z))
				return false;
		}
		return true;
	}
};