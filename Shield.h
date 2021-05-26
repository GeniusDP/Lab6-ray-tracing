#pragma once

class Shield {
	Point originPoint;
	int originI, originJ;//center of the matrix
	Plane plane;
	vector<vector<char>> m;
public:
	Shield(Point originPoint, Plane plane, int size) {
		this->originPoint = originPoint;
		originI = originJ = size / 2;
		this->plane = plane;
		m = vector<vector<char>>(size, vector<char>(size, '.'));
	}
	vector<vector<char>>& getM() {
		return m;
	}
	void trace(vector<Triangle>&, Point camera);
};

