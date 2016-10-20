#include <iostream>

using namespace std;

class Point {
    double x_, y_;
    
    public:
    
    Point(double x, double y) {
        x_ = x;
        y_ = y;
    }
    
    double get_x() const {
        return x_;
    }
    
    Point& set_x(double x) {
        x_ = x;
        return *this;
    }
    
    double get_y() const {
        // pointless usage of this
        return this -> y_;
    }
    
    Point& set_y(double y) {
        // pointless usage of this
        (*this).y_ = y;
        // meaningful usage of this
        return *this;
    }
    
    void print() const {
        cout << "Point(" << x_ << ", "
                         << y_ << ")" << endl;
    }
};

int main() {
    const Point p1(10, 10);
    p1.print();
    
    Point p2(11, 12);
    p2.set_x(20);
    p2.print();
    
    Point p3(0, 0);
    p3.set_y(10).set_x(11).print();
    return 0;
}








