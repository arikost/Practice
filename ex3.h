//
// Created by USER on 8/25/2022.
//

#ifndef PRACTICE_EX3_H
#define PRACTICE_EX3_H
#include <fstream>
#include <deque>
#include <iterator>
#include <iostream>
#include <memory>
using namespace std;

class Thing {
    weak_ptr<Thing> ptr;
    int i;
    static int count;
public:
    Thing() : i(++count) {}
    ~Thing () {cout << "Thing " << i << " destruction" << endl;}
    int get_i() const {return i;}
    void set_ptr(shared_ptr<Thing> p)
    { ptr = p; }
    void print_pointing_to() const	{
        if (ptr.expired())
            cout << "Thing " << i << " is pointing at nothing" << endl;
        else {
            shared_ptr<Thing> p = ptr.lock();
            cout <<  "Thing " << i << " is pointing to Thing " << p->get_i() << endl;
        }
    }
};

int Thing::count = 0;

int ex3_1(void) {

    shared_ptr<Thing> p1(new Thing);
    shared_ptr<Thing> p2(new Thing);
    p1->print_pointing_to();
    p2->print_pointing_to();
    p1->set_ptr(p2);
    p2->set_ptr(p1);
    p1->print_pointing_to();
    p2->print_pointing_to();


/*	A. YOUR IMPLEMENTATION GOES HERE; ACHIEVE THE FOLLOWING OUTPUT:
	-----
	Thing 1 is pointing at nothing
	Thing 2 is pointing at nothing
	Thing 1 is pointing to Thing 2
	Thing 2 is pointing to Thing 1
	Exiting main function
	Thing 2 destruction
	Thing 1 destruction
	-----
*/

    cout << "Exiting main function" << endl;
    return 0;
}
void goo (const char* iname, const char* oname) {
    shared_ptr<fstream> file(new fstream(iname , std::ios::in));
    deque<char> dc;
    istream_iterator<char> r_it(*file);
    while (r_it != istream_iterator<char>() )
        dc.push_front(*r_it++);
    file.get()->close();
    file.get()->open(oname, std::ios::out);
    ostream_iterator<char> w_it(*file,"$");
    copy(dc.begin(),dc.end(),w_it);
    file.get()->close();
}

int ex3_2(int argc, char** argv) {
    if (argc < 3) {
        cerr << "REQUIRED: ifile name followed by ofile name.\n";
        return -1;
    }
    goo(argv[1],argv[2]);
    return 0;
}


class S {
    string first;
public:
    S(const string& r) : first(r) { }
    virtual ~S(){cout<< "distract S "+first<<endl; }
    virtual string operator*() { return first; }
};

class CS: public S {
    string second;
public:
    CS(const string& x, const string& y) : S(x), second(y) { }
    virtual ~CS() { cout << "Computer Scientist\n"; }
    virtual string operator*() { return second; }
};


int ex3_3(void) {
    shared_ptr<CS> a (new CS("Donald", "Knuth"));
    shared_ptr<S> b (new S(*a));

    cout << **a << ", " << **b << endl;
    return 0;
}


#endif //PRACTICE_EX3_H
