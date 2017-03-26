#include "route_search.h"
#include "graphm.h"
#include "lstack.h"
#include "llist.h"
#include "station.h"
#include "lqueue.h"
#include <iostream>
#include <stack>
#include <vector>
#include <queue>

using namespace std;

Route_search::Route_search(int numvert)
{
    int i;
    D = new int[numvert];
    D_temp = new int[numvert];
    F = new int[numvert];
    F_temp = new int[numvert];
    for(i=0; i<numvert; i++){
        D[i] = 99999;
        D_temp[i] = 99999;
        F[i] = i;
        F_temp[i] = i;
    }
    source = -1;
    destination = -1;
}

Route_search::~Route_search(){
    cout<<"~Route_search"<<endl;
    delete [] D;
    D = NULL;
    delete [] D_temp;
    D_temp = NULL;
    delete [] F;
    F = NULL;
    delete [] F_temp;
    F_temp = NULL;
    //system("pause");
}

//void Route_search::convtonumber(LList<Station>* list, string src, string dst){
void Route_search::convtonumber(vector<Station>* list, string src, string dst){
    //cout<<"conv"<<endl;
    int i, j;
    bool src_ok = false, dst_ok = false;//记录起点终点转换好没有
    Station temp_stn;
    //list->movetostart();
    //for(i=0; i<list->length(); i++){
    for(i=0; i<list->size(); i++){
        //cout<<"i"<<i<<endl;
        //temp_stn = list->getvalue();
        temp_stn = list->at(i);
        if(!src_ok || !dst_ok){
            if((!src_ok) &&
                    (temp_stn.name() == src) ||(temp_stn.stnnumber() == src)){
                for(j=0; j<temp_stn.count(); j++){//看看这个站有多少条线
                    switch(j){
                    case 0: //same_src.enqueue(temp_stn.number());
                        same_src.push(temp_stn.number());
                        //source = temp_stn.number();//记录起点编号
                        break;
                    case 1: //same_src.enqueue(temp_stn.same1());//保存另外的线路对于那个站的编号
                        same_src.push(temp_stn.same1());
                        break;
                    case 2: //same_src.enqueue(temp_stn.same2());
                        same_src.push(temp_stn.same2());
                        break;
                    case 3: //same_src.enqueue(temp_stn.same3());
                        same_src.push(temp_stn.same3());
                        break;
                    }
                }
                src_ok = !src_ok;
                //cout<<"same source"<<same_src.length()<<endl;
                cout<<"same source"<<same_src.size()<<endl;
            }

            else if((!dst_ok) &&
                    (temp_stn.name() == dst) || (temp_stn.stnnumber() == dst)){
                //cout<<"same destination count"<<temp_stn.count()<<endl;
                for(j=0; j<temp_stn.count(); j++){
                    //cout<<"j"<<j<<endl;
                    switch(j){
                    case 0: //same_dst.enqueue(temp_stn.number());
                        same_dst.push(temp_stn.number());
                        //destination = temp_stn.number();
                        break;
                    case 1: //same_dst.enqueue(temp_stn.same1());
                        same_dst.push(temp_stn.same1());
                        break;
                    case 2: //same_dst.enqueue(temp_stn.same2());
                        same_dst.push(temp_stn.same2());
                        break;
                    case 3: //same_dst.enqueue(temp_stn.same3());
                        same_dst.push(temp_stn.same3());
                        break;
                    }
                }
                dst_ok = !dst_ok;
                //cout<<"same destination"<<same_dst.length()<<endl;
                cout<<"same destination"<<same_dst.size()<<endl;
            }
            //list->next();
        }

        else{
            break;
        }
    }

    if(!src_ok || !dst_ok){
        source = 0;
        destination = 1;
    }
}

void Route_search::dijkstra(Graphm *G, int s, bool forcompare){
    //cout<<"dijkstra start"<<endl;
    int i, v, w;
    G->clearmark();

    if(!forcompare){
        //cout<<"!temp"<<endl;
        D[s] = 0;
        for(i=0; i<G->n(); i++){
            v = minvertex(G, forcompare);
            if(D[v] == 99999)
                return;
            G->setmark(v, 1);
            for(w=G->first(v); w<G->n(); w=G->next(v,w)){
                if(D[w] > (D[v] + G->weight(v,w))){
                    D[w] = D[v] + G->weight(v,w);
                    F[w] = v;
                }
            }
        }
    }

    else{
        //cout<<"temp"<<endl;
        D_temp[s] = 0;
        for(i=0; i<G->n(); i++){
            v = minvertex(G, forcompare);
            if(D_temp[v] == 99999)
                return;
            G->setmark(v, 1);
            for(w=G->first(v); w<G->n(); w=G->next(v,w)){
                if(D_temp[w] > (D_temp[v] + G->weight(v,w))){
                    D_temp[w] = D_temp[v] + G->weight(v,w);
                    F_temp[w] = v;
                }
            }
        }
    }
    //cout<<"dijkstra finished"<<endl;
}

