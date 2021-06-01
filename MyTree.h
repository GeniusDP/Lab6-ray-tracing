#pragma once
#include <iostream>
#include <vector>
#include "Geometry.h"

using namespace std;


struct Node {
	Parallelepiped parallelepiped;
	vector<Node*> children;
	vector<Triangle> triangle;
};

class MyTree {
	Node* root;
	Parallelepiped big;
public:
	MyTree() {
	}
	Node* getRoot() {
		return root;
	}
	void insertTriangle(Triangle& tr) {


	}



};
