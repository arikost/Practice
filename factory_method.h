//
// Created by USER on 8/29/2022.
//

#ifndef PRACTICE_FACTORY_METHOD_H
#define PRACTICE_FACTORY_METHOD_H
#include <iostream>

using namespace std;
//the product interface
class Doc{
public:
    virtual ~Doc(){}
    virtual void open() const = 0;
    virtual void close() const = 0;
    virtual void save() const = 0;
};
//implementation for product type 1
class ExcelDoc : public Doc{
public:
    ExcelDoc(){cout << "new ExcelDoc created"<<endl;}
    void open() const override{
        cout<<"open Excel document"<<endl;
    }
    void close() const override{
        cout<<"close Excel document"<<endl;
    }
    void save() const override{
        cout<<"save Excel document"<<endl;
    }
};
//implementation for product type 2

class PowerPointDoc : public Doc{
public:
    PowerPointDoc(){cout<<"new PowerPointDoc created"<<endl;}
    void open() const override{
        cout<<"open PowerPoint document"<<endl;
    }
    void close() const override{
        cout<<"close PowerPoint document"<<endl;
    }
    void save() const override{
        cout<<"save PowerPoint document"<<endl;
    }
};


//the creator class
class App{
protected:
    Doc *doc;
    virtual Doc * createDoc() const = 0;
public:
    void newDoc() {
        doc = this->createDoc();
    }
    void openDoc()const{
        doc->open();
    }
    void saveDoc()const{
        doc->save();
    }
    void closeDoc() const{
        doc->close();
    }
    virtual ~App(){};
};


//Standard creator
template<class DocType>
class  StandardCreatorApp: public App{
protected:
    virtual Doc * createDoc() const override{
        return new DocType();
    }
};

void testFactoryMethod(){
    cout<< "testing factory method implementation///////////"<<endl;
    App * excel = new StandardCreatorApp<ExcelDoc>();
    excel->newDoc();
    excel->openDoc();
    excel->saveDoc();
    excel->closeDoc();
    delete excel;
    App * pp = new StandardCreatorApp<PowerPointDoc>();
    pp->newDoc();
    pp->openDoc();
    pp->saveDoc();
    pp->closeDoc();
    delete pp;
}


#endif //PRACTICE_FACTORY_METHOD_H
