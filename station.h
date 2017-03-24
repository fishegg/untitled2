#ifndef STATION_H
#define STATION_H
#include <string>

//using namespace std;


class Station
{
private:
    int num, lines_count;
    int s1, s2, s3;
    string stn_num, stn_name, line0;
    bool interchange;
public:
    Station();
    Station(int n, int l, string s, string sn, string li, int o1, int o2, int o3, bool i);
    int number();
    string stnnumber();
    string name();
    bool isinterchange();
    int count();
    string line();
    int same1();
    int same2();
    int same3();

};

#endif // STATION_H
