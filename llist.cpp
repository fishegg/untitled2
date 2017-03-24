#include "llist.h"
#include "link.h"
#include "station.h"

template <typename E>
LList<E>::LList()
{
    init();
}

template <typename E>
LList<E>::~LList(){
    cout<<"~LList"<<endl;
    removeall();
    //system("pause");
}

template <typename E>
void LList<E>::clear(){
    removeall();
    init();
}

/*void LList::insert(const E& it){
    curr->next = new Link<E>(it, curr->next);
    if(tail == curr){
        tail = curr->next;
    }
    cnt++;
}*/

template <typename E>
void LList<E>::append(const E& it){
    tail = tail->next = new Link<E>(it, NULL);
	cnt++;
}

template <typename E>
void LList<E>::movetostart(){
    curr = head;
}

template <typename E>
void LList<E>::movetoend(){
    curr = tail;
}

template <typename E>
void LList<E>::prev(){
    if(curr == head)
        return;
    Link<E>* temp = head;
    while(temp->next != curr){
        temp = temp->next;
    }
    curr = temp;
}

template <typename E>
void LList<E>::next(){
    if(curr != tail)
        curr = curr->next;
}

template <typename E>
int LList<E>::length() const{
    return cnt;
}

template <typename E>
int LList<E>::currpos() const{
    Link<E>* temp = head;
    int i;
    for(i=0; curr!=temp; i++){
        temp = temp->next;
    }
    return i;
}

template <typename E>
void LList<E>::movetopos(int pos){
    curr = head;
    for(int i=0; i<pos; i++){
        curr = curr->next;
    }
}

template <typename E>
const E& LList<E>::getvalue() const{
    return curr->next->element;
}

template <typename E>
void LList<E>::print() {
	int i;
    Station stn;
	int n = length();
    cout << "list" << n << endl;
	movetostart();
    for (i = 0; i < cnt; i++) {
        stn = getvalue();
        cout << stn.number() << stn.stnnumber() << stn.name() << stn.isinterchange() << stn.count() << stn.line() << stn.same1() << stn.same2() << stn.same3() << endl;
		next();
    }
}
