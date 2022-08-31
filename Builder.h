//
// Created by USER on 8/30/2022.
//

#ifndef PRACTICE_BUILDER_H
#define PRACTICE_BUILDER_H
/**
 * Mael class is the product
 */
using namespace std;
class Meal{
public:
    string berger;
    string sideDish;
    string drink;
    string dessert;
    void get_meal()const{
        cout<<"berger: "<<berger<<endl;
        cout<<"side dish: "<<sideDish<<endl;
        cout<<"drink: "<<drink<<endl;
        cout<<"dessert: "<<dessert<<endl;
    }
    Meal() = default;
    Meal(const Meal& m) = default;
};
/**
 * Kitchen is the builder interface
 */
class Kitchen{
public:
    virtual ~Kitchen(){}
    virtual void makeBerger(string) const = 0;
    virtual void makeSideDish(string) const = 0;
    virtual void makeDrink(string) const = 0;
    virtual void makeDessert(string) const = 0;
};
/**
 * MacdonaldKitchen class is the ConcreteBuilder that implement the builder interface(Kitchen)
 */
class MacdonaldKitchen: public Kitchen{
private:
    Meal* meal;
public:
    MacdonaldKitchen(){
        this->Reset();
    }
    ~MacdonaldKitchen(){
        delete meal;
    }
    void Reset(){
        this->meal = new Meal();
    }
    /**
     * implementing the builder interface
     */
     void makeBerger(string type) const override{
         meal->berger = type;
     }
     void makeSideDish(string type) const override{
         meal->sideDish = type;
     }
     void makeDrink(string type)const override{
         meal->drink = type;
     }
     void makeDessert(string type)const override{
         meal->dessert = type;
     }
    /**
        * Please be careful here with the memory ownership. Once you call
        * GetProduct the user of this function is responsable to release this
        * memory. Here could be a better option to use smart pointers to avoid
        * memory leaks
        */
     unique_ptr<Meal> finishOrder(){
         unique_ptr<Meal> meal_ptr = make_unique<Meal>(*meal);
         Reset();
         return move(meal_ptr);
     }
};

/**
 * class Cashier is the Director
 */
class Cashier{
private:
    Kitchen* kitchen;
public:
    void open_register(Kitchen * c1){
        cout<<"the register is open"<<endl;
        this->kitchen = c1;
    }
    void OrderChildrenMeal(){
        cout<<"costumer order Children meal"<<endl;
        kitchen->makeBerger("Small berger");
        kitchen->makeDrink("Small coke");
        kitchen->makeSideDish("small cheeps");
        kitchen->makeDessert("ice-cream");
    }
    void OrderAdultMeal(){
        cout<<"costumer order Adult meal"<<endl;
        kitchen->makeBerger("double berger with cheese");
        kitchen->makeDrink("large coke");
        kitchen->makeSideDish("mash potato");
        kitchen->makeDessert("apple pie");
    }
};
/**
 * class Costumer is the client
 */
class Costumer{
private:
    Cashier * cashier;
public:
    void goto_Cashier(Cashier * c1){
        this->cashier = c1;
    }
    void order(string size){
        if(size == "Children")
            cashier->OrderChildrenMeal();
        else if(size == "Adult")
            cashier->OrderAdultMeal();
    }

    void eat(unique_ptr<Meal> meal){
        cout<< "costumer eating:\n"
        <<meal->berger<<"\n"
        <<meal->sideDish<<"\n"
        <<meal->drink<<"\n"
        <<meal->dessert<<endl;
    }
};

void testBuilder(){
    MacdonaldKitchen * k = new MacdonaldKitchen();
    Cashier *cashier;
    cashier->open_register(k);
    Costumer *costumer;
    costumer->goto_Cashier(cashier);
    costumer->order("Children");
    costumer->eat(move(k->finishOrder()));
}


#endif //PRACTICE_BUILDER_H
