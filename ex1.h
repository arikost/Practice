//
// Created by USER on 8/24/2022.
//


#ifndef PRACTICE_EX1_H
#define PRACTICE_EX1_H
#include <sstream>
#include <iterator>

int lcm(int a, int b);
using namespace std;
class rational {
private:
    int numerator, denominator;
public:
     struct MyException{
        string msg;
        MyException(string m){ msg = m;}
    };
    // Constructors
    rational(){
        this->denominator=1;
        this->numerator=0;
    }          // Zero
    rational(int n){
        this->denominator=1;
        this->numerator=n;

    }       // Equal to n/1
    rational(int n, int d) noexcept(false){
        if(d == 0)
            throw MyException("Error: ATTEMPTING TO DIVIDE BY ZERO");
        this->denominator=d;
        this->numerator=n;

    }  // General case (n/d)

    rational& operator=(int n){
        this->numerator = n;
        this->denominator = 1;
    }

    rational& assign(int n, int d){
        this->numerator = n;
        this->denominator = d;
    }

    // Representation
    int getNum() const{
        return this->numerator;
    }
    int getDenom() const{
        return this->denominator;
    }

    // Arithmetic operators
    rational& operator+= (const rational& r){
        int x = lcm(r.denominator, this->denominator), n_r = r.numerator;
        if(x != denominator){
            this->numerator *= (x / this->denominator);
        }
        if(x != r.denominator){
            n_r *= (x / r.denominator);
        }
        this->numerator += n_r;
        this->denominator = x;
    }
    rational& operator-= (const rational& r){
        int x = lcm(r.denominator, this->denominator), n_r = r.numerator;
        if(x != denominator){
            this->numerator *= (x / this->denominator);
        }
        if(x != r.denominator){
            n_r *= (x / r.denominator);
        }
        this->numerator -= n_r;
        this->denominator = x;

    }
    rational& operator*= (const rational& r){
        this->denominator *= r.denominator;
        this->numerator *= r.numerator;
    }
    rational& operator/= (const rational& r){
        this->denominator *= r.numerator;
        this->numerator *= r.denominator;
    }

    // Comparison operators
    bool operator< (const rational& r) const{
        return (numerator/denominator) < (r.numerator/r.denominator);
    }
    bool operator== (const rational& r) const{
        return (numerator/denominator) == (r.numerator/r.denominator);
    }
    operator string() const noexcept(false) {
        return "n: " + to_string(numerator)+" d: " + to_string(denominator);
    }
    rational(string num_str){
        istringstream iss(num_str);
        vector<string > split_num_str((istream_iterator<string>(iss)), istream_iterator<string>());
        if(split_num_str[0] != "n:")
            throw MyException("Error: syntax error ");
        else
            this->numerator = stoi(split_num_str[1]);
        if(split_num_str[2] != "d:")
            throw MyException("Error: syntax error ");
        else {
            int d = stoi(split_num_str[3]);
            if(d == 0)
                throw MyException("Error: ATTEMPTING TO DIVIDE BY ZERO");
            this->denominator=d;
        }
    }

};
int lcm(int a, int b){
    int hcf = a;
    int temp = b;

    while(hcf != temp)
    {
        if(hcf > temp)
            hcf -= temp;
        else
            temp -= hcf;
    }

    return int((a * b) / hcf);
}

#endif //PRACTICE_EX1_H
