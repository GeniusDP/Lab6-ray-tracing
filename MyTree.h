#pragma once
#include <iostream>
#include <vector>
#include "Geometry.h"

using namespace std;

#define MAX_SIZE 99

struct Node {
	Parallelepiped parallelepiped;
	vector<Node*> children;
	vector<Triangle> triangles;
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
		Node* curr = root;
		while (curr->children.size() > 0) {//while we have not reached
			curr->parallelepiped.extendByTriangle(tr);
			double minimalExtention = 1e9;//inf
			Node* next = nullptr;
			for (auto c : curr->children) {
				double tmpExt = c->parallelepiped.getExtentionAfterInsert(tr);
				if (tmpExt < minimalExtention) {
					minimalExtention = tmpExt;
					next = c;
				}
			}
			if (next) {
				curr = next;
			}
		}//while curr has children
		curr->triangles.push_back(tr);
		if (curr->triangles.size() > MAX_SIZE) {
			//divide this node
			Node* left, * right;
			left = new Node; right = new Node;
			

			//adding triangles into children
			int cntOfTriangles = curr->triangles.size();
			for (int i = 0; i < cntOfTriangles; i++) {
				if (i < cntOfTriangles / 2) {
					//to left
					left->parallelepiped.extendByTriangle(curr->triangles[i]);
					left->triangles.push_back(curr->triangles[i]);
				}
				else {
					//to right
					left->parallelepiped.extendByTriangle(curr->triangles[i]);
					left->triangles.push_back(curr->triangles[i]);
				}
			}
		}

	}//end sub



};
