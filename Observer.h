#include <utility>

//
// Created by USER on 9/1/2022.
//

#ifndef PRACTICE_OBSERVER_H
#define PRACTICE_OBSERVER_H

class ObserverInt{
public:
    virtual void update(string&) = 0;
    virtual ~ObserverInt(){}
};

class SubjectInt{
public:
    virtual void attach(shared_ptr<ObserverInt>  ods) = 0;
    virtual void detach(shared_ptr<ObserverInt> ods) = 0;
    virtual void notify() = 0;
    virtual ~SubjectInt(){};
};

class ConcreteSubject : public SubjectInt{
private:
    list<shared_ptr<ObserverInt>> obs_list_;
    string data;
public:
    void attach(shared_ptr<ObserverInt> obs)override{
        obs_list_.push_back(move(obs));
    }
    void detach(shared_ptr<ObserverInt> obs)override{
        obs_list_.remove(obs);
    }
    void notify()override{
        for_each(obs_list_.begin(), obs_list_.end(), [this](const shared_ptr<ObserverInt>& obs){
            obs->update(data);
        });
    }
    void InitData(string new_data){
        data = std::move(new_data);
        cout<<"data has been initial ... \n\t sending data to observers"<<endl;
        notify();
    }
    void ChangData(string new_data){
        data = std::move(new_data);
        cout<<"data has been changed ... \n\t sending changed data to observers"<<endl;
        notify();
    }
};

class Observer: public ObserverInt{
private:
    shared_ptr<ConcreteSubject> concreteSubject_ptr;
    static int count;
    int num;
public:
    Observer(shared_ptr<ConcreteSubject> subject): concreteSubject_ptr(std::move(subject)), num(count++){
        concreteSubject_ptr->attach(make_shared<Observer>(*this));
        cout<<"Observer"<<num<<" created...\n";
    }
    Observer(const Observer& other) = default;
    void update(string & data) override{
        cout<<"Observer"<<num<<" received data from subject\n"<<data<<endl;
    }
    void removeObserver(){
        concreteSubject_ptr->detach(make_shared<Observer>(*this));
    }
};

int Observer::count = 0;

void testObserver(){
    shared_ptr<ConcreteSubject> subject = make_shared<ConcreteSubject>();
    auto *ob1 = new Observer(subject);
    auto *ob2 = new Observer(subject);
    auto *ob3 = new Observer(subject);
    subject->InitData("this is the initial data");
    ob3->removeObserver();
    subject->ChangData("this is the new data");
};


#endif //PRACTICE_OBSERVER_H
