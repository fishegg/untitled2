#ifndef ROUTE_SEARCH_H
#define ROUTE_SEARCH_H
#include <string>
#include "graphm.h"
#include "llist.h"
#include "station.h"
#include "lqueue.h"
#include <stack>
#include <vector>
#include <queue>

using namespace std;

class Route_search
{
private:
    int *D;//储存到各点的距离
    int *D_temp;//同上，用来比较不同路线的距离
    int *F;//储存到各点最短距离上一步是哪一个结点
    int *F_temp;//同上
    int source, destination;//起点，终点
    //LQueue<int> same_src;//起点是转乘站时，保存不同线路对应那个站的编号
    queue<int> same_src;
    //LQueue<int> same_dst;//终点……………………………………………………………………………………
    queue<int> same_dst;
    int minvertex(Graphm* G, bool forcompare){
        int i, v = -1;
        for(i=0; i<G->n(); i++){
            if(G->getmark(i) == 0){
                v = i;
                break;
            }
        }
        if(!forcompare){
            for(i++; i<G->n(); i++){
                if((G->getmark(i) == 0) && (D[i] < D[v])){
                    v = i;
                }
            }
        }
        else{
            for(i++; i<G->n(); i++){
                if((G->getmark(i) == 0) && (D_temp[i] < D_temp[v])){
                    v = i;
                }
            }
        }
        return v;
    }
public:
    Route_search(int numvert);
    ~Route_search();
    //void convtonumber(LList<Station>* list, string src, string dst);//将站名转换成编号
    void convtonumber(vector<Station>* list, string src, string dst);
    void dijkstra(Graphm* G, int s, bool forcompare);
    //void search(Graphm* G, LList<Station>* list, string s, string d);
    void search(Graphm* G, vector<Station>* list, string s, string d);
    void printdistance();
    //void printroute(LList<Station>* list);
    void printroute(vector<Station>* list);
    //void printresult(LList<Station>* list);
    void printresult(vector<Station>* list);
};

#endif // ROUTE_SEARCH_H
