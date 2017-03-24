#ifndef LSTACK_H
#define LSTACK_H
#include "link.h"

template <typename E> class LStack{
private:
    Link<E>* top;
    int size;
public:
    LStack(){
        top = NULL;
        size = 0;
    }

    ~LStack(){
        clear();
    }

    void clear(){
        while(top != NULL){
            Link<E>* temp = top;
            top = top->next;
            delete temp;
        }
        size = 0;
    }

    void push(const E& it){
        top = new Link<E>(it, top);
        size++;
    }

    E pop(){
        E it = top->element;
        Link<E>* ltemp = top->next;
        delete top;
        top = ltemp;
        size--;
        return it;
    }

    const E& topvalue() const{
        return top->element;
    }

    int length() const{
        return size;
    }
};

#endif // LSTACK_H
