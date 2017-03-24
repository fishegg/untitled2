#ifndef LLIST_H
#define LLIST_H
#include "link.h"


template <typename E> class LList
{
private:
    Link<E>* head;
    Link<E>* tail;
    Link<E>* curr;
    int cnt;

    void init(){
        curr = tail = head = new Link<E>;
        cnt = 0;
    }

    void removeall(){
        while(head != NULL){
            curr = head;
            head = head->next;
            delete curr;
        }
    }

public:
    LList();
    ~LList();
    void clear();
    //void insert(const E& it);
    void append(const E& it);
    void movetostart();
    void movetoend();
    void prev();
    void next();
    int length() const;
    int currpos() const;
    void movetopos(int pos);
    const E& getvalue() const;
    void print();
};

#endif // LLIST_H