//void Route_search::search(Graphm* G, LList<Station>* list, string s, string d){
void Route_search::search(Graphm* G, vector<Station>* list, string s, string d){
    convtonumber(list, s, d);

    //if(same_src.length() == 0 && same_dst.length() == 0){//如果起点终点都不是转乘站
    if(same_src.size() == 0 && same_dst.size() == 0){
        cout<<"source1="<<source<<endl;
        source = same_src.front();
        destination = same_dst.front();
        same_src.pop();
        same_dst.pop();
        dijkstra(G, source, false);
    }

    //else if(same_src.length() > 0 && same_dst.length() == 0){//起点是
    else if(same_src.size() > 0 && same_dst.size() == 0){
        cout<<"interchange source"<<endl;
        source = same_src.front();
        destination = same_dst.front();
        same_src.pop();
        same_dst.pop();
        dijkstra(G, source, false);
        //int n = same_src.length(), temp_src;
        int n = same_src.size(), temp_src;
        cout<<"n"<<n<<endl;
        int i, j;
        for(i=0; i<n; i++){
            //cout<<"i"<<i<<endl;
            //temp_src = same_src.dequeue();//从这个站另一条线出发
            temp_src = same_src.front();
            same_src.pop();
            cout<<"dequeued"<<endl;
            cout<<"sourcen="<<temp_src<<endl;
            dijkstra(G, temp_src, true);
            if(D[destination] > D_temp[destination]){//如果这条线比较近
                source = temp_src;
                //for(j=0; j<list->length(); j++){
                for(j=0; j<list->size(); j++){
                    D[j] = D_temp[j];
                    F[j] = F_temp[j];
                }
            }
        }
    }

    //else if(same_src.length() == 0 && same_dst.length() > 0){//终点是
    else if(same_src.size() == 0 && same_dst.size() > 0){
        //cout<<"intechange destination"<<endl;
        source = same_src.front();
        destination = same_dst.front();
        same_src.pop();
        same_dst.pop();
        dijkstra(G, source, false);
        //int n = same_dst.length(), temp_dst;
        int n = same_dst.size(), temp_dst;
        //cout<<"n"<<n<<endl;
        int i, j;
        for(i=0; i<n; i++){
            //cout<<"i"<<i<<endl;
            //temp_dst = same_dst.dequeue();
            temp_dst = same_dst.front();
            same_dst.pop();
            //cout<<"dequeued"<<endl;
            dijkstra(G, source, true);
            if(D[destination] > D_temp[temp_dst]){
                destination = temp_dst;
                //for(j=0; j<list->length(); j++){
                for(j=0; j<list->size(); j++){
                    D[j] = D_temp[j];
                    F[j] = F_temp[j];
                }
            }
        }
    }

    //else if(same_src.length() > 0 && same_dst.length() > 0){//都是
    else if(same_src.size() > 0 && same_dst.size() > 0){
        //cout<<"both interchanges"<<endl;
        source = same_src.front();
        destination = same_dst.front();
        same_src.pop();
        same_dst.pop();
        same_src.push(source);
        same_dst.push(destination);
        dijkstra(G, source, false);
        //int src_count = same_src.length(), dst_count = same_dst.length(),
                //temp_src, temp_dst;
        int src_count = same_src.size(), dst_count = same_dst.size(),temp_src, temp_dst;
        int i, j, k;
        for(i=0; i<src_count; i++){
            //temp_src = same_src.dequeue();
            temp_src = same_src.front();
            same_src.pop();
            for(j=0; j<dst_count; j++){
                //temp_dst = same_dst.dequeue();
                temp_dst = same_dst.front();
                same_dst.pop();
                dijkstra(G, temp_src, true);
                if(D[destination] > D_temp[temp_dst]){
                    source = temp_src;
                    destination = temp_dst;
                    //for(k=0; k<list->length(); k++){
                    for(k=0; k<list->size(); k++){
                        D[k] = D_temp[k];
                        F[k] = F_temp[k];
                    }
                }
                //same_dst.enqueue(temp_dst);
                same_dst.push(temp_dst);
            }
        }
    }
}

void Route_search::printdistance(){
    cout<<"source"<<source<<endl;
    cout<<"destination"<<destination<<endl;
    cout << D[destination] << endl;
}

//void Route_search::printroute(LList<Station>* list){
void Route_search::printroute(vector<Station>* list){
    //cout<<"printroute"<<endl;
    if(D[destination] == 99999){
        cout<<"no route"<<endl;
        return;
    }
    int prev = destination;
    int i = 0, number;
    //LStack<int> rt;
    stack<int> rt;
    Station this_stn, prev_stn;
    do{
        rt.push(prev);
        prev = F[prev];
        i++;
    }while(prev != source);
    rt.push(prev);

    //cout<<"push times"<<rt.length()<<endl;
    //while(rt.length() > 0){
    while(rt.size()>0){
        number = rt.top();
        rt.pop();
        //list->movetopos(number);
        //this_stn = list->getvalue();
        this_stn = list->at(number);
        if(number == source){
            cout<<this_stn.name()<<"乘坐"<<this_stn.line()<<endl;
        }
        else if(this_stn.name() == prev_stn.name()){
            cout<<this_stn.name()<<"换乘"<<this_stn.line()<<endl;
        }
        else{
            cout<<this_stn.name()<<endl;
        }
        prev_stn = this_stn;
    }
}

//void Route_search::printresult(LList<Station>* list){
void Route_search::printresult(vector<Station>* list){
    printdistance();
    printroute(list);
}
