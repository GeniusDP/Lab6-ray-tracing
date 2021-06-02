#pragma once
#include <cmath>
#include <vector>
#include <iostream>
#include <stdio.h>
#include "Geometry.h"
#include "RTree.h"
using namespace std;


class Shield {
	Point originPoint;
	int originI, originJ;//center of the matrix
	Plane plane;
	vector<vector<double>> m;
public:
	Shield(Point originPoint, Plane plane, int size) {
		this->originPoint = originPoint;
		originI = originJ = size / 2;
		this->plane = plane;
		m = vector<vector<double>>(size, vector<double>(size, -5));
	}
	vector<vector<double>>& getM() {
		return m;
	}
	void trace(vector<Triangle>&, Point camera);
};


void Shield::trace(vector<Triangle>& trVec, Point camera) {
	double minC = 1e9, maxC = -1e9;
	for (auto t : trVec) {
		minC = min(minC, t.A.x);
		minC = min(minC, t.A.y);
		minC = min(minC, t.A.z);
		minC = min(minC, t.B.x);
		minC = min(minC, t.B.y);
		minC = min(minC, t.B.z);
		minC = min(minC, t.C.x);
		minC = min(minC, t.C.y);
		minC = min(minC, t.C.z);

		maxC = max(maxC, t.A.x);
		maxC = max(maxC, t.A.y);
		maxC = max(maxC, t.A.z);
		maxC = max(maxC, t.B.x);
		maxC = max(maxC, t.B.y);
		maxC = max(maxC, t.B.z);
		maxC = max(maxC, t.C.x);
		maxC = max(maxC, t.C.y);
		maxC = max(maxC, t.C.z);
	}
	int cnt = 0;
	RTree* tree = new RTree({ minC, minC, minC }, 2*(maxC - minC), 2 *(maxC - minC), 2 *(maxC - minC));

	for (auto tr : trVec)
		tree->addNode(tree->getRoot(), tr);
	for (int i = 0; i < m.size(); i++) {
		for (int j = 0; j < m.size(); j++) {
			Point curr;
			if (plane.A == 0 && plane.B == 0) {
				//z = -d;
				//параллельно xOy
				curr = Point(originPoint.x + (originI - i), originPoint.y + (originJ - j), originPoint.z);
				//Point(originPoint.x + (originJ - j), originPoint.y, originPoint.z + (originI - i));
			}
			else
				if (plane.A == 0 && plane.C == 0) {
					//y = -d;
					//параллельно xOz
					curr = Point(originPoint.x + (originJ - j), originPoint.y, originPoint.z + (originI - i));
				}
				else
					if (plane.B == 0 && plane.C == 0) {
						//x = -d;
						//параллельно zOy
						curr = Point(originPoint.x, originPoint.y + (originJ - j), originPoint.z + (originI - i));
					}


			Line line(curr, camera - curr);
			Point crossPt;//point where line and triangle intercross
			vector< Triangle > intersectedTriangles;
			tree->traceRay(tree->getRoot(), line, intersectedTriangles);
			double minDist = 1e9;
			Triangle theClosest(Point(1e9, 1e9, 1e9), Point(1e9, 1e9, 1e9), Point(1e9, 1e9, 1e9));
			for (auto tr : intersectedTriangles) {
				if (tr.interSect(line, crossPt)) {
					if (distEuclid(curr, crossPt) < minDist) {
						minDist = distEuclid(curr, crossPt);
						theClosest = tr;
					}
				}
			}

			if (minDist + 100 < 1e9) {
				cnt++;
				double cosA = (line.a * theClosest.plane.normal) / sqrt(line.a.lengthPow2() * theClosest.plane.normal.lengthPow2());
				cosA = fabs(cosA);
				m[i][j] = cosA;
			}
		}
	}
	//delete tree;
	//cout << "cnt = " << cnt << endl;
	cout << "Solved!";
}
