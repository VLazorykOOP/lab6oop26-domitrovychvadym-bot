#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

/* ============================================================
   TASK 1. Variant 7
   Virtual and non-virtual inheritance
   ============================================================ */

class A {
protected:
    int a;
public:
    A(int value = 1) : a(value) {
        cout << "A constructor\n";
    }

    virtual ~A() {
        cout << "A destructor\n";
    }

    void showA() const {
        cout << "A value = " << a << endl;
    }
};

// Without virtual inheritance
class B : public A {
protected:
    int b;
public:
    B(int av = 1, int bv = 2) : A(av), b(bv) {
        cout << "B constructor\n";
    }

    ~B() {
        cout << "B destructor\n";
    }
};

class C : public A {
protected:
    int c;
public:
    C(int av = 1, int cv = 3) : A(av), c(cv) {
        cout << "C constructor\n";
    }

    ~C() {
        cout << "C destructor\n";
    }
};

class D : public B, public C {
protected:
    int d;
public:
    D() : B(10, 20), C(30, 40), d(50) {
        cout << "D constructor\n";
    }

    ~D() {
        cout << "D destructor\n";
    }

    void show() const {
        cout << "Class D without virtual inheritance\n";
        cout << "B::A value = " << B::a << endl;
        cout << "C::A value = " << C::a << endl;
    }
};

// With virtual inheritance
class BV : virtual public A {
protected:
    int b;
public:
    BV(int av = 1, int bv = 2) : A(av), b(bv) {
        cout << "BV constructor\n";
    }

    virtual ~BV() {
        cout << "BV destructor\n";
    }
};

class CV : virtual public A {
protected:
    int c;
public:
    CV(int av = 1, int cv = 3) : A(av), c(cv) {
        cout << "CV constructor\n";
    }

    virtual ~CV() {
        cout << "CV destructor\n";
    }
};

class DV : public BV, public CV {
protected:
    int d;
public:
    DV() : A(100), BV(10, 20), CV(30, 40), d(50) {
        cout << "DV constructor\n";
    }

    ~DV() {
        cout << "DV destructor\n";
    }

    void show() const {
        cout << "Class DV with virtual inheritance\n";
        cout << "A value = " << a << endl;
    }
};

void task1() {
    cout << "\n========== TASK 1 ==========\n";

    cout << "\n--- Without virtual inheritance ---\n";
    D obj1;
    obj1.show();

    cout << "\nSizes without virtual inheritance:\n";
    cout << "Size of A = " << sizeof(A) << endl;
    cout << "Size of B = " << sizeof(B) << endl;
    cout << "Size of C = " << sizeof(C) << endl;
    cout << "Size of D = " << sizeof(D) << endl;

    cout << "\n--- With virtual inheritance ---\n";
    DV obj2;
    obj2.show();

    cout << "\nSizes with virtual inheritance:\n";
    cout << "Size of A = " << sizeof(A) << endl;
    cout << "Size of BV = " << sizeof(BV) << endl;
    cout << "Size of CV = " << sizeof(CV) << endl;
    cout << "Size of DV = " << sizeof(DV) << endl;
}

/* ============================================================
   TASK 2.7
   Abstract class with virtual function: progression sum
   ============================================================ */

class Progression {
protected:
    double first;
    double value;

public:
    Progression(double f = 1, double v = 1) : first(f), value(v) {
        cout << "Progression constructor\n";
    }

    virtual ~Progression() {
        cout << "Progression destructor\n";
    }

    virtual double sum(int n) const = 0;
    virtual void print() const = 0;
};

class ArithmeticProgression : public Progression {
public:
    ArithmeticProgression(double a0 = 1, double d = 1)
        : Progression(a0, d) {
        cout << "ArithmeticProgression constructor\n";
    }

    ~ArithmeticProgression() {
        cout << "ArithmeticProgression destructor\n";
    }

    double sum(int n) const override {
        double an = first + n * value;
        return (n + 1) * (first + an) / 2.0;
    }

    void print() const override {
        cout << "Arithmetic progression: a0 = " << first
            << ", d = " << value << endl;
    }
};

class GeometricProgression : public Progression {
public:
    GeometricProgression(double a0 = 1, double r = 2)
        : Progression(a0, r) {
        cout << "GeometricProgression constructor\n";
    }

    ~GeometricProgression() {
        cout << "GeometricProgression destructor\n";
    }

    double sum(int n) const override {
        if (value == 1)
            return first * (n + 1);

        double an = first * pow(value, n);
        return (first - an * value) / (1 - value);
    }

    void print() const override {
        cout << "Geometric progression: a0 = " << first
            << ", r = " << value << endl;
    }
};

