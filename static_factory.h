//
// Created by USER on 8/29/2022.
//

#ifndef PRACTICE_STATIC_FACTORY_H
#define PRACTICE_STATIC_FACTORY_H
#include <iostream>
#include <memory>
using namespace std;

class NutritionFacts {
    int servingSize;
    int servings;
    int calories;
    int fat;
    int carbohydrate;
    int sodium;
public:
    class Builder {
        int servingSize;
        int servings;
        int calories_;
        int fat_;
        int carbohydrate_;
        int sodium_;
    public:
        Builder(int ss, int s) :
                servingSize(ss), servings(s),
                calories_(0), fat_(0), carbohydrate_(0), sodium_(0) {}

        int getServingSize() const { return servingSize; }
        int getCalories() const { return calories_; }
        int getCarbohydrate() const { return carbohydrate_; }
        int getFat() const { return fat_; }
        int getServings() const { return servings; }
        int getSodium() const { return sodium_; }

        Builder * calories(int c) {
            calories_ = c;
            return this;
        }
        Builder * carbohydrate(int c) {
            carbohydrate_ = c;
            return this;
        }
        Builder * fat(int f) {
            fat_ = f;
            return this;
        }
        Builder * sodium(int s) {
            sodium_ = s;
            return this;
        }
        NutritionFacts * build()
        {
            if (fat_ > calories_) throw "Fat cannot be greater than calories";
            else return new NutritionFacts(this);
        }
    };

    static unique_ptr<Builder> getBuilder(int servingSize, int servings)
    {
        /* YOUR IMPLEMENTATION IS NEEDED HERE */
        static unique_ptr<Builder> ptr = make_unique<Builder>(servingSize, servings);
        return move(ptr);
    }

protected:
    NutritionFacts(Builder *b)
    {
        /* YOUR IMPLEMENTATION IS NEEDED HERE */
        this->servings = b->getServings();
        this->servingSize = b->getServingSize();
        this->calories = b->getCalories();
        this->fat = b->getFat();
        this->carbohydrate = b->getCarbohydrate();
        this->sodium = b->getSodium();
    }
};

void test_NutritionFacts(void) {

    /* YOUR CODE IS NEEDED HERE FOR GENERATING THE FOLLOWING NutritionFacts INSTANCE:
    serving size: 100
    servings: 8
    calories: 156
    sodium: 200
    fat: 100
    */
    NutritionFacts::Builder * builder = NutritionFacts::getBuilder(100, 8).get();
    NutritionFacts * nutritionFacts = builder->calories(156)->sodium(200)->fat(100)->build();
}
#endif //PRACTICE_STATIC_FACTORY_H
