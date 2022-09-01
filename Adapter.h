//
// Created by USER on 8/31/2022.
//

#ifndef PRACTICE_ADAPTER_H
#define PRACTICE_ADAPTER_H

#include "Composite.h"
#include "Decorator.h"
using namespace std;
/**
 * the Graphic class is the Target
 * the TexBox class is the Adaptee
 * the TextShape is the Adapter
 * in this implementation Adapter has a  Adaptee
 * there is also a version of Adapter is a Adaptee
 */
class TextBox{
public:
    string text;
    int font;
    Color color;

    TextBox(string text, int font, Color c): text(text), font(font), color(c){}
    /**
     * specific draw request
     * @param component
     */
    void drawText(string::iterator i){
        if(font == 1)
            for_each(text.begin(), text.end(), [](char c){toupper(c);});
        else
            for_each(text.begin(), text.end(), [](char c){tolower(c);});
        copy(text.begin(),text.end(), i);
    }
};

class TextShape: public Graphic{
private:
    TextBox *adaptee_;
    Point position;
public:
    TextShape(TextBox *tb, int x, int y): adaptee_(tb) ,position(x, y){};
    void setColor(Color c)override{
        adaptee_->color = c;
    }
    void setText(string  text){
         adaptee_->text = text;
    }
    void setSize(int length, int width)override{}
    void move(int x, int y)override{
        position.x = x;
        position.y = y;
    }
    void draw(vector<string> &board)override{
        adaptee_->drawText(board[position.y].begin()+position.x);
    }
    int get_length()override{
        return 0;
    }
    int get_width()override {
        return 0;
    }
    Point get_position() override{
        return position;
    }
    Color getColor()override{
        return white;
    }

};

void testComposite(){
    shared_ptr<Composite> component1 = make_shared<Composite>(10,20, 0,0, white);
    shared_ptr<Graphic> borderDecorator1 = make_shared<BorderDecorator>(component1, red);
    component1->add(borderDecorator1);
    shared_ptr<Graphic> rectangle = make_shared<Rectangle>(green, 3,3, 5, 5 );
    shared_ptr<Graphic> ts = make_shared<TextShape>(new TextBox("test", 1, red), 5,2);
    shared_ptr<Graphic> borderDecorator2 = make_shared<BorderDecorator>(rectangle, blue);
    component1->add(rectangle);
    component1->add(borderDecorator2);
    component1->add(ts);
    component1->draw();

}

#endif //PRACTICE_ADAPTER_H
