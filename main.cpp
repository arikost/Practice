#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include "ex1.h"
#include "ex2.h"
#include "ex3.h"
#include "ex4.h"
#include "Singelton.h"
#include "static_factory.h"
#include "factory_method.h"
#include "Abstract_Factory.h"
#include "Builder.h"
#include "Adapter.h"
#include "Bridge.h"
#include "Proxy.h"
#include "Observer.h"
#include "Visitor.h"
//class Singleton_destroyer{
//public:
//    ~Singleton_destroyer(){
//        cout<< "Singleton is destroy"<<endl;
//        delete Singleton::ptr_inst;
//    }
//}sd;

class A{
    vector<string> v;
public:
    void addName(const string & s){v.push_back(s);}
    void addName(const string&& s){v.push_back(move(s));}
};
class B{
    vector<string> v;
public:
    void addName(const string s){v.push_back(move(s));}
};


int main(int argc, char** argv) {
    string name("arik");
    A  a;
    B  b;
    a.addName(name);
    a.addName("sadas");
    b.addName(name + "ostrovsky");


//    ex2("C:\\Dev\\Clion\\honhot\\Practice\\test");
//    int arr[5] = {4,2,5,7,1};
//    int * ptr = new int();
//    SortCopy(arr, arr+5, ptr, [](int a, int b){return a<b;});
//    for(int i=0; i < 5; i++)
//        cout<<*(ptr+i)<<endl;
//    delete ptr;
//    pair<int*, int> v[5];
//    keep_it_real(arr, arr+5, v);
//    for(int i=0; i<5; i++)
//        cout<< v[i].first<<" "<< v[i].second<<endl;
//    ex3_1();
//    ex3_2(argc, argv);
//    ex3_3();
//    ex2_2();
//    map<string, int> map;
//    map["a"] =  1;
//    map["b"] =  5;
//    map["c"] =  2;
//    map["d"] =  7;
//    map["e"] =  4;
//    map["f"] =  3;
//    map["g"] =  6;
//
//    showCommonWords(map.begin(), map.end(), 5);
//    ex2_3();
//    ex4_1();
//    ex4_2();
//    ex4_3();
//    string s1 = "arik";
//    string s2 = "ostrovsky";
//    string s3 = "dadad";
//    string s4 = "gggg";
//    Singleton::getInstance().addString(s1);
//    Singleton::getInstance().addString(s2);
//    Singleton::getInstance().addString(s3);
//    Singleton::getInstance().addString(s4);
//    for(int i=0; i < Singleton::getInstance().getDataSize();i++)
//        cout<<Singleton::getInstance().getStringAt(i)<<endl;
//    test_NutritionFacts();
//    testFactoryMethod();
//    testAF();
//    testBuilder();
//    testComposite();
//    testBridge();
//    testProxy();
//    testObserver();
//    testVisitor();
    return 0;
}
