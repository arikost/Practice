//
// Created by USER on 8/31/2022.
//

#ifndef PRACTICE_PROXY_H
#define PRACTICE_PROXY_H
class ElementProxy{
public:
    virtual void Request() const = 0;
};
class ActualElement: public ElementProxy{
public:
    void Request() const override{
        cout<<"ActualElement: Handling request.\n";
    }
};
class Proxy: public ElementProxy{
private:
    unique_ptr<ActualElement> actualElement_;
    bool CheckAccess()const{
        std::cout << "Proxy: Checking access prior to firing a actual request.\n";
        if(actualElement_)
            return true;
        else
            return false;
    }
    void LogAccess() const {
        std::cout << "Proxy: Logging the time of request.\n";
    }

public:
    Proxy(unique_ptr<ActualElement> actualElement): actualElement_(std::move(actualElement)){}
    void Request() const override {
        if (this->CheckAccess()) {
            this->actualElement_->Request();
            this->LogAccess();
        }
    }
};
void testProxy(){
    unique_ptr<ActualElement> element = make_unique<ActualElement>();
    element->Request();
    Proxy * proxy = new Proxy(std::move(element));
    proxy->Request();
    delete proxy;
}

#endif //PRACTICE_PROXY_H
