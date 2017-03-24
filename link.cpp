#include "link.h"

template <class E>
Link<E>::Link(const E& elemval, Link<E>* nextval = NULL)
{
    element = elemval;
    next = nextval;
}

template <class E>
Link<E>::Link(/*Link<E>* nextval = NULL*/){
    //next = nextval;
    next = NULL;
}
