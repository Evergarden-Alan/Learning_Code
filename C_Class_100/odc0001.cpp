#include <bits/stdc++.h>
#define FAST_IO ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
using namespace std;

struct worker
{
    int year;
    int month;
    int day;
};


class Solution{
private:

public:
    Solution(){
    }
};


int main(){
    FAST_IO;

    int search_month;
    cin>>search_month;
    cin.ignore();

    string row_names;
    getline(cin,row_names);

    string row_dates;
    getline(cin,row_dates);

    stringstream namestream(row_names);
    stringstream datestream(row_dates);

    string name;
    string date;
    unordered_map<string,worker> workers;
    while (getline(namestream, name, ' '))
    {
        getline(datestream, date, ' ');
        istringstream dateiss(date);
        int year, month, day;
        dateiss >> year >> month >> day;
        workers[name] = worker{year, month, day};
    }
    
    

    return 0;
}