void task2() {
    cout << "\n========== TASK 2.7 ==========\n";

    ArithmeticProgression ap(2, 3);
    GeometricProgression gp(2, 2);

    Progression* arr[2];
    arr[0] = &ap;
    arr[1] = &gp;

    int n = 5;

    for (int i = 0; i < 2; i++) {
        arr[i]->print();
        cout << "Sum for n = " << n << " is " << arr[i]->sum(n) << endl;
    }
}

/* ============================================================
   TASK 3.7
   Multiple inheritance: Worker, Woman, WorkerWoman
   ============================================================ */

class Worker {
protected:
    string name;
    double salary;

public:
    Worker(string n = "Unknown", double s = 0)
        : name(n), salary(s) {
        cout << "Worker constructor\n";
    }

    Worker(const Worker& other)
        : name(other.name), salary(other.salary) {
        cout << "Worker copy constructor\n";
    }

    virtual ~Worker() {
        cout << "Worker destructor\n";
    }

    friend ostream& operator<<(ostream& out, const Worker& obj) {
        out << "Name: " << obj.name << endl;
        out << "Salary: " << obj.salary << endl;
        return out;
    }

    friend istream& operator>>(istream& in, Worker& obj) {
        cout << "Enter worker name: ";
        in >> obj.name;
        cout << "Enter salary: ";
        in >> obj.salary;
        return in;
    }
};

class Woman {
protected:
    int age;
    string familyStatus;

public:
    Woman(int a = 18, string status = "Single")
        : age(a), familyStatus(status) {
        cout << "Woman constructor\n";
    }

    Woman(const Woman& other)
        : age(other.age), familyStatus(other.familyStatus) {
        cout << "Woman copy constructor\n";
    }

    virtual ~Woman() {
        cout << "Woman destructor\n";
    }

    friend ostream& operator<<(ostream& out, const Woman& obj) {
        out << "Age: " << obj.age << endl;
        out << "Family status: " << obj.familyStatus << endl;
        return out;
    }

    friend istream& operator>>(istream& in, Woman& obj) {
        cout << "Enter age: ";
        in >> obj.age;
        cout << "Enter family status: ";
        in >> obj.familyStatus;
        return in;
    }
};

class WorkerWoman : public Worker, public Woman {
private:
    string position;

public:
    WorkerWoman(string n = "Unknown", double s = 0,
        int a = 18, string status = "Single",
        string p = "Worker")
        : Worker(n, s), Woman(a, status), position(p) {
        cout << "WorkerWoman constructor\n";
    }

    WorkerWoman(const WorkerWoman& other)
        : Worker(other), Woman(other), position(other.position) {
        cout << "WorkerWoman copy constructor\n";
    }

    ~WorkerWoman() {
        cout << "WorkerWoman destructor\n";
    }

    friend ostream& operator<<(ostream& out, const WorkerWoman& obj) {
        out << "Worker-woman information:\n";
        out << "Name: " << obj.name << endl;
        out << "Salary: " << obj.salary << endl;
        out << "Age: " << obj.age << endl;
        out << "Family status: " << obj.familyStatus << endl;
        out << "Position: " << obj.position << endl;
        return out;
    }

    friend istream& operator>>(istream& in, WorkerWoman& obj) {
        cout << "Enter name: ";
        in >> obj.name;
        cout << "Enter salary: ";
        in >> obj.salary;
        cout << "Enter age: ";
        in >> obj.age;
        cout << "Enter family status: ";
        in >> obj.familyStatus;
        cout << "Enter position: ";
        in >> obj.position;
        return in;
    }
};

void task3() {
    cout << "\n========== TASK 3.7 ==========\n";

    WorkerWoman ww1("Anna", 25000, 30, "Married", "Manager");

    cout << "\nOriginal object:\n";
    cout << ww1;

    WorkerWoman ww2 = ww1;

    cout << "\nCopied object:\n";
    cout << ww2;

    cout << "\nTesting input from keyboard:\n";
    WorkerWoman ww3;
    cin >> ww3;

    cout << "\nKeyboard object:\n";
    cout << ww3;
}

/* ============================================================
   MAIN
   ============================================================ */

int main() {
    srand(time(0));

    int choice;

    do {
        cout << "\n========== LAB 6 MENU ==========\n";
        cout << "1. Task 1 - Virtual and non-virtual inheritance\n";
        cout << "2. Task 2.7 - Progression sum\n";
        cout << "3. Task 3.7 - Multiple inheritance\n";
        cout << "4. Run all tasks\n";
        cout << "0. Exit\n";
        cout << "Choose option: ";
        cin >> choice;

        switch (choice) {
        case 1:
            task1();
            break;

        case 2:
            task2();
            break;

        case 3:
            task3();
            break;

        case 4:
            task1();
            task2();
            task3();
            break;

        case 0:
            cout << "Program finished.\n";
            break;

        default:
            cout << "Wrong choice. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}