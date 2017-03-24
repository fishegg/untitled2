#include <iostream>
#include <fstream>
#include <string>
#include "graphm.h"
#include "graphm.cpp"
#include "link.h"
#include "link.cpp"
#include "llist.h"
#include "llist.cpp"
#include "station.h"
#include "station.cpp"
#include "route_search.h"
#include "route_search.cpp"
#include <vector>
#include <stack>
#include <queue>

using namespace std;

int main(int argc, char *argv[])
{
	cout << "Hello World!" << endl;

	unsigned num, line_count;
	int other1, other2, other3;
	string stn_num, stn_name, line;
	bool inter;

    int tmp, i, j;

    //LList<Station> stn_list;
    //LList<Station>* list_ptr = &stn_list;
    vector<Station> stn_list;
    vector<Station>* list_ptr = &stn_list;

    int stations_count = 276;
    int graph[276][276];
    Graphm system_map(stations_count);
    Graphm* map_ptr = &system_map;
    Route_search search(stations_count);
    string src, dst;

    ifstream file;
    //file.open("C:\\Users\\shit\\Documents\\build-untitled2-Desktop_Qt_5_7_0_MSVC2015_64bit-Debug\\debug\\StationsList", ios::in);
    file.open("StationsList", ios::in);
	if (!file) {
		cout << "shit" << endl;
	}
    else{
        while (file >> num >> stn_num >> stn_name >> inter >> line_count >> line >> other1 >> other2 >> other3) {
            //cout<<num<<stn_num<<stn_name<<inter<<line_count<<line<<' '<<other1<<other2<<other3<<endl;
            Station temp_stn(num, line_count, stn_num, stn_name, line, other1, other2, other3, inter);
            //stn_list.append(temp_stn);
            stn_list.push_back(temp_stn);
            //cout << stn_list.length() << endl;
            cout << stn_list.size() << endl;
        }
        file.close();
    }

    //stn_list.print();

    //file.open("C:\\Users\\shit\\Documents\\build-untitled2-Desktop_Qt_5_7_0_MSVC2015_64bit-Debug\\debug\\SystemGraph", ios::in);
    file.open("SystemGraph", ios::in);
	if (!file) {
		cout << "shit" << endl;
	}
    for (i = 0; i<stations_count; i++) {
        for (j = 0; j<stations_count; j++) {
			file >> graph[i][j];
		}
	}
	file.close();

    for (i = 0; i<stations_count; i++) {
        for (j = 0; j<stations_count; j++) {
            //cout << graph[i][j];
            system_map.setedge(i, j, graph[i][j]);
        }
    }
    //system_map.print();

    cin>>src>>dst;
    search.search(map_ptr, list_ptr, src, dst);
    search.printresult(list_ptr);

    //cout<<"end"<<endl;
	system("pause");
	return 0;
}
