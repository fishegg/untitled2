#ifndef LINK_H
#define LINK_H


template <class E> class Link
{
public:
    E element;
    Link<E> *next;
    Link(const E& elemval, Link* nextval = NULL);
    Link(/*Link* nextval = NULL*/);
};

#endif // LINK_H
