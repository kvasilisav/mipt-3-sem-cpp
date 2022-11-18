#include <iostream>
#include<string>

using namespace std;

struct Point {

    unsigned long long const x, y;

    Point(unsigned long long int x, unsigned long long int y) : x(x), y(y) {}

    Point minx(Point const& rha) const {
        return Point(rha.x < x ? rha.x : x, y);
    }
    Point miny(Point const& rha) const {
        return Point(x, rha.y < y ? rha.y : y);
    }
    Point maxx(Point const& rha) const {
        return Point(rha.x > x ? rha.x : x, y);
    }
    Point maxy(Point const& rha) const {
        return Point(x, rha.y > y ? rha.y : y);
    }
    void print() const {
        cout << '(' << x << ',' << y << ')' << ' ';
    }
};

struct Rectangle {
    Point p;

    Rectangle() : Rectangle(Point(0, 0)) {}
    Rectangle(Point const& p) : p(p) {}

    Rectangle operator*(Rectangle const& rha) const {
        return Rectangle(Point(p.minx(rha.p).x, p.miny(rha.p).y));
    }

    Rectangle operator+(Rectangle const& rha) const {
        return Rectangle(Point(p.maxx(rha.p).x, p.maxy(rha.p).y));
    }

    void print() const {
        cout << p.x << ' ' << p.y << ' ';
    }
};

Rectangle multiplication(Rectangle* rec_array, int start, int end, char* operations) {
    if (start == end) {
        return rec_array[start];
    }

    else return rec_array[start] * multiplication(rec_array, start + 1, end, operations);
}


Rectangle addition(Rectangle* rec_array, int start, int end, char* operations) {

    if (start == end) {
        return rec_array[start];
    }

    else if (operations[start] == '+') {
        return rec_array[start] + addition(rec_array, start + 1, end, operations);
    }

    else {
        int partition = 0;
        bool flag = false;
        for (int i = start; i < end; ++i) {
            if (operations[i] == '+') {
                partition = i;
                flag = true;
            }
        }
        if (flag) return multiplication(rec_array, start, partition, operations) + addition(rec_array, partition + 1, end, operations);
        else return multiplication(rec_array, start, end, operations);
    }
}

int main() {

    string expression;
    getline(cin, expression);
    int len = expression.length();


    Rectangle rec(Point(0, 0));

    void* memory = operator new (sizeof(Rectangle) * len);

    int j = 0;
    unsigned long long int a = 0;
    unsigned long long int b = 0;

    for (int i = 0; i < len; ++i) {

        if (expression[i] == '(') {
            a = 0;
            i++;
            while (expression[i] != ',') {
                if (expression[i] != ' ') {
                    a = a * 10 + (expression[i] - '0');
                }
                i++;
            }
            b = 0;
            i++;
            while (expression[i] != ')') {
                if (expression[i] != ' ') {
                    b = b * 10 + (expression[i] - '0');
                }
                i++;
            }
            new ((char*)memory + sizeof(Rectangle) * j) Rectangle(Point(a, b));
            j++;
        }
    }

    Rectangle* rec_array = reinterpret_cast<Rectangle*>(memory);

    int amount = j;



    char* operations = new char[amount - 1];
    int tmp = 0;
    for (int i = 0; i < len; ++i) {
        if (expression[i] == '+') {
            operations[tmp] = '+';
            tmp++;
        }
        else if (expression[i] == '*') {
            operations[tmp] = '*';
        }
    }


    addition(rec_array, 0, amount - 1, operations).print();

    delete[] operations;
    delete[] rec_array;
}