//
// Created by USER on 8/28/2022.
//

#ifndef PRACTICE_SINGELTON_H
#define PRACTICE_SINGELTON_H
#include <vector>

class Singleton{
public:
    static Singleton &getInstance(){
        if(ptr_inst == nullptr)
            ptr_inst = new Singleton();
        return *ptr_inst;
    }
    Singleton(const Singleton&) = delete;
    Singleton& operator= (const Singleton&) = delete;
    Singleton(const Singleton&&) = delete;
    Singleton& operator= (const Singleton&&) = delete;

    void addString(string & s){ data.push_back(s); }
    string getStringAt(int i){ return data[i];}
    size_t getDataSize(){return data.size();}

private:
    static Singleton *ptr_inst;
    vector<string> data;
    Singleton();
    ~Singleton(){}
    friend class Singleton_destroyer;
};


Singleton::Singleton() {}
Singleton *Singleton::ptr_inst = nullptr;

#endif //PRACTICE_SINGELTON_H
