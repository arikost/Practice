//
// Created by USER on 8/30/2022.
//

#ifndef PRACTICE_ABSTRACT_FACTORY_H
#define PRACTICE_ABSTRACT_FACTORY_H

using namespace std;

class Player{
public:
    virtual string getPosition() const = 0;
    virtual void setPosition(string&)  = 0;
    virtual string getName() const = 0;
    virtual ~Player(){};
};

class Defender: public Player{
protected:
    string position;
    string name;
public:
    Defender(string & name, string & position){
        this->position = position;
        this->name = name;
        cout<<"Defender created"<<endl;
    }
    string getPosition() const override{
        return position;
    }
    void setPosition(string & pos) override{
        this->position = pos;
    }
    string getName() const override{
        return name;
    }
};

class Attacker: public Player{
protected:
    string position;
    string name;
public:
    Attacker(string & name, string & position){
        this->name = name;
        this->position = position;
        cout<<"Attacker created"<<endl;
    }
    string getPosition() const override{
        return position;
    }
    void setPosition(string & pos) override{
        this->position = pos;
    }
    string getName() const override{
        return name;
    }
};

class PlayerFactory{
public:
    Defender* makeDefender(string  name, string  pos){return new Defender(name, pos);}
    Attacker* makeAttacker(string  name, string  pos){return new Attacker(name,pos);}
};



void testAF(){
    PlayerFactory * pf = new PlayerFactory();
    Defender* def = pf->makeDefender( "benado",  "fullback");
    Attacker* att = pf->makeAttacker("atzili", "left winger");
    cout<<"defender name: "<<def->getName()<<" position: "<<def->getPosition()<<endl;
    cout<<"attacker name: "<<att->getName()<<" position: "<<att->getPosition()<<endl;
}
#endif //PRACTICE_ABSTRACT_FACTORY_H
