#pragma once
#include <iostream>
#include <vector>
#include "Geometry.h"

using namespace std;



struct Node {
	Parallelepiped parallelepiped;
	vector<Node*> children;
	Triangle triangle;
	Node() : triangle(Triangle({ -1e9, -1e9 }, { -1e9, -1e9 }, { -1e9, -1e9 })) {}
};


class RTree {
	Node* root;
	int maxDepth;
public:
	RTree(Point origin, double width, double length, double height) {
		root = new Node;
		root->parallelepiped = Parallelepiped(origin, width, length, height);
		maxDepth = 4;
		buildTree(root);
	}
	RTree(Parallelepiped p) {
		root = new Node;
		root->parallelepiped = p;
		maxDepth = 4;
		buildTree(root);
	}
	Node* getRoot() {
		return root;
	}
	void buildTree(Node* node, int d = 1) {
		double newWidth = node->parallelepiped.getX().x / 2,
			newLength = node->parallelepiped.getY().y / 2,
			newHeight = node->parallelepiped.getZ().z / 2;
		Node* nodes[8];
		for (int i = 0; i < 8; i++)
			nodes[i] = new Node;
		Point point[8];
		point[0] = node->parallelepiped.getOrigin();
		point[1] = node->parallelepiped.getOrigin();
		point[1].x += newWidth;
		point[2] = node->parallelepiped.getOrigin();
		point[2].y += newLength;
		point[3] = node->parallelepiped.getOrigin();
		point[3].x += newWidth;
		point[3].y += newLength;
		point[4] = node->parallelepiped.getOrigin();
		point[4].z += newHeight;
		point[5] = node->parallelepiped.getOrigin();
		point[5].z += newHeight;
		point[5].x += newHeight;
		point[6] = node->parallelepiped.getOrigin();
		point[6].z += newHeight;
		point[6].y += newLength;
		point[7] = node->parallelepiped.getOrigin();
		point[7].z += newHeight;
		point[7].x += newWidth;
		point[7].y += newLength;
		for (int i = 0; i < 8; i++) {
			nodes[i]->parallelepiped = Parallelepiped(point[i], newWidth, newLength, newHeight);
			node->children.push_back(nodes[i]);
		}

		if (d < maxDepth) {
			for (int i = 0; i < node->children.size(); i++)
				buildTree(node->children[i], d + 1);
		}
	}

	void addNode(Node* node, Triangle& triangle, int d = 1) {
		if (!node->parallelepiped.intersectWithTriangle(triangle))
			return;
		if (d == maxDepth + 1) {
			Node* newNode = new Node;
			newNode->triangle = triangle;
			node->children.push_back(newNode);
		}
		else {
			for (int i = 0; i < node->children.size(); i++)
				addNode(node->children[i], triangle, d + 1);
		}
	}
	void removeNode(Node* node) {
		for (int i = 0; i < node->children.size(); i++)
			removeNode(node->children[i]);
		delete node;
	}
	void traceRay(Node* node, Line& line, vector< Triangle >& result) {
		if (node->children.size() > 0) {
			if (node->parallelepiped.intersectWithLine(line)) {
				for (int i = 0; i < node->children.size(); i++) {
					traceRay(node->children[i], line, result);
				}
			}
		}
		else {
			Point point(0, 0, 0);
			if (node->triangle.interSect(line, point)) {
				result.push_back(node->triangle);
			}
		}
	}

	~RTree() {
		removeNode(root);
	}
};