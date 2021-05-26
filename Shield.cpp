#include "RTree.h"
#include "Shield.h"

void Shield::trace(vector<Triangle>& trVec, Point camera) {
	const char* pixels = "WXwxoc-\0";
	int cnt = 0;
	//for (int i = 0; i < m.size(); i++) {
	//	for (int j = 0; j < m.size(); j++) {
	//		Point curr;
	//		if (plane.A == 0 && plane.B == 0) {
	//			//z = -d;
	//			//параллельно xOy
	//			curr = Point(originPoint.x + (originI - i), originPoint.y + (originJ - j), originPoint.z);
	//			//Point(originPoint.x + (originJ - j), originPoint.y, originPoint.z + (originI - i));
	//		}else
	//			if (plane.A == 0 && plane.C == 0) {
	//				//y = -d;
	//				//параллельно xOz
	//				curr = Point(originPoint.x + (originJ - j), originPoint.y, originPoint.z + (originI - i));
	//			}else
	//				if (plane.B == 0 && plane.C == 0) {
	//					//x = -d;
	//					//параллельно zOy
	//					curr = Point(originPoint.x, originPoint.y + (originJ - j), originPoint.z + (originI - i));
	//				}


	//		Line line(curr, camera-curr);
	//		Point crossPt;//point where line and triangle intercross
	//		double minDist = 1e9;
	//		Triangle totSamyi(Point(1e9, 1e9, 1e9), Point(1e9, 1e9, 1e9), Point(1e9, 1e9, 1e9));
	//		for (auto tr : trVec) {
	//			if (tr.interSect(line, crossPt)) {
	//				if (distEuclid(curr, crossPt) < minDist) {
	//					minDist = distEuclid(curr, crossPt);
	//					totSamyi = tr;
	//				}
	//			}
	//		}
	//		
	//		if (minDist+100<1e9) {
	//			cnt++;
	//			double cosA = (line.a * totSamyi.plane.normal) / (line.a.length() * totSamyi.plane.normal.length());
	//			cosA = fabs(cosA);
	//			m[i][j] = pixels[int(cosA * 6)];
	//		}
	//	}
	//}
	RTree* tree = new RTree({ -250, -250 }, 500, 500, 500);
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
			vector< Triangle > intersectedTrinagles;
			tree->traceRay(tree->getRoot(), line, intersectedTrinagles);
			double minDist = 1e9;
			Triangle totSamyi(Point(1e9, 1e9, 1e9), Point(1e9, 1e9, 1e9), Point(1e9, 1e9, 1e9));
			for (auto tr : intersectedTrinagles) {
				if (tr.interSect(line, crossPt)) {
					if (distEuclid(curr, crossPt) < minDist) {
						minDist = distEuclid(curr, crossPt);
						totSamyi = tr;
					}
				}
			}

			if (minDist + 100 < 1e9) {
				cnt++;
				double cosA = (line.a * totSamyi.plane.normal) / (line.a.length() * totSamyi.plane.normal.length());
				cosA = fabs(cosA);
				m[i][j] = pixels[int(cosA * 6)];
			}
		}
	}
	delete tree;
	cout << "cnt = " << cnt << endl;
}
