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
        // istringstream dateiss(date);
        // Parse date string in format "year/month/day"
        size_t pos1 = date.find('/');
        size_t pos2 = date.find('/', pos1 + 1);
        int year = stoi(date.substr(0, pos1));
        int month = stoi(date.substr(pos1 + 1, pos2 - pos1 - 1));
        int day = stoi(date.substr(pos2 + 1));
        // dateiss >> year >> month >> day;
        // if(workers.count(name)!=0) continue;
        workers[name] = worker{year, month, day};
    }

    int result=0;
    for(auto const & [name,worker] : workers){
        if(worker.month==search_month) result++;
    }

    cout<<result;
    return 0;
}