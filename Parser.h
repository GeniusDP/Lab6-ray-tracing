#pragma once
#include <iostream>
#include <vector>
#include "Geometry.h"
#include <fstream>
#include <string>
#include <sstream>

using namespace std;
Point readPoint(string s, double arcX, double arcY, double arcZ) {
	stringstream stream;
	for (int i = 2; i < s.size(); i++)
		stream << s[i];
	Point pt;
	stream >> pt.x >> pt.y >> pt.z;
	pt.x *= 100;
	pt.y *= 100;
	pt.z *= 100;
	pt.rotate(arcX, arcY, arcZ);
	return pt;
}

Triangle readTriangle(string str, const vector<Point>& points) {
	stringstream stream;
	int i = 2, right = 0;
	str += ' ';
	while (i < str.size()) {
		if (str[i] == '/') {
			right = i;
			while (str[right] != ' ') {
				right++;
			}
			stream << " ";
			i = right + 1;
		}
		else {
			stream << str[i];
			i++;
		}
	}
	int a, b, c;
	stream >> a >> b >> c;
	a--; b--; c--;
	return Triangle(points[a], points[b], points[c]);
}



class Parser {
	string filename;
public:
	Parser(string filename) {
		this->filename = filename;
	}
	vector<Triangle> parse(double arcX, double arcY, double arcZ) {
		vector<Triangle> result;
		vector<Point> points;
		string s;
		ifstream in(filename);
		while (getline(in, s)) {
			if(s[0] == 'v' && s[1]==' ')points.push_back( readPoint(s, arcX, arcY, arcZ) );
			else {
				if (s[0] == 'f')result.push_back( readTriangle(s, points) );
			}
		}
		return result;
	}

};