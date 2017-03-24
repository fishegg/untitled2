#ifndef LQUEUE_H
#define LQUEUE_H
#include "link.h"
#include <assert.h>

template<typename E> class LQueue{
private:
    Link<E>* front;
    Link<E>* rear;
    int size;
public:
    LQueue(){
        front = rear = new Link<E>();
        size = 0;
    }

    ~LQueue(){
        cout<<"~LQueue"<<endl;
        clear();
        //delete front;
    }

    void clear(){
        Link<E>* temp = NULL;
        while(front->next != NULL){
            cout<<front->next->element<<endl;
            temp = front->next;
            delete front;
            front = temp;
        }
        front = NULL;
        delete temp;
        temp = NULL;
        size = 0;
    }

    void enqueue(const E& it){
        rear->next = new Link<E>(it, NULL);
        rear = rear->next;
        cout<<"enqueue"<<rear->element<<endl;
        size++;
    }

    E dequeue(){
        assert(size != 0);
        E it = front->next->element;
        Link<E>* ltemp = front->next;
        front->next = ltemp->next;
        if(rear == ltemp){
            rear = front;
        }
        delete ltemp;
        size--;
        cout<<"dequeue"<<it<<endl;
        return it;
    }

    const E& frontvalue() const{
        return front->next->element;
    }

    int length() const{
        return size;
    }
};

#endif // LQUEUE_H
