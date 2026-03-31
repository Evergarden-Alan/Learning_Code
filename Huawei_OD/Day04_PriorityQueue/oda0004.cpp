#include <bits/stdc++.h>
#define FAST_IO                  \
    ios::sync_with_stdio(false); \
    cin.tie(0);                  \
    cout.tie(0);
using namespace std;

struct Task
{
    int id;
    int priority;
};

struct CompareTask
{
    bool operator()(const Task &a, const Task &b)
    {
        if (a.priority != b.priority)
            return a.priority < b.priority;
        return a.id > b.id;
    }
};

class Printer
{
private:
    priority_queue<Task, vector<Task>, CompareTask> pq;

public:
    Printer()
    {
    }

    void insert_STL(int id, int priority)
    {
        pq.push({id, priority});
    }

    int pop_STL()
    {
        if (pq.empty())
            return -1;
        int top = pq.top().id;
        pq.pop();
        return top;
    }
};

int main()
{
    FAST_IO;
    int N;
    cin >> N;

    vector<Printer> printers(5);
    int index = 1;
    while (N--)
    {
        string opt, printer_index, priority;
        cin >> opt;

        bool isIN = (opt == "IN");

        if (isIN)
        {
            cin >> printer_index >> priority;
            printers[stoi(printer_index)-1].insert_STL(index++, stoi(priority));
        }
        else
        {
            cin >> printer_index;
            
            int value = printers[stoi(printer_index)-1].pop_STL();//注意审题，打印机index是1~5
            if (value == -1)
            {
                cout << "NULL" << "\n";
            }
            else
            {
                cout << value << "\n";
            }
        }
    }
    return 0;
}