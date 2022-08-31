//
// Created by USER on 8/27/2022.
//

#ifndef PRACTICE_EX4_H
#define PRACTICE_EX4_H
#include <memory>
#include <iostream>
#include <vector>
using namespace std;
//void foo(int i) {
//    cout << "foo with call by value " << i << endl;
//    i++;
//    cout << "i is now " << i << endl;
//}

void foo(int& i) {
    cout << "foo with call by reference " << i << endl;
    i++;
    cout << "i is now " << i << endl;
}


void foo(const int& i) {
    cout << "foo with call by reference to const " << i << endl;
    //   i++;
    cout << "i is now " << i << endl;
}


void foo(int&& i) {
    cout << "foo with call by rvalue reference " << i << endl;
    i++;
    cout << "i is now " << i << endl;
}

int return_an_int() {
    static int i = 10;
    i++;
    return i;
}

void ex4_1(void) {
    int int1 = 6;
    foo(17);
    foo(int1);
    cout << "int1 is now " << int1 << endl;
    foo(move(int1));
    cout << "int1 is now " << int1 << endl;
    foo(return_an_int());
}

/**targil 2 **/

class Thing1 {
public:
    Thing1() : i (++count) {cout << "Thing1 " << i << " creation" << endl;}
    ~Thing1 () {cout << "Thing1 " << i << " destruction" << endl;}
    int get_i() const {return i;}
private:
    int i;
    static int count;
};

int Thing1::count = 0;

// create a Thing1, but return a unique_ptr to it - ownership is transferred!
unique_ptr<Thing1> create_Thing1() {

    /*
    TODO1: create a new Thing1, pointed by a uniqe_ptr named p, to be returned in the end
    */
    unique_ptr<Thing1> p = make_unique<Thing1>();
    cout << "in create_Thing1: p points to Thing1 " << p->get_i() << endl;

    return p;
}

void refer_to_it(unique_ptr<Thing1>& p)
{
    cout << "in refer_to_it: p points to Thing1 " << p->get_i() << endl;
    cout << "leaving refer_to_it" << endl;
}

void take_it(unique_ptr<Thing1> p)
{
    cout << "in take_it: p points to Thing1 " << p->get_i() << endl;
    cout << "leaving take_it" << endl;
}


int ex4_2(void) {
    //Scope 1: in a scope, let's create a Thing1 owned by a unique ptr, then leave the scope.
    {
        cout << "\nEntering main scope 1" << endl;
        unique_ptr<Thing1> p = create_Thing1();

        cout << "in main scope 1: p points to Thing1 " << p->get_i() << endl;
        unique_ptr<Thing1> p2;

        cout << "Leaving main scope 1" << endl;
    }

    // Scope 2: create another Thing1, give it to function that refers to it.
    {
        cout << "\nEntering main scope 2" << endl;
        unique_ptr<Thing1> p = create_Thing1();
        cout << "in main scope 2: p points to Thing1 " << p->get_i() << endl;

        refer_to_it(p);

        /*
		TODO2: check whether p still owns anyThing1?
		*/
        if(p) cout << "p is points to: "<<p->get_i()<<endl;
        else cout<<"p is empty"<<endl;
        cout << "Leaving main scope 2" << endl;
    }

    // Scope 3: create another Thing1, call to take_it function
    {
        cout << "\nEntering main scope 3" << endl;
        unique_ptr<Thing1> p = create_Thing1();
        cout << "in main scope 3: p points to Thing1 " << p->get_i() << endl;

        /*
		TODO3:
		call take_it function and transfer ownership to it
		check whether p still owns anyThing1?
		*/
        take_it(move(p));

        if(p) cout << "p is points to: "<<p->get_i()<<endl;
        else cout<<"p is empty"<<endl;

        cout << "Leaving main scope 3" << endl;
    }

    // Scope 4: create some Thing1s, pointed to with unique_ptr, and store them in a vector
    {
        cout << "\nEntering main scope 4" << endl;
        vector<unique_ptr<Thing1>> v;

        /*
        TODO4: push_back new Thing1 objects, owned by unique_ptr, to v
        */
        v.push_back(make_unique<Thing1>());
        v.push_back(create_Thing1());
        unique_ptr<Thing1> p = move(v[1]);
        cout << "in main scope 4: v[1] points to Thing1 " << p->get_i() << endl;


        cout << "in main scope 4: contents of v" << endl;
        for(auto it = v.begin(); it != v.end(); ++it) {
            if(*it)
                cout << "Thing1 " << (*it)->get_i() << endl;
            else
                cout << "noThing1" << endl;
        }

        // if we want to get the unique_ptr, we have a problem
        cout << "in main scope 4: contents of v" << endl;
        /*
		TODO5: Solve the following compilation error in order to have proper p
		*/
        for(auto it = v.begin(); it != v.end(); ++it) {
            unique_ptr<Thing1>& p = *it; // COMILATION ERROR:
            if(p) cout << "p is points to: "<<p->get_i()<<endl;
            else cout<<"p is empty"<<endl;
        }

        cout << "Leaving main scope 4" << endl;
    }

    cout << "Done" << endl;
    return 0;
}
template<class T>
class Matrix {
    std::array<int,2> dim;
    T* elem; // pointer to size() elements of type T
    int i;
    static int count;
public:
    Matrix(int d1, int d2) : i(count++), dim{d1,d2}, elem{new T[d1*d2]} {
        cout<<"default constructor"<<i<<endl;
    }
    int size() const { return dim[0]*dim[1]; }
    // copy constructor
    Matrix(const Matrix& m):i(count++),  dim(m.dim), elem{new T[m.size()]}{
        copy(m.elem, m.elem+m.size(), elem);
        cout<<"copy constructor"<<i<<endl;
    }
    // move constructor
    Matrix(Matrix&& a):i(a.i),  dim{a.dim}, elem{a.elem}{
        a.dim = {0,0};
        a.elem = nullptr;

        cout<<"move constructor"<<i<<endl;
    }
    // copy assignment
    Matrix& operator=(const Matrix& m){
        if(dim[0] != m.dim[0] || dim[1] != m.dim[1])
            throw runtime_error("bad size in Matrix =");
        copy(m.elem, m.elem + m.size(), elem);
        cout<<"copy assignment"<<i<<endl;
        return *this;
    }
    Matrix& operator=(Matrix&& m){// move assignment
        swap(dim, m.dim);
        swap(elem,m.elem);
        cout<<"move assignment"<<i<<endl;

        return *this;
    }

    ~Matrix(){// destructor
        delete[] elem;
        count--;
        cout<<"destructor "<<i<<endl;
    }

    // ...

};
template<class T>
int Matrix<T>::count = 0;
void ex4_3(){
    Matrix<int> m1(4,4);
    Matrix<int> m2 = m1;
    Matrix<int> m3 = move(m1);
    Matrix<int> m4(4,4);
    m4 = move(m3);
    m3 = m2;

    cout<<"m1: "<<&m1<< endl;
    cout<<"m2: "<<&m2<< endl;
    cout<<"m3: "<<&m3<< endl;
}


#endif //PRACTICE_EX4_H
