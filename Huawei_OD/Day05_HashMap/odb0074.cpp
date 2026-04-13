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
        return (filesize + current_size > max_size);
    }

    void clearCache()
    {
        string erase_key;
        int latest_use = INT_MAX;
        int count = INT_MAX;
        for (auto const &f : filename_to_file)
        {
            if (f.second.get_count < count)
            {
                erase_key = f.first;
                count = f.second.get_count;
                latest_use = f.second.get_time;
            }
            else if (f.second.get_count == count)
            {
                if (f.second.get_time < latest_use)
                {
                    erase_key = f.first;
                    latest_use = f.second.get_time;
                }
            }
        }
        current_size -= filename_to_file[erase_key].size;
        filename_to_file.erase(erase_key);
    }

    void put(string filename, int filesize, int time)
    {
        if (filename_to_file.count(filename)==0)
        { // 新节点，执行插入；重名则无任何操作
            file new_file;
            new_file.filename = filename;
            new_file.size = filesize;
            new_file.get_time = time;
            if (!isOverflow(filesize)) // 有空间
            {
                filename_to_file[filename] = new_file;
            }
            else
            { // 没空间
                while (isOverflow(filesize))
                {
                    clearCache();//复杂度太高！！！！！！！！！！！！！！！！！！！！！1
                }
                filename_to_file[filename] = new_file;
            }

            current_size += filesize;
        }
    }

    void get(string filename, int get_time)
    {
        if (filename_to_file.count(filename) != 0)
        {
            filename_to_file[filename].get_count++;
            filename_to_file[filename].get_time = get_time;
        }
    }

    vector<string> getresult(){
        vector<string> result;
        for(auto const& f: filename_to_file){
            result.push_back(f.first);
        }
        sort(result.begin(),result.end());

        return result;
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