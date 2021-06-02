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
    //cout << "Enter image size, please(bigger than 150): "; cin >> imageSize;
    //сбоку работает
    Point CAM(0, 100, 0);
    Shield shield(Point(0, imageSize*0.9, 0), Plane(Point(100, imageSize * 0.9, 0), Point(-100, imageSize * 0.9, 0), Point(0, imageSize * 0.9, 100)), imageSize);

    Parser p("cow.obj");
    cout << "Parsing..." << endl;
    vector<Triangle> vec = p.parse(30, -21, 15);
    cout << "Tracing..." << endl;
    shield.trace(vec, CAM);
    printToPicture(shield.getM());
    
    /*Point test(1, 2, 3);
    //вокруг Оz на 90 градусов
    Point next = Point(test.x * cos(3.14159 / 2) - test.y * sin(3.14159 / 2), test.x * sin(3.14159 /2) + test.y * cos(3.14159 /2), test.z);//1, test.x*sin(3.14/4) + test.y*cos(3.14/4), test.z * sin(3.14 / 4) - test.z * cos(3.14 / 4)
    //вокруг Оx на 90 градусов
    Point next = Point(test.x, test.z * sin(3.1415962 / 4) + test.y * cos(3.1415962 / 4), test.z * cos(3.1415962 / 4) - test.y * sin(3.1415962 / 4));//1, test.x*sin(3.14/4) + test.y*cos(3.14/4), test.z * sin(3.14 / 4) - test.z * cos(3.14 / 4)
    
    //вокруг Оy на 90 градусов
    Point next = Point(test.x * cos(3.14159 / 2) - test.z * sin(3.14159 / 2), test.y, test.x * sin(3.1415962 / 2) + test.z * cos(3.1415962 / 2));*/
    return 0;
}
