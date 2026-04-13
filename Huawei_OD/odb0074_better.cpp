#include <bits/stdc++.h>
#define FAST_IO                  \
    ios::sync_with_stdio(false); \
    cin.tie(0);                  \
    cout.tie(0);
using namespace std;

struct file
{
    string filename;
    int get_time;
    int size = -1;
    int get_count = 0;
};

class Solution
{
private:
    // file *head = new file();
    unordered_map<string, file> filename_to_file;
    int max_size, current_size = 0;

public:
    Solution(int m)
    {
        max_size = m;
    }

    bool isOverflow(int filesize)
    {
    }

    void clearCache()
    {
    
    }

    void put(string filename, int filesize, int time)
    {
    
    }

    void get(string filename, int get_time)
    {
    
    }

    vector<string> getresult(){
    
    }
};

int main()
{
    FAST_IO;
    int m, n;
    cin >> m >> n;
    cin.ignore();

    int time = 0;
    Solution solu = Solution(m);
    while (n--)
    {
        string raw_opt;
        getline(cin, raw_opt);
        stringstream ss(raw_opt);
        string split_opt;

        vector<string> opt;
        while (getline(ss, split_opt, ' '))
        {
            opt.push_back(split_opt);
        }

        if (opt[0] == "put")
        {
            solu.put(opt[1], stoi(opt[2]), time);
        }
        else
        {
            solu.get(opt[1], time);
        }
        time++;
    }

    vector<string> result = solu.getresult();
    if(result.size()==0) cout<<"NONE";
    for (size_t i = 0; i < result.size(); i++)
    {
        cout<<result[i];
        if(i<result.size()-1){
            cout<<",";
        }
    }
    


    return 0;
}