//
// Created by USER on 8/31/2022.
//

#ifndef PRACTICE_DECORATOR_H
#define PRACTICE_DECORATOR_H
#include <utility>

#include "Composite.h"

class Decorator: public Graphic{
protected:
    shared_ptr<Graphic> widget_;
public:
    Decorator(shared_ptr<Graphic>  widget): widget_(std::move(widget)){ }

    void move(int x, int y) {
        widget_->move(x, y);
    }
    void setSize(int length, int width) {
        widget_->setSize(length, width);
    }
    void draw(vector<string> &board) override {
        cout<<"in Decorator::draw\n";
        widget_->draw(board);
    }
    void setColor(Color color) {
        widget_->setColor(color);
    };
    int get_length()override{
        return widget_->get_length();
    }
    int get_width()override {
        return widget_->get_width();
    }
    Point get_position() override{
        return widget_->get_position();
    }
    Color getColor()override{
        return widget_->getColor();
    }

};

class BorderDecorator: public Decorator{
private:
    Color borderColor;
public:
    BorderDecorator(shared_ptr<Graphic> widget, Color c): Decorator(std::move(widget)), borderColor(c){
        cout<<"creat BorderDecorator\n";
    }
    void draw(vector<string> &board)override {

        cout<<"in BorderDecorator::draw\n";

        for (int i = get_position().x; i < get_position().x + get_length(); i++) {
            board[i][get_position().y] = paint(borderColor);
            board[i][get_position().y + get_width()-1] = paint(borderColor);
        }
        string::iterator i_top = board[get_position().y].begin() +get_position().x + 1;
        replace(i_top, i_top + get_width()-1, paint(widget_->getColor()), paint(borderColor));
        string::iterator i_bottom = board[get_position().y+get_length()-1].begin()+get_position().x + 1;
        replace(i_bottom, i_bottom + get_width()-1, paint(widget_->getColor()), paint(borderColor));

    }
};




#endif //PRACTICE_DECORATOR_H
