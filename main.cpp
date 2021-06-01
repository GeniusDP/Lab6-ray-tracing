#include <iostream>
#include <vector>
#include "Geometry.h"
#include "Parser.h"
#include <filesystem>
#include "Picture.h"
#include "Shield.h"

using namespace std;
int main()
{
    
    //Circle tr(Plane(Point(0, 0, 0), Point(0, 10, 0), Point(0, 0, 10)), Point(0, 0, 0), 3);
    //Triangle tr(Point(0, 6, 4), Point(1, 10, 7), Point(2, 12, 2));
    //Triangle tr(Point(0, 0, 0), Point(0, 10, 0), Point(0, 10, 10));
    
    //спереди работает
    /*
    int imageSize = 1001;
    Point CAM(100, 0, 0);
    Shield shield(Point(imageSize * 0.8, 0, 0), Plane(Point(imageSize * 0.8, 0, 0), Point(imageSize * 0.8, 100, 0), Point(imageSize * 0.8, 0, 100)), imageSize);
    */
    
    //сзади работает
    /*
    Point CAM(-100, 0, 0);
    Shield shield(Point(-200, 0, 0), Plane(Point(-200, 0, 0), Point(-200, 100, 0), Point(-200, 0, 100) ), 121);
    */
    
    //сверху работает
    /*
    Point CAM(0, 0, 100);
    Shield shield(Point(0, 0, 200), Plane(Point(0, 0, 200), Point(-1, 1, 200), Point(3, -5, 200)), 121);
    */
    
 
    int imageSize = 1001;
    //сбоку работает
    Point CAM(0, 100, 0);
    Shield shield(Point(0, imageSize*0.8, 0), Plane(Point(100, imageSize * 0.8, 0), Point(-100, imageSize * 0.8, 0), Point(0, imageSize * 0.8, 100)), imageSize);

    Parser p("cow.obj");
    vector<Triangle> vec = p.parse();
    
    shield.trace(vec, CAM);
    printToPicture(shield.getM());

    return 0;
}
