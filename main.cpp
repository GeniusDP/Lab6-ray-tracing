#include <iostream>
#include <vector>
#include "Geometry.h"
#include "Parser.h"
#include <filesystem>
#include "Picture.h"

using namespace std;
int main()
{
    
    //Circle tr(Plane(Point(0, 0, 0), Point(0, 10, 0), Point(0, 0, 10)), Point(0, 0, 0), 3);
    //Triangle tr(Point(0, 6, 4), Point(1, 10, 7), Point(2, 12, 2));
    //Triangle tr(Point(0, 0, 0), Point(0, 10, 0), Point(0, 10, 10));
    
    //спереди работает
    /*
    Point CAM(100, 0, 0);
    Shield shield(Point(200, 0, 0), Plane(Point(200, 0, 0), Point(200, 100, 0), Point(200, 0, 100)), 121);
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
    
    
    
    //сбоку работает
    Point CAM(0, 100, 0);
    Shield shield(Point(0, 200, 0), Plane(Point(100, 200, 0), Point(-100, 200, 0), Point(0, 200, 100)), 121);
    

    Parser p("cow.obj");
    vector<Triangle> vec = p.parse();

    shield.trace(vec, CAM);
    
    printToPicture(shield.getM());
    /*FILE* filePtr;
    freopen_s(&filePtr, "output.txt", "w", stdout);
    //output
    for (int i = shield.getM().size()-1; i >=0 ; i--) {
        for (int j = shield.getM().size() - 1; j >= 0; j--)
            cout << shield.getM()[i][j];
        cout << endl;
    }*/

    return 0;
}
