#include <iostream>
#include <vector>

using namespace std;

class Shape {
    private: 
        double height;

    public:
        Shape(double height) {
            this->height = height;
        }

        virtual double calculateBaseArea() = 0; 
        virtual double calculateBasePerimeter() = 0;

        double calculateVolume() {
            return this->calculateBaseArea() * this->height;
       }

       double calculateSurface() {
           return 2 * this->calculateBaseArea() + this->calculateBasePerimeter() * this->height;  
       }
};

class Circle: public Shape {
    private:
        double radius;
        const double pi = 3.14;

    public:
        Circle(double height, double radius): Shape(height) {
            this->radius = radius;
        }

        virtual double calculateBaseArea() {
            return this->pi * this->radius * this->radius;
        }

        virtual double calculateBasePerimeter() {
            return this->pi * this->radius * 2;
        }
};

class Rectangle: public Shape {
    private:
        double width, length;

    public:
        Rectangle(double height, double width, double length): Shape(height) {
            this->width = width;
            this->length = length;
        }

        virtual double calculateBaseArea() {
            return this->width * this->length;
        }

        virtual double calculateBasePerimeter() {
            return 2 * (this->width * this->length);
        }        
};

class Square: public Rectangle {
    public:
        Square(double height, double length): Rectangle(height, length, length) {

        }
};

class BakingGrandma {
    private:
        vector<Shape*> shapes;
        double totalWhippedCream;
        double totalMagiun;

        void createShape() {
            string baseType;
            cin >> baseType;

            double height;
            cin >> height;

            if (baseType == "circle") {
                double radius;
                cin >> radius;
                this->shapes.push_back(
                    new Circle(height, radius)
                );
            } else if (baseType == "rectangle") {
                double width, length;
                cin >> width >> length;
                this->shapes.push_back(
                    new Rectangle(height, width, length)
                );
            } else if (baseType == "square") {
                double length;
                cin >> length;
                this->shapes.push_back(
                    new Square(height, length)
               );
            }
        }

        void removeShape() {
            uint index;
            cin >> index;

            Shape *shape = this->shapes[index];

            double whippedCream = 2 * shape->calculateVolume();
            double magiun = shape->calculateSurface(); 

            this->totalMagiun += magiun;
            this->totalWhippedCream += whippedCream;

            cout << "Whipped cream used " << whippedCream << endl;
            cout << "\"Magiun\" used " << magiun << endl; 
        }
    
    public:
        BakingGrandma() {
            this->totalWhippedCream = 0;
            this->totalMagiun = 0;
        }

        void interactiveCommandLine() {
            while (true) {
                string command;
                cin >> command;

                if (command == "STOP") {
                    break;
                } else if (command == "ADD") {
                    this->createShape();
                } else if (command == "REMOVE") {
                    this->removeShape();
                } else if (command == "TOTAL") {
                    cout << "Total used \"magiun\" is " << this->totalMagiun 
                         << " and whipped cream " << this->totalWhippedCream << endl;  
                } 
            }
        }
};

int main() {
    BakingGrandma grandma;
    grandma.interactiveCommandLine();

    return 0;
}