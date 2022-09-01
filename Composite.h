//
// Created by USER on 8/30/2022.
//

#ifndef PRACTICE_COMPOSITE_H
#define PRACTICE_COMPOSITE_H
#include <list>
#include <functional>
#include <utility>

class Decorator;

using namespace std;
enum Color  {red=0, green, blue, white};

char paint(Color color){
    switch (color) {
        case red:
            return '*';
        case green:
            return '#';
        case blue:
            return '+';
        case white:
            return ' ';
    }
}
struct Point{
    int x, y;
    Point(int xp, int yp){
        x = xp;
        y = yp;
    }
    Point (const Point & p){
        x = p.x;
        y = p.y;
    }
};
/**
 * Compo class (component) is an interface for gui component
 */

class Graphic {
public:
    virtual void move(int x, int y) = 0;

    virtual void setSize(int length, int width) = 0;

    virtual void draw(vector<string> &board) = 0;

    virtual void setColor(Color color) = 0;

    virtual int get_length() = 0;

    virtual int get_width() = 0;

    virtual Point get_position() = 0;
    virtual Color getColor() = 0;
};
/**
 * Leaf
 */
class Rectangle: public Graphic{
protected:
    Color color;
    Point position;
    int length;
    int width;
public:
    Rectangle(Color c, int x, int y, int len, int wid): color(c), position(x,y), length(len), width(wid){ }
    void setColor(Color c) override{
        this->color = c;
    }
    void move(int x, int y)override{
        position.x = x;
        position.y = y;
    }
    void setSize(int length, int width)override{
        this->length = length;
        this->width = width;
    }
    void draw(vector<string> &board)override{
        for(int i = position.x ; i < position.x + width;i++){
            for(int j = position.y ; j< position.y + length; j++){
                board[j][i] = paint(color);
            }
        }
    }
    int get_length()override{
        return length;
    }
    int get_width()override {
        return width;
    }
    Point get_position() override{
        return position;
    }
    Color getColor()override{
        return color;
    }
};

class Composite: public Graphic, public list<shared_ptr<Graphic>>{
protected:
    int length;
    int width;
    Point position;
    vector<string> board;
    Color color;

    void draw(vector<string> &outerBoard)override{
        draw();
        for (int j = position.y; j < position.y + length; j++) {
            for (int i = position.x; i < position.x + width; i++) {
                outerBoard[i][j] = board[i][j];
            }
        }
    }
public:
    Composite(int len, int wid, int x, int y, Color color): length(len), width(wid), position(x,y), color(color){
        string buff;
        for(int i=0; i < length; i++){
            for (int j = 0; j < width; ++j) {
                buff.push_back(paint(this->color));
            }
            board.push_back( buff);
            buff.clear();
        }

    }
    void setColor(Color color){
        this->color = color;
        list<shared_ptr<Graphic>>::const_iterator i;
        for(i = cbegin(); i != cend(); i++)
            i->get()->setColor(color);
    }
    void draw(){
        for(int i=0; i < length; i++){
            for (int j = 0; j < width; ++j) {
                board[i][j] = paint(this->color);
            }
        }
        list<shared_ptr<Graphic>>::const_iterator i;
        for(i = cbegin(); i != cend(); i++)
            i->get()->draw(this->board);
        cout<<"\n\n";
        for_each(board.begin(), board.end(), [](string &line){cout<<line<<endl;});
    }

    void move(int x, int y)override{
        position.x = x;
        position.y = y;
    }
    void setSize(int length, int width)override{
        this->length = length;
        this->width = width;
    }
    void add(shared_ptr<Graphic> graphic){
        this->push_back(graphic);
    }
    void remove(shared_ptr<Graphic> graphic){
        list<shared_ptr<Graphic>>::const_iterator i;
        for(i = cbegin(); i != cend(); i++){
            if(i->get() == graphic.get()){
                this->erase(i);
                break;
            }
        }
    }
    int get_length()override{
        return length;
    }
    int get_width()override {
        return width;
    }
    Point get_position() override{
        return position;
    }
    Color getColor()override{
        return color;
    }

};
#endif //PRACTICE_COMPOSITE_H
