//
// Created by USER on 9/1/2022.
//

#ifndef PRACTICE_VISITOR_H
#define PRACTICE_VISITOR_H

class ConElementA;
class ConElementB;

class Visitor{
public:
    virtual void visitA(ConElementA * element) = 0;
    virtual void visitB(ConElementB * element) = 0;
};

class Element{
public:
    virtual void Accept(Visitor*) = 0;
};

class ConElementA : public Element{
public:
    void Accept(Visitor * v){
        v->visitA(this);
    }
    string A_Method(){return "ElementA";}
};
class ConElementB : public Element{
public:
    void Accept(Visitor * v){
        v->visitB(this);
    }
    string B_Method(){return "ElementB";}
};

class ConVisitor1: public Visitor{
public:
    void visitA(ConElementA * elementA)override{
        cout<< elementA->A_Method()<<" ConVisitor1"<<endl;
    }
    void visitB(ConElementB * elementB)override{
        cout<< elementB->B_Method()<<" ConVisitor1"<<endl;
    }
};
class ConVisitor2: public Visitor{
public:
    void visitA(ConElementA * elementA)override{
        cout<< elementA->A_Method()<<" ConVisitor2"<<endl;
    }
    void visitB(ConElementB * elementB)override{
        cout<< elementB->B_Method()<<" ConVisitor2"<<endl;
    }
};

void testVisitor(){
    array<Element*, 2> elementArr = {new ConElementA(), new ConElementB};
    ConVisitor1 * v1 = new ConVisitor1();
    ConVisitor2 * v2 = new ConVisitor2();
    for(auto &elem : elementArr)
        elem->Accept(v1);
    for(auto &elem : elementArr)
        elem->Accept(v2);
}


#endif //PRACTICE_VISITOR_H
