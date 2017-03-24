#include "station.h"
#include <string>

Station::Station()
{
    num = -1;
    lines_count = 0;
    stn_num = "null";
    stn_name = "null";
    interchange = false;
    line0 = "null";
    s1 = -1;
    s2 = -1;
    s3 = -1;
}

Station::Station(int n, int l, string s, string sn, string li, int o1, int o2, int o3, bool i){
    num = n;
    lines_count = l;
    stn_num = s;
    stn_name = sn;
    interchange = i;
    line0 = li;
    s1 = o1;
    s2 = o2;
    s3 = o3;
}

int Station::number(){
    return num;
}

string Station::stnnumber(){
    return stn_num;
}

string Station::name(){
    return stn_name;
}

bool Station::isinterchange(){
    return interchange;
}

int Station::count(){
    return lines_count;
}

string Station::line(){
    return line0;
}

int Station::same1(){
    return s1;
}

int Station::same2(){
    return s2;
}

int Station::same3(){
    return s3;
}
