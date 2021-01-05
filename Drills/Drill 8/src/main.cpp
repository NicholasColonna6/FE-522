/*
 * Nicholas Colonna
 * FE 522
 * Drill 10
 */

#include "std_lib_facilities.h"

//point class
class Point {
    double x, y;
public:
    Point () : x(0), y(0) {};
    Point (double x_, double y_) : x(x_), y(y_) {};

    double getX () {    //getter for x
        return x;
    }
    double getY () {    //getter for y
        return y;
    }
};

//overload input operation
istream & operator>> (istream & is, Point & p) {
    char c1, c2, c3;
    double x, y;
    is >> c1 >> x >> c2 >> y >> c3;
    if (!is) {
        error("An error occurred while reading point");
    }
    if (c1 != '(' || c2 != ',' || c3 != ')') {
        error("Invalid input format");
    }
    p = Point(x,y);
    return is;
}

//overload output operation
ostream & operator<< (ostream & os, Point p) {
    os << "(" << p.getX() << "," << p.getY() << ")";
    return os;
}

int main() {
    //prompts user to enter 7 points
    cout << "Enter 7 points with format \"(x,y)\"\n";
    vector<Point> original_points;
    for (int i = 0; i < 7; i++) {
        Point p;
        cin >> p;
        if (!cin) {
            error("Error reading the point entered");
        }
        original_points.push_back(p);
    }

    //creates output file and writes all the points to it
    ofstream outputFile;
    outputFile.open("../../data/mydata.txt", ios::out);
    for (int i = 0; i < 7; i++)
        outputFile << original_points[i] << endl;
    outputFile.close();

    //reads points from mydata.txt and stores in vector
    vector<Point> processed_points;
    ifstream inputFile;
    inputFile.open("../../data/mydata.txt");
    for (int i = 0; i < 7; i++) {
        Point p;
        inputFile >> p;
        if (!inputFile) {
            error("Error while reading point");
        }
        processed_points.push_back(p);
    }
    inputFile.close();

    //prints points from original_points
    cout << "\nOriginal Points:\n";
    for (int i = 0; i < 7; i++){
        cout << original_points[i] << "\n";
    }

    //prints the points from processed points
    cout << "\nProcessed Points:\n";
    for (int i = 0; i < 7; i++){
        cout << processed_points[i] << "\n";
    }

    //checks that points between the 2 vectors are the same
    cout << "\nChecking that original points and processed points are the same...";
    bool somethings_wrong = false;
    if (original_points.size() != processed_points.size()){
        somethings_wrong = true;
    }
    for (int i=0; i < 7; i++) {
        if((original_points[i].getX() != processed_points[i].getX()) || (original_points[i].getY() != processed_points[i].getY())){
            somethings_wrong = true;
            break;
        }
    }
    if(somethings_wrong == true){
        cout << "Something's wrong!\n\n";
    }else{
        cout << "All points match!\n\n";
    }

    keep_window_open();
    return 0;
}